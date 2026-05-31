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

#include "move_generation.hpp"

#include "geometry.hpp"

namespace surveyor {
namespace {
auto generate_pawn_moves(const position& pos, move_list& ml) {
  const color stm = pos.stm();
  const piece_mask pawns = pos.ptype_mask(stm, piece_type::pawn());

  for (const piece_id pawn_id : pawns) {
    const square src = pos.sq_of(pos.stm(), pawn_id);

    if (auto dst = geometry::shift(src, geometry::pawn_direction(stm)); dst.has_value()) {
      ml.emplace_back(move::make(src, *dst));
    }
  }
}
}

auto generate_moves(const position& pos) -> move_list {
  move_list ml{};

  generate_pawn_moves(pos, ml);

  return ml;
}

}  // namespace surveyor
