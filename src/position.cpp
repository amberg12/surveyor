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

      out.m_color_bb[col].set(sq);
      out.m_piece_bb[ptype].set(sq);
    };

    const auto put_piece = [&](color col, piece_type ptype, square sq) {
      u8& id = next_id[col];
      put_piece_raw(col, ptype, sq, id);
      ++id;
    };

    for (usize sq_idx = 0; sq_idx < square::count; ++sq_idx) {
      const char   ch = board[read_idx++];
      const square sq{sq_idx ^ 56};

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

      for (; file >= 0 && file < 8; file += dir) {
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
        out.m_rook_info[color::white()].a_side = scan_for_rook(color::white(), 0, 1);
      } else if (ch == 'k') {
        out.m_rook_info[color::black()].h_side = scan_for_rook(color::black(), 7, -1);
      } else if (ch == 'q') {
        out.m_rook_info[color::black()].a_side = scan_for_rook(color::black(), 0, 1);
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

  out.lazy_generate_attacks();
  out.lazy_generate_pinner();
  out.lazy_generate_key();

  return out;
}

auto position::lazy_generate_key() -> void {
  m_key = 0;

  for (const piece_id id : m_piece_list[color::white()].mask) {
    const usize ptype_idx = ptype_of(color::white(), id).compressed_idx();
    const usize sq_idx = sq_of(color::white(), id).idx;
    m_key ^= zobrist::pieces[0][ptype_idx][sq_idx];
  }

  for (const piece_id id : m_piece_list[color::black()].mask) {
    const usize ptype_idx = ptype_of(color::black(), id).compressed_idx();
    const usize sq_idx = sq_of(color::black(), id).idx;
    m_key ^= zobrist::pieces[1][ptype_idx][sq_idx];
  }

  if (m_ep.has_value()) {
    m_key ^= zobrist::en_passant[m_ep.file()];
  }

  const usize castling_idx = [&] {
    usize out = 0;

    if (m_rook_info[color::white()].a_side.has_value()) {
      out |= 0b0001;
    }

    if (m_rook_info[color::white()].h_side.has_value()) {
      out |= 0b0010;
    }

    if (m_rook_info[color::black()].a_side.has_value()) {
      out |= 0b0100;
    }

    if (m_rook_info[color::black()].h_side.has_value()) {
      out |= 0b1000;
    }

    return out;
  }();

  m_key ^= zobrist::castling[castling_idx];

  if (m_stm == color::white()) {
    m_key ^= zobrist::stm;
  }
}

auto position::lazy_generate_pinner() -> void {
  m_pin_aware_attack_table = m_attack_box[m_stm];
  m_pinned                 = {};

  const color  stm     = m_stm;
  const square king_sq = king_square(stm);

  const auto handle_pin = [&](square to) {
    const bitboard ray        = bitboard::ray_exclusive(king_sq, to);
    const bitboard all_pieces = bb();
    const bitboard our_pieces = color_bb(stm);

    if ((all_pieces & ray).popcount() != 1) {
      return;
    }

    if ((our_pieces & ray).popcount() != 1) {
      return;
    }

    const square pinned = (our_pieces & ray).lsb();
    m_pinned.set(pinned);

    const piece_id pinned_id = id_at(pinned);
    const bitboard ray_incl = bitboard::ray_inclusive(king_sq, to);

    m_pin_aware_attack_table.remove_attacker(pinned_id, ~ray_incl);
  };

  for (const piece_id id : ptype_mask(~stm, piece_type::bishop(), piece_type::queen())) {
    const square sq = sq_of(~stm, id);

    if (!sq.diag_to(king_sq)) {
      continue;
    }

    handle_pin(sq);
  }

  for (const piece_id id : ptype_mask(~stm, piece_type::rook(), piece_type::queen())) {
    const square sq = sq_of(~stm, id);

    if (!sq.orth_to(king_sq)) {
      continue;
    }

    handle_pin(sq);
  }
}

auto position::lazy_generate_attacks() -> void {
  m_attack_box = {};

  const auto lazy_generate_attacks_for = [&](color stm) {
    const piece_mask pm = m_piece_list[stm].mask;

    for (const auto id : pm) {
      const square s = sq_of(stm, id);
      generate_attacks(s);
    }
  };

  lazy_generate_attacks_for(color::white());
  lazy_generate_attacks_for(color::black());
}

auto position::generate_attacks(square src) -> void {
  const auto [id, col, ptype] = place_at(src);

  if (ptype == piece_type::pawn()) {
    if (col == color::white()) {
      generate_leapers(col, id, src, geometry::ne_diag);
      generate_leapers(col, id, src, geometry::nw_diag);
    } else {
      generate_leapers(col, id, src, geometry::se_diag);
      generate_leapers(col, id, src, geometry::sw_diag);
    }
  }

  if (ptype == piece_type::knight()) {
    generate_leapers(col, id, src, geometry::nne_horsie);
    generate_leapers(col, id, src, geometry::nee_horsie);
    generate_leapers(col, id, src, geometry::see_horsie);
    generate_leapers(col, id, src, geometry::sse_horsie);
    generate_leapers(col, id, src, geometry::ssw_horsie);
    generate_leapers(col, id, src, geometry::sww_horsie);
    generate_leapers(col, id, src, geometry::nww_horsie);
    generate_leapers(col, id, src, geometry::nnw_horsie);
  }

  if (ptype == piece_type::king()) {
    generate_leapers(col, id, src, geometry::n_orth);
    generate_leapers(col, id, src, geometry::ne_diag);
    generate_leapers(col, id, src, geometry::e_orth);
    generate_leapers(col, id, src, geometry::se_diag);
    generate_leapers(col, id, src, geometry::s_orth);
    generate_leapers(col, id, src, geometry::sw_diag);
    generate_leapers(col, id, src, geometry::w_orth);
    generate_leapers(col, id, src, geometry::nw_diag);
  }

  if (ptype.orth()) {
    generate_sliders(col, id, src, geometry::n_orth);
    generate_sliders(col, id, src, geometry::e_orth);
    generate_sliders(col, id, src, geometry::s_orth);
    generate_sliders(col, id, src, geometry::w_orth);
  }

  if (ptype.diag()) {
    generate_sliders(col, id, src, geometry::ne_diag);
    generate_sliders(col, id, src, geometry::se_diag);
    generate_sliders(col, id, src, geometry::sw_diag);
    generate_sliders(col, id, src, geometry::nw_diag);
  }
}

auto position::generate_sliders(color col, piece_id id, square src, geometry::direction dir)
  -> void {
  for (auto s = geometry::shift(src, dir); s.has_value(); s = geometry::shift(*s, dir)) {
    m_attack_box[col][*s].set(id);

    if (m_mail_box[*s].has_value()) {
      break;
    }
  }
}

auto position::generate_leapers(color col, piece_id id, square src, geometry::direction dir)
  -> void {
  if (const auto s = geometry::shift(src, dir); s.has_value()) {
    m_attack_box[col][*s].set(id);
  }
}

}  // namespace surveyor
