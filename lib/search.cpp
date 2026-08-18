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

#include "search.h"

#include "game.h"
#include "move_generation.h"
#include "position.h"

#include <print>
#include <thread>

namespace surveyor {

worker::worker(search_shared& shared)
    : m_shared(shared) {
}

auto worker::launch() -> void {
  m_thread = std::jthread([this] {
    this->thread_main();
  });
}

auto worker::thread_main() -> void {
  while (true) {
    switch (m_shared.message) {
    case engine_message::go: {
      begin_search();
    } break;
    case engine_message::idle: {
    } break;
    case engine_message::destroy: {
      return;
    }
    }
  }
}

auto worker::begin_search() -> void {
  const game g = m_shared.g;

  iterative_deepening(g.root());
}

auto worker::iterative_deepening(const position& pos) -> void {
  line last_pv;
  i32  last_depth = -1;

  auto print_info = [&] {
    m_shared.output->info({
      .depth = last_depth,
      .pv    = last_pv,
    });
  };

  for (i32 depth = 1; depth < 255; ++depth) {
    line pv;

    search(pos, pv, 0, depth);

    if (m_shared.stopped) {
      break;
    }

    last_pv = pv;
    last_depth = depth;

    print_info();
  }

  m_shared.halt();

  print_info();
  m_shared.output->best_move(last_pv[0]);
}

auto worker::search(const position& pos, line& pv, i32 ply, i32 depth) -> score {
  if (m_shared.stopped) {
    return 0;
  }

  if (depth == 0) {
    return pos.key() % 1024;
  }

  const move_list ml = generate_moves(pos);

  score best_score = scoring::mated_in(ply);

  for (const move mv : ml) {
    line           child_pv;
    const position child = pos.make_move(mv);

    const score search_score = -search(child, child_pv, ply + 1, depth - 1);

    if (search_score > best_score) {
      pv.clear();
      pv.emplace_back(mv);
      for (const move pv_move : child_pv) {
        pv.emplace_back(pv_move);
      }
    }
  }

  return best_score;
}

}  // namespace surveyor
