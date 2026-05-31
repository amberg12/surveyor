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
#include "move.hpp"
#include "position.hpp"
#include "util/static_vector.hpp"

#include <print>

namespace surveyor {

using move_list = static_vector<move, 256>;

auto generate_moves(const position& pos) -> move_list;

enum class perft_settings {
  bulk,
  standard,
};

template <perft_settings ps, bool is_root = true>
constexpr auto perft(const position& pos, i32 depth) -> u64 {
  if (depth <= 0) {
    return 1;
  }

  const move_list ml = generate_moves(pos);

  if (!is_root && ps == perft_settings::bulk && depth == 1) {
    return ml.size();
  }

  u64 nodes = 0;

  for (const move mv : ml) {
    const position child = pos.make_move(mv);
    const u64 child_nodes = perft<ps, false>(child, depth - 1);

    if constexpr (is_root) {
      std::println("{}: {}", mv, child_nodes);
    }

    nodes += child_nodes;
  }

  if constexpr (is_root) {
    std::println("nodes: {}", nodes);
  }

  return nodes;
}

}  // namespace surveyor
