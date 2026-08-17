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

#include "perft.h"

#include "move_generation.h"

#include <print>

namespace surveyor::perft {

auto standard(const position& pos, i32 depth, bool print_info) -> u64 {
  if (depth == 0) {
    return 1;
  }

  const move_list legal_moves = generate_moves(pos);

  u64 total_nodes = 0;

  for (const auto mv : legal_moves) {
    const position child = pos.make_move(mv);

    const u64 leaf_nodes = standard(child, depth - 1, false);

    if (print_info) {
      std::println("{}: {}", mv, leaf_nodes);
    }

    total_nodes += leaf_nodes;
  }

  return total_nodes;
}

}  // namespace surveyor::perft
