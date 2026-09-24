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
auto evaluate_pieces(color stm, const position& pos) -> pair {
  pair out{};

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

auto evaluate_threats(color stm, const position& pos) -> pair {
  pair out{};

  for (const piece_id id : pos.ptype_mask(stm, piece_type::knight())) {
    const bitboard attack_bb = pos.threat_bb(stm, id);
    const i32 mobility = (attack_bb & ~pos.bb()).ipopcount();

    out += knight_mobility[mobility];
  }

  for (const piece_id id : pos.ptype_mask(stm, piece_type::bishop())) {
    const bitboard attack_bb = pos.threat_bb(stm, id);
    const i32 mobility = (attack_bb & ~pos.bb()).ipopcount();

    out += bishop_mobility[mobility];
  }

  for (const piece_id id : pos.ptype_mask(stm, piece_type::rook())) {
    const bitboard attack_bb = pos.threat_bb(stm, id);
    const i32 mobility = (attack_bb & ~pos.bb()).ipopcount();

    out += rook_mobility[mobility];
  }

  for (const piece_id id : pos.ptype_mask(stm, piece_type::queen())) {
    const bitboard attack_bb = pos.threat_bb(stm, id);
    const i32 mobility = (attack_bb & ~pos.bb()).ipopcount();

    out += queen_mobility[mobility];
  }

  return out;
}

}

auto evaluate_unnormalized(const position& pos) -> pair {
  pair out{};

  out += evaluate_pieces(color::white(), pos);
  out -= evaluate_pieces(color::black(), pos);

  out += evaluate_threats(color::white(), pos);
  out -= evaluate_threats(color::black(), pos);

  return pos.stm() == color::white() ? out : -out;
}

auto evaluate(const position& pos) -> score {
  return evaluate_unnormalized(pos).phase(pos.phase());
}

}  // namespace surveyor
