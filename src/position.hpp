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
#include "score.hpp"
#include "square.hpp"
#include "zobrist.hpp"

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

  constexpr auto clear() -> void {
    a_side = std::nullopt;
    h_side = std::nullopt;
  }
};

class position {
public:
  // Constants
  static constexpr i32 max_phase = 24;

  // Constructors
  static auto parse(std::string_view sv) -> position;

  [[nodiscard]] auto make_move(move mv) const -> position {
    position out = *this;
    out.do_move(mv);
    out.lazy_generate_attacks();
    out.m_pin_cache_updated = false;
    return out;
  }

  [[nodiscard]] auto make_null_move() const -> position {
    position out = *this;
    out.m_stm    = ~m_stm;
    out.m_ep     = square::invalid();
    out.lazy_generate_attacks();
    out.lazy_generate_key();
    out.m_pin_cache_updated = false;
    return out;
  }

  // Methods
  [[nodiscard]] constexpr auto stm() const -> color {
    return m_stm;
  }

  [[nodiscard]] constexpr auto ep() const -> square {
    return m_ep;
  }

  [[nodiscard]] constexpr auto a_side(color stm) const -> std::optional<square> {
    return m_rook_info[stm].a_side;
  }

  [[nodiscard]] constexpr auto h_side(color stm) const -> std::optional<square> {
    return m_rook_info[stm].h_side;
  }

  [[nodiscard]] auto move_rule(i32 ply) const -> std::optional<score>;

  [[nodiscard]] constexpr auto key() const -> z_key {
    return m_key;
  }

  [[nodiscard]] constexpr auto pawn_key() const -> z_key {
    return m_pawn_key;
  }

  [[nodiscard]] constexpr auto white_non_pawn_key() const -> z_key {
    return m_white_non_pawn_key;
  }

  [[nodiscard]] constexpr auto black_non_pawn_key() const -> z_key {
    return m_black_non_pawn_key;
  }

  [[nodiscard]] constexpr auto checkers() const -> usize {
    const piece_mask king_attackers = attackers_to(~m_stm, king_square(m_stm));
    return king_attackers.popcount();
  }

  [[nodiscard]] constexpr auto king_square(color stm) const -> square {
    const auto& pl = m_piece_list[stm];
    return pl.squares[piece_id::king().idx()];
  }

  [[nodiscard]] constexpr auto has_value(square sq) const -> bool {
    return m_mail_box[sq].has_value();
  }

  [[nodiscard]] constexpr auto id_at(square sq) const -> piece_id {
    const auto [pid, col, ptype] = place_at(sq);
    return pid;
  }

  [[nodiscard]] constexpr auto ptype_at(square sq) const -> piece_type {
    const auto [pid, col, ptype] = place_at(sq);
    return ptype;
  }

  [[nodiscard]] constexpr auto piece_at(square sq) const -> std::tuple<color, piece_type> {
    const auto [pid, col, ptype] = place_at(sq);
    return {col, ptype};
  }

  [[nodiscard]] constexpr auto place_at(square sq) const -> place::unpacked {
    const auto result = m_mail_box[sq];
    return result.unpack();
  }

  [[nodiscard]] constexpr auto attackers_to(color col, square sq) const -> piece_mask {
    return m_attack_box[col][sq];
  }

  [[nodiscard]] constexpr auto is_attacked(color col, square sq) const -> bool {
    return attackers_to(col, sq).popcount() != 0;
  }

  [[nodiscard]] constexpr auto sq_of(color col, piece_id id) const -> square {
    return m_piece_list[col].sq_of(id);
  }

  [[nodiscard]] constexpr auto ptype_of(color col, piece_id id) const -> piece_type {
    return m_piece_list[col].ptype_of(id);
  }

  template<piece_type_list... Pts>
  constexpr auto ptype_mask(color c, Pts... ptypes) const -> piece_mask {
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

  template<piece_type_list... Pts>
  [[nodiscard]] constexpr auto ptype_count(color c, Pts... ptypes) const -> i32 {
    return ptype_mask(c, ptypes...).ipopcount();
  }

  [[nodiscard]] constexpr auto phase() const -> i32 {
    const auto stm_phase = [&](color stm) {
      return ptype_count(stm, piece_type::knight()) + ptype_count(stm, piece_type::bishop())
        + ptype_count(stm, piece_type::rook()) * 2 + ptype_count(stm, piece_type::queen()) * 4;
    };

    return stm_phase(color::white()) + stm_phase(color::black());
  }

  [[nodiscard]] constexpr auto pin_at() const -> const attack_box& {
    if (!m_pin_cache_updated) {
      lazy_generate_pinner();
    }

    return m_pin_aware_attack_table;
  }

  [[nodiscard]] constexpr auto pinned(square sq) const -> bool {
    if (!m_pin_cache_updated) {
      lazy_generate_pinner();
    }

    return m_pinned.has_value(sq);
  }

private:
  position() = default;

  auto do_move(move mv) -> void {
    const auto [stm, ptype] = piece_at(mv.src());

    ++m_move_rule;

    if (mv.is_capture() || ptype == piece_type::pawn()) {
      m_move_rule = 0;
    }

    const auto fix_castling = [&](square sq) {
      if (m_rook_info[color::white()].a_side == sq) {
        m_rook_info[color::white()].a_side = std::nullopt;
      }

      if (m_rook_info[color::white()].h_side == sq) {
        m_rook_info[color::white()].h_side = std::nullopt;
      }

      if (m_rook_info[color::black()].a_side == sq) {
        m_rook_info[color::black()].a_side = std::nullopt;
      }

      if (m_rook_info[color::black()].h_side == sq) {
        m_rook_info[color::black()].h_side = std::nullopt;
      }
    };

    const auto normal = [&] {
      move_piece(mv.src(), mv.dst());
      m_ep = square::invalid();

      if (ptype == piece_type::king()) {
        m_rook_info[stm].clear();
      } else {
        fix_castling(mv.src());
      }
    };

    const auto double_push = [&] {
      move_piece(mv.src(), mv.dst());
      m_ep = *geometry::shift(mv.src(), geometry::pawn_direction(m_stm));
    };

    const auto castle_aside = [&] {
      const square king_dst = m_stm == color::white() ? square{2, 0} : square{2, 7};
      const square rook_dst = m_stm == color::white() ? square{3, 0} : square{3, 7};

      move_piece(*m_rook_info[m_stm].a_side, rook_dst);
      move_piece(king_square(m_stm), king_dst);

      m_rook_info[m_stm].clear();
      m_ep = square::invalid();
    };

    const auto castle_hside = [&] {
      const square king_dst = m_stm == color::white() ? square{6, 0} : square{6, 7};
      const square rook_dst = m_stm == color::white() ? square{5, 0} : square{5, 7};

      move_piece(*m_rook_info[m_stm].h_side, rook_dst);
      move_piece(king_square(m_stm), king_dst);

      m_rook_info[m_stm].clear();
      m_ep = square::invalid();
    };

    const auto cap_normal = [&] {
      destroy_piece(mv.dst());
      move_piece(mv.src(), mv.dst());
      m_ep = square::invalid();

      if (ptype == piece_type::king()) {
        m_rook_info[stm].clear();
      } else {
        fix_castling(mv.src());
      }

      fix_castling(mv.dst());
    };

    const auto promo = [&](piece_type to) {
      move_piece(mv.src(), mv.dst());
      mutate_piece(mv.dst(), to);
      m_ep = square::invalid();
    };

    const auto cap_promo = [&](piece_type to) {
      destroy_piece(mv.dst());
      move_piece(mv.src(), mv.dst());
      mutate_piece(mv.dst(), to);

      m_ep = square::invalid();
      fix_castling(mv.dst());
    };

    const auto en_passant = [&] {
      move_piece(mv.src(), mv.dst());
      const square ep_victim = *geometry::shift(m_ep, geometry::pawn_direction(~m_stm));
      destroy_piece(ep_victim);
      m_ep = square::invalid();
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
    case move::castle_aside: {
      castle_aside();
    } break;
    case move::castle_hside: {
      castle_hside();
    } break;
    case move::promo_q: {
      promo(piece_type::queen());
    } break;
    case move::promo_n: {
      promo(piece_type::knight());
    } break;
    case move::promo_r: {
      promo(piece_type::rook());
    } break;
    case move::promo_b: {
      promo(piece_type::bishop());
    } break;
    case move::cap_promo_q: {
      cap_promo(piece_type::queen());
    } break;
    case move::cap_promo_n: {
      cap_promo(piece_type::knight());
    } break;
    case move::cap_promo_r: {
      cap_promo(piece_type::rook());
    } break;
    case move::cap_promo_b: {
      cap_promo(piece_type::bishop());
    } break;
    case move::en_passant: {
      en_passant();
    } break;
    }

    m_stm = ~m_stm;

    lazy_generate_key();
  }

  auto move_piece(square src, square dst) -> void {
    const auto [id, c, ptype] = m_mail_box[src].unpack();

    m_mail_box[dst] = m_mail_box[src];
    m_mail_box[src] = {};

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

  auto mutate_piece(square at, piece_type to) -> void {
    const auto [id, c, ptype]        = place_at(at);
    m_mail_box[at]                   = place{id, c, to};
    m_piece_list[c].ptypes[id.idx()] = to;

    m_piece_bb[ptype].del(at);
    m_piece_bb[to].set(at);
  }

  auto lazy_generate_key() -> void;

  auto lazy_generate_pinner() const -> void;

  auto lazy_generate_attacks() -> void;

  auto generate_attacks(square src) -> void;

  auto generate_sliders(color col, piece_id id, square src, geometry::direction dir) -> void;

  auto generate_leapers(color col, piece_id id, square src, geometry::direction dir) -> void;

  mail_box                m_mail_box;
  color_array<attack_box> m_attack_box;
  color_array<piece_list> m_piece_list;

  color_array<bitboard> m_color_bb;
  piece_array<bitboard> m_piece_bb;

  mutable attack_box m_pin_aware_attack_table;
  mutable bitboard   m_pinned;
  mutable bool       m_pin_cache_updated = false;

  z_key m_key                = 0;
  z_key m_pawn_key           = 0;
  z_key m_white_non_pawn_key = 0;
  z_key m_black_non_pawn_key = 0;

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
