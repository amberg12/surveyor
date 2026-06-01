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
  const geometry::direction pd = geometry::pawn_direction(stm);

  for (const piece_id pawn_id : pawns) {
    const square src = pos.sq_of(pos.stm(), pawn_id);

    if (auto dst = geometry::shift(src, pd); dst.has_value()) {
      if (pos.has_value(*dst)) {
        continue;
      }

      ml.emplace_back(move::make(src, *dst));

      if (dst->relative_rank(stm) == 2 ) {
        const square dst2 = *geometry::shift(*dst, pd);
        if (pos.has_value(dst2)) {
          continue;
        }

        ml.emplace_back(move::make(src, dst2, move::double_push));
      }
    }
  }
}

auto generate_moves_no_checkers(const position& pos, move_list& ml) {
  const color stm = pos.stm();

  for (const square dst : squares) {
    const piece_mask attackers = pos.attackers_to(stm, dst);

    for (const piece_id id : attackers) {
      if (pos.has_value(dst)) {
        const auto [dst_stm, dst_ptype] = pos.piece_at(dst);

        if (stm == dst_stm) {
          continue;
        }
      }

      // We already check to see if the dst is friendly so no need to do so here.
      const bool capture = pos.has_value(dst);

      const auto src = pos.sq_of(stm, id);
      const auto [src_stm, src_ptype] = pos.piece_at(src);

      if (src_ptype == piece_type::pawn() && !capture) {
        continue;
      }

      if (src_ptype == piece_type::king() && pos.attackers_to(~stm, dst).has_value()) {
        continue;
      }

      if (capture) {
        ml.emplace_back(move::make(src, dst, move::cap_normal));
      } else {
        ml.emplace_back(move::make(src, dst));
      }
    }
  }
}
}

auto generate_moves(const position& pos) -> move_list {
  move_list ml{};

  generate_pawn_moves(pos, ml);
  generate_moves_no_checkers(pos, ml);

  return ml;
}

}  // namespace surveyor
