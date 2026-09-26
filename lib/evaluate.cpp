/*
 * Surveyor - A UCI Chess Engine
 * Copyright (C) 2026 Amber Goulding
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the
 * GNU Affero General Public License as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#include "evaluate.h"

#include "evaluation_constants.h"

using namespace surveyor::evaluation_constants;

namespace surveyor {
namespace {
auto evaluate_pieces(color stm, const position& pos) -> out_pair {
  out_pair out{};

  const piece_mask ids = pos.mask(stm);

  for (const auto id : ids) {
    const piece_type ptype  = pos.ptype_of(stm, id);
    const square     sq     = pos.sq_of(stm, id);
    const square     rel_sq = sq.relative(stm);

    if (ptype == piece_type::pawn()) {
      out += pawn_material;
      out += pawn_psqt[rel_sq.idx - 8];
    }

    if (ptype == piece_type::knight()) {
      out += knight_material;
      out += knight_psqt[rel_sq.idx];
    }

    if (ptype == piece_type::bishop()) {
      out += bishop_material;
      out += bishop_psqt[rel_sq.idx];
    }

    if (ptype == piece_type::rook()) {
      out += rook_material;
      out += rook_psqt[rel_sq.idx];
    }

    if (ptype == piece_type::queen()) {
      out += queen_material;
      out += queen_psqt[rel_sq.idx];
    }

    if (ptype == piece_type::king()) {
      out += king_psqt[rel_sq.idx];
    }
  }

  return out;
}

auto evaluate_pawns(color stm, const position& pos) -> out_pair {
  out_pair out{};

  const piece_mask pawns = pos.ptype_mask(stm, piece_type::pawn());

  for (const auto id : pawns) {
    const square sq   = pos.sq_of(stm, id);
    const i32    file = sq.file();
    const i32    rank = sq.rank();

    const auto file_bb = bitboard::file_bb(file);
    const auto file_bl = bitboard::file_bb(std::clamp(file - 1, 0, 7));
    const auto file_br = bitboard::file_bb(std::clamp(file + 1, 0, 7));

    const auto lane_3 = file_bb | file_bl | file_br;

    const auto ahead_bb = [&] {
      auto out = bitboard::full();
      if (stm == color::white()) {
        for (i32 i = 0; i < rank; ++i) {
          out = out.shift(geometry::n_orth);
        }
      } else {
        for (i32 i = 0; i < rank; ++i) {
          out = out.shift(geometry::s_orth);
        }
      }
      return out;
    }();

    if ((pos.bb(~stm, piece_type::pawn()) & ahead_bb & lane_3) == bitboard::empty()) {
      const square destination_sq =
        geometry::from_x88(geometry::to_x88(sq) + geometry::pawn_direction(stm));

      const auto relative_rank = destination_sq.relative_rank(stm);

      out += passed_pawn[sq.relative_rank(stm) - 1];

      const piece_mask dst_defenders = pos.attackers_to(stm, destination_sq);
      const piece_mask dst_attackers = pos.attackers_to(~stm, destination_sq);

      if (dst_defenders.ipopcount() > dst_attackers.ipopcount()) {
        out += defended_passed_pawn[relative_rank - 2];
      }
    }

    if ((pos.bb(stm, piece_type::pawn()) & lane_3).ipopcount() == 1) {
      out += isolated_pawn;
    }
  }

  const auto pawn_bb = pos.bb(stm, piece_type::pawn());

  const auto lhs_defend = pawn_bb.shift(geometry::pawn_direction(stm)).shift(geometry::w_orth);
  const auto rhs_defend = pawn_bb.shift(geometry::pawn_direction(stm)).shift(geometry::e_orth);

  for (const auto sq : pawn_bb&(lhs_defend | rhs_defend)) {
    out += defended_pawn[sq.relative_rank(stm) - 2];
  }

  for (const auto sq : pawn_bb & pawn_bb.shift(geometry::e_orth)) {
    out += phalanx[sq.relative_rank(stm) - 1];
  }

  return out;
}

auto evaluate_threats(color stm, const position& pos) -> out_pair {
  out_pair out{};

  for (const piece_id id : pos.ptype_mask(stm, piece_type::knight())) {
    const bitboard attack_bb = pos.threat_bb(stm, id);
    const i32      mobility  = (attack_bb & ~pos.bb()).ipopcount();

    out += knight_mobility[mobility];
  }

  for (const piece_id id : pos.ptype_mask(stm, piece_type::bishop())) {
    const bitboard attack_bb = pos.threat_bb(stm, id);
    const i32      mobility  = (attack_bb & ~pos.bb()).ipopcount();

    out += bishop_mobility[mobility];
  }

  for (const piece_id id : pos.ptype_mask(stm, piece_type::rook())) {
    const bitboard attack_bb = pos.threat_bb(stm, id);
    const i32      mobility  = (attack_bb & ~pos.bb()).ipopcount();

    out += rook_mobility[mobility];
  }

  for (const piece_id id : pos.ptype_mask(stm, piece_type::queen())) {
    const bitboard attack_bb = pos.threat_bb(stm, id);
    const i32      mobility  = (attack_bb & ~pos.bb()).ipopcount();

    out += queen_mobility[mobility];
  }

  const auto pawn_bb    = pos.bb(stm, piece_type::pawn());
  const auto lhs_defend = pawn_bb.shift(geometry::pawn_direction(stm)).shift(geometry::w_orth);
  const auto rhs_defend = pawn_bb.shift(geometry::pawn_direction(stm)).shift(geometry::e_orth);

  const auto pawn_threats = lhs_defend | rhs_defend;

  out += pawn_threat_knight * (pos.bb(~stm, piece_type::knight()) & pawn_threats).ipopcount();
  out += pawn_threat_bishop * (pos.bb(~stm, piece_type::bishop()) & pawn_threats).ipopcount();
  out += pawn_threat_rook * (pos.bb(~stm, piece_type::rook()) & pawn_threats).ipopcount();
  out += pawn_threat_queen * (pos.bb(~stm, piece_type::queen()) & pawn_threats).ipopcount();

  return out;
}

auto evaluate_bishop_pair(color stm, const position& pos) -> out_pair {
  return pos.bb(stm, piece_type::bishop()).popcount() >= 2 ? bishop_pair : out_pair{};
}

auto evaluate_king_safety(color stm, const position& pos) -> out_pair {
  out_pair out{};

  const square king_sq  = pos.king_square(stm);
  const bool   lhs_king = king_sq.file() < 4;

  const i32 shelter_mid_file = std::clamp<i32>(king_sq.file(), 1, 6);

  for (i32 i = -1; i <= 1; ++i) {
    const auto     file      = bitboard::file_bb(shelter_mid_file + i);
    const bitboard our_pawns = pos.bb(stm, piece_type::pawn());

    const i32 shelter_rank =
      (our_pawns & file).any() ? our_pawns.backmost(stm).relative_rank(stm) : 0;

    const i32 rel_i = lhs_king ? i : -i;

    if (rel_i == -1) {
      out += shelter_edge[shelter_rank];
    }

    if (rel_i == 0) {
      out += shelter_mid[shelter_rank];
    }

    if (rel_i == 1) {
      out += shelter_centre[shelter_rank];
    }
  }

  return out;
}

}  // namespace

auto evaluate_unnormalized(const position& pos) -> out_pair {
  out_pair out{};

  out += evaluate_pieces(color::white(), pos);
  out -= evaluate_pieces(color::black(), pos);

  out += evaluate_threats(color::white(), pos);
  out -= evaluate_threats(color::black(), pos);

  out += evaluate_bishop_pair(color::white(), pos);
  out -= evaluate_bishop_pair(color::black(), pos);

  out += evaluate_king_safety(color::white(), pos);
  out -= evaluate_king_safety(color::black(), pos);

  out += evaluate_pawns(color::white(), pos);
  out -= evaluate_pawns(color::black(), pos);

  return pos.stm() == color::white() ? out : -out;
}

auto evaluate(const position& pos) -> score {
  return evaluate_unnormalized(pos).phase(pos.phase());
}

}  // namespace surveyor
