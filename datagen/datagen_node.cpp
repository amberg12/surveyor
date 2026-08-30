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

#include "datagen_node.h"

#include "../lib/move_generation.h"
#include "common.h"
#include "datagen_manager.h"

namespace surveyor_datagen {

auto node::launch() -> void {
  m_thread = std::jthread([this] {
    this->thread_main();
  });
}

auto node::thread_main() -> void {
  namespace rv = std::views;

  std::vector<std::string> work;

  while (m_manager.requires_games()) {
    work.clear();

    for ([[maybe_unused]] const i32 work_slice : rv::iota(0, 5)) {
      const auto g = generate_game();
      work.emplace_back(g);
    }

    m_manager.submit_work(work);
  }
}

auto node::generate_game() -> std::string {
  namespace rv = std::views;

  constexpr ctrls::search_control verify = ctrls::nodes{.soft_nodes = 50000, .hard_nodes = 8000000};
  constexpr ctrls::search_control search = ctrls::nodes{.soft_nodes = 5000, .hard_nodes = 8000000};

  auto output = std::make_shared<null_output>();

  game g{position::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")};

  auto is_game_over = [&] {
    const move_list ml = generate_moves(g.root());

    return ml.empty();
  };

  // Select a position

  std::string out = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

  for ([[maybe_unused]] const i32 i : rv::iota(0, std::uniform_int_distribution(5, 9)(m_rng))) {
    const move_list ml = generate_moves(g.root());

    if (is_game_over()) {
      return generate_game();
    }

    const move selected_move =
      ml[std::uniform_int_distribution<usize>(usize{0}, ml.size() - 1)(m_rng)];

    g.add_move(selected_move);
    out += std::format(" {} {}", selected_move, 0);
  }

  if (is_game_over()) {
    return generate_game();
  }

  return out;
}

}  // namespace surveyor_datagen
