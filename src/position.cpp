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

#include "position.hpp"

#include "util/parse.hpp"

#include <sstream>
#include <string>

namespace surveyor {
auto position::parse(std::string_view sv) -> position {
  const std::string  in{sv};
  std::istringstream ss{in};

  std::string board, fen_col, castling, ep, move_rule;
  ss >> board >> fen_col >> castling >> ep >> move_rule;

  position out{};

  {
    color_array<u8> next_id{1, 1};
    usize           read_idx = 0;

    const auto put_piece_raw = [&](color col, piece_type ptype, square sq, u8 id) {
      piece_id pid{id};
      out.m_mail_box[sq] = place{pid, col, ptype};

      out.m_piece_list[col].mask.set(pid);
      out.m_piece_list[col].ptypes[id]  = ptype;
      out.m_piece_list[col].squares[id] = sq;
    };

    const auto put_piece = [&](color col, piece_type ptype, square sq) {
      u8& id = next_id[col];
      put_piece_raw(col, ptype, sq, id);
      ++id;
    };

    for (usize sq_idx = 0; sq_idx < square::count; ++sq_idx) {
      const char   ch = board[read_idx++];
      const square sq{sq_idx};

      switch (ch) {
      case '/':
        --sq_idx;
        break;
      case '1' ... '8':
        sq_idx += ch - '1';
        break;
      case 'K':
        put_piece_raw(color::white(), piece_type::king(), sq, 0);
        break;
      case 'Q':
        put_piece(color::white(), piece_type::queen(), sq);
        break;
      case 'R':
        put_piece(color::white(), piece_type::rook(), sq);
        break;
      case 'B':
        put_piece(color::white(), piece_type::bishop(), sq);
        break;
      case 'N':
        put_piece(color::white(), piece_type::knight(), sq);
        break;
      case 'P':
        put_piece(color::white(), piece_type::pawn(), sq);
        break;
      case 'k':
        put_piece_raw(color::black(), piece_type::king(), sq, 0);
        break;
      case 'q':
        put_piece(color::black(), piece_type::queen(), sq);
        break;
      case 'r':
        put_piece(color::black(), piece_type::rook(), sq);
        break;
      case 'b':
        put_piece(color::black(), piece_type::bishop(), sq);
        break;
      case 'n':
        put_piece(color::black(), piece_type::knight(), sq);
        break;
      case 'p':
        put_piece(color::black(), piece_type::pawn(), sq);
        break;
      default:
        break;
      }
    }
  }

  out.m_stm = fen_col == "w" ? color::white() : color::black();

  if (castling != "-") {
    const auto scan_for_rook = [&](color stm, i32 file, i32 dir) -> std::optional<square> {
      const i32 rank = stm == color::white() ? 0 : 7;

      for (file += dir; file >= 0 && file < 8; file += dir) {
        const square sq{file, rank};

        if (const auto [c, ptype] = out.piece_at(sq); c == stm && ptype == piece_type::rook()) {
          return sq;
        }
      }

      return std::nullopt;
    };

    for (const char ch : castling) {
      if (ch == 'K') {
        out.m_rook_info[color::white()].h_side = scan_for_rook(color::white(), 7, -1);
      } else if (ch == 'Q') {
        out.m_rook_info[color::white()].h_side = scan_for_rook(color::white(), 0, 1);
      } else if (ch == 'k') {
        out.m_rook_info[color::black()].h_side = scan_for_rook(color::black(), 7, -1);
      } else if (ch == 'q') {
        out.m_rook_info[color::black()].h_side = scan_for_rook(color::black(), 0, 1);
      } else {
        const color  stm       = std::isupper(ch) ? color::white() : color::black();
        const i32    rook_file = ch - (std::isupper(ch) ? 'A' : 'a');
        const i32    king_file = out.king_square(stm).file();
        const square rook_sq   = square{rook_file, stm == color::white() ? 0 : 7};

        if (rook_file < king_file) {
          out.m_rook_info[stm].a_side = rook_sq;
        } else {
          out.m_rook_info[stm].h_side = rook_sq;
        }
      }
    }
  }

  if (ep != "-") {
    out.m_ep = square::parse(ep);
  }

  if (const auto mr = parse_number<i32>(move_rule)) {
    out.m_move_rule = *mr;
  } else {
    out.m_move_rule = 0;
  }

  return out;
}

}  // namespace surveyor
