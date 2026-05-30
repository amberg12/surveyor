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
#include "piece.hpp"
#include "square.hpp"

#include <array>
#include <optional>
#include <string_view>
#include <tuple>

namespace surveyor {

struct mail_box {
  std::array<place, square::count> byte_board{};

  constexpr auto operator[](square sq) -> place& {
    return byte_board[sq.idx];
  }

  constexpr auto operator[](square sq) const -> const place& {
    return byte_board[sq.idx];
  }
};

struct piece_list {
  piece_mask                                mask{};
  std::array<square, piece_mask::count>     squares{};
  std::array<piece_type, piece_mask::count> ptypes{};
};

struct rook_info {
  std::optional<square> a_side = std::nullopt;
  std::optional<square> h_side = std::nullopt;
};

class position {
public:
  // Constructors
  static auto parse(std::string_view sv) -> position;

  // Methods
  [[nodiscard]] constexpr auto ep() const -> square {
    return m_ep;
  }

  [[nodiscard]] constexpr auto king_square(color stm) const -> square {
    const auto& pl = m_piece_list[stm];
    return pl.squares[piece_id::king().idx()];
  }

  [[nodiscard]] constexpr auto piece_at(square sq) const -> std::tuple<color, piece_type> {
    const auto [pid, col, ptype] = m_mail_box[sq].unpack();
    return {col, ptype};
  }

private:
  position() = default;

  mail_box                m_mail_box;
  color_array<piece_list> m_piece_list;

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

            out += col == color::white() ? std::toupper(ch) : ch;
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
