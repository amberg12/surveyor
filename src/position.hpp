/*
  Surveyor - A UCI chess engine.
  Copyright (C) 2026 Amber Goulding

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once
#include "bitboard.hpp"
#include "geometry.hpp"
#include "move.hpp"
#include "piece.hpp"
#include "square.hpp"

#include <array>
#include <optional>
#include <string_view>
#include <tuple>

namespace surveyor {

class position;

struct mail_box {
  std::array<place, square::count> byte_board{};

  constexpr auto operator[](square sq) -> place& {
    return byte_board[sq.idx];
  }

  constexpr auto operator[](square sq) const -> const place& {
    return byte_board[sq.idx];
  }
};

struct attack_box {
  std::array<piece_mask, square::count> word_board{};

  constexpr auto operator[](square sq) const -> const piece_mask& {
    return word_board[sq.idx];
  }

  constexpr auto operator[](square sq) -> piece_mask& {
    return word_board[sq.idx];
  }

  constexpr auto remove_attacker(piece_id atk, bitboard mask) -> void {
    for (const square sq : mask) {
      (*this)[sq].del(atk);
    }
  }
};

struct piece_list {
  piece_mask                                mask{};
  std::array<square, piece_mask::count>     squares{};
  std::array<piece_type, piece_mask::count> ptypes{};

  [[nodiscard]] constexpr auto ptype_of(piece_id id) const -> const piece_type& {
    return ptypes[id.idx()];
  }

  [[nodiscard]] constexpr auto ptype_of(piece_id id) -> piece_type& {
    return ptypes[id.idx()];
  }

  [[nodiscard]] constexpr auto sq_of(piece_id id) const -> const square& {
    return squares[id.idx()];
  }

  [[nodiscard]] constexpr auto sq_of(piece_id id) -> square& {
    return squares[id.idx()];
  }

  template<piece_type_list... Pt>
  [[nodiscard]] constexpr auto ptype_mask(Pt... pts) const -> piece_mask {
    piece_mask out{};
    for (const piece_id id : mask) {
      if (((ptype_of(id) == pts) || ...)) {
        out.set(id);
      }
    }

    return out;
  }
};

struct rook_info {
  std::optional<square> a_side = std::nullopt;
  std::optional<square> h_side = std::nullopt;
};

class position {
public:
  // Constructors
  static auto parse(std::string_view sv) -> position;

  [[nodiscard]] auto make_move(move mv) const -> position {
    position out = *this;
    out.do_move(mv);
    out.lazy_generate_attacks();
    out.lazy_generate_pinner();
    return out;
  }

  // Methods
  [[nodiscard]] constexpr auto stm() const -> color {
    return m_stm;
  }

  [[nodiscard]] constexpr auto ep() const -> square {
    return m_ep;
  }

  [[nodiscard]] constexpr auto king_square(color stm) const -> square {
    const auto& pl = m_piece_list[stm];
    return pl.squares[piece_id::king().idx()];
  }

  [[nodiscard]] constexpr auto has_value(square sq) const -> bool {
    return m_mail_box[sq].has_value();
  }

  [[nodiscard]] constexpr auto piece_at(square sq) const -> std::tuple<color, piece_type> {
    const auto [pid, col, ptype] = m_mail_box[sq].unpack();
    return {col, ptype};
  }

  [[nodiscard]] constexpr auto place_at(square sq) const -> place::unpacked {
    const auto result = m_mail_box[sq];
    return result.unpack();
  }

  [[nodiscard]] constexpr auto attackers_to(color col, square sq) const -> piece_mask {
    return m_attack_box[col][sq];
  }

  [[nodiscard]] constexpr auto sq_of(color col, piece_id id) const -> square {
    return m_piece_list[col].sq_of(id);
  }

  [[nodiscard]] constexpr auto ptype_of(color col, piece_id id) const -> piece_type {
    return m_piece_list[col].ptype_of(id);
  }

  template<piece_type_list... Pts>
  constexpr auto ptype_mask(color c, Pts... ptypes) const {
    return m_piece_list[c].ptype_mask(ptypes...);
  }

  template<piece_type_list... Pts>
  [[nodiscard]] constexpr auto ptype_bb(Pts... ptypes) const -> bitboard {
    return (m_piece_bb[ptypes] | ...);
  }

  [[nodiscard]] constexpr auto color_bb(color c) const -> bitboard {
    return m_color_bb[c];
  }

  [[nodiscard]] constexpr auto bb() const -> bitboard {
    return color_bb(color::white()) | color_bb(color::black());
  }

  template<piece_type_list... Pts>
  [[nodiscard]] constexpr auto bb(color c, Pts... ptypes) const -> bitboard {
    return color_bb(c) | ptype_bb(ptypes...);
  }

  [[nodiscard]] constexpr auto pin_at() const -> const attack_box& {
    return m_pin_aware_attack_table;
  }

private:
  position() = default;

  auto do_move(move mv) -> void {
    const auto normal = [&] {
      move_piece(mv.src(), mv.dst());
    };

    const auto double_push = [&] {
      move_piece(mv.src(), mv.dst());
      m_ep = *geometry::shift(mv.src(), geometry::pawn_direction(m_stm));
    };

    const auto cap_normal = [&] {
      destroy_piece(mv.dst());
      move_piece(mv.src(), mv.dst());
    };

    switch (mv.flags()) {
    case move::normal: {
      normal();
    } break;
    case move::cap_normal: {
      cap_normal();
    } break;
    case move::double_push: {
      double_push();
    } break;
    case move::castle_aside:
    case move::castle_hside:
    case move::promo_q:
    case move::promo_n:
    case move::promo_r:
    case move::promo_b:
    case move::cap_promo_q:
    case move::cap_promo_n:
    case move::cap_promo_r:
    case move::cap_promo_b:
    case move::en_passant:
      break;
    }

    m_stm = ~m_stm;
  }

  auto move_piece(square src, square dst) -> void {
    const auto [id, c, ptype] = m_mail_box[src].unpack();
    std::swap(m_mail_box[src], m_mail_box[dst]);
    m_piece_list[c].sq_of(id) = dst;

    m_color_bb[c].del(src);
    m_color_bb[c].set(dst);

    m_piece_bb[ptype].del(src);
    m_piece_bb[ptype].set(dst);
  }

  auto destroy_piece(square at) -> void {
    const auto [id, c, ptype] = m_mail_box[at].unpack();
    m_mail_box[at]            = place{};
    m_piece_list[c].mask.del(id);

    m_color_bb[c].del(at);
    m_piece_bb[ptype].del(at);
  }

  auto lazy_generate_pinner() -> void;

  auto lazy_generate_attacks() -> void;

  auto generate_attacks(square src) -> void;

  auto generate_sliders(color col, piece_id id, square src, geometry::direction dir) -> void;

  auto generate_leapers(color col, piece_id id, square src, geometry::direction dir) -> void;

  mail_box                m_mail_box;
  color_array<attack_box> m_attack_box;
  color_array<piece_list> m_piece_list;

  color_array<bitboard> m_color_bb;
  piece_array<bitboard> m_piece_bb;

  attack_box m_pin_aware_attack_table;

  color                  m_stm = color::white();
  square                 m_ep  = square::invalid();
  i32                    m_move_rule{0};
  color_array<rook_info> m_rook_info{};
};

}  // namespace surveyor

template<>
struct std::formatter<surveyor::position> : std::formatter<std::string> {
  auto format(const surveyor::position& pos, std::format_context& ctx) const {
    using namespace surveyor;

    const std::string board = [&] {
      std::string out;

      for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
          const square sq{file, rank};
          const auto [col, ptype] = pos.piece_at(sq);

          if (ptype == piece_type::empty()) {
            out += " ";
          } else {
            const char ch = [&] {
              if (ptype == piece_type::pawn()) {
                return 'p';
              }

              if (ptype == piece_type::knight()) {
                return 'n';
              }

              if (ptype == piece_type::bishop()) {
                return 'b';
              }

              if (ptype == piece_type::rook()) {
                return 'r';
              }

              if (ptype == piece_type::queen()) {
                return 'q';
              }

              if (ptype == piece_type::king()) {
                return 'k';
              }

              return '?';
            }();

            out += col == color::white() ? static_cast<char>(std::toupper(ch)) : ch;
          }
        }

        out += "\n";
      }

      return out;
    }();

    const std::string str = std::format("{}{}", board, pos.ep());
    return std::formatter<std::string>::format(str, ctx);
  }
};
