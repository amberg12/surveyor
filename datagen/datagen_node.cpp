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

#include <iostream>
#include <print>

namespace surveyor_datagen {
namespace {
class extractor : public engine_output {
public:
  score sc{};
  move  bm{};

  auto info(info_line info) -> void override {
    sc = info.sc;
  }

  auto best_move(move mv) -> void override {
    bm = mv;
  }

  auto reset() -> void {
    sc = scoring::none;
    bm = move::null();
  }
};
}  // namespace

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

    for ([[maybe_unused]] const i32 work_slice : rv::iota(0, 1)) {
      const auto g = generate_game();
      work.emplace_back(g);
    }

    m_manager.submit_work(work);
  }
}

auto node::generate_game() -> std::string {
  namespace rv = std::views;
  namespace rg = std::ranges;

  constexpr ctrls::ctrls verify = ctrls::nodes{.soft_nodes = 50000, .hard_nodes = 8000000};
  constexpr ctrls::ctrls search = ctrls::nodes{.soft_nodes = 5000, .hard_nodes = 8000000};

  auto output = std::make_shared<null_output>();

  game g{position::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")};

  auto game_result = [&]() -> double {
    const position& pos = g.root();
    const move_list ml  = generate_moves(pos);

    if (ml.empty()) {
      if (pos.checkers() != 0) {
        return pos.stm() == color::white() ? 0.0 : 1.0;
      }

      return 0.5;
    }

    return 0.5;
  };

  auto is_game_over = [&] {
    g.set_uci_line();
    const move_list ml = generate_moves(g.root());

    return ml.empty() || g.repetition_table().is_threefold_repetition(g.root());
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

  engine a;
  engine b;

  auto a_e = std::make_shared<extractor>();
  auto b_e = std::make_shared<extractor>();

  a.set_output(a_e);
  b.set_output(b_e);

  // Verify exit
  a.go(g, verify);
  a.await();

  if (std::abs(a_e->sc) > 200) {
    return generate_game();
  }

  a_e->reset();

  while (true) {
    a.go(g, search);
    a.await();

    if (is_game_over()) {
      break;
    }

    g.add_move(a_e->bm);
    out += std::format(" {} {}", a_e->bm, a_e->sc);
    a_e->reset();

    b.go(g, search);
    b.await();

    if (is_game_over()) {
      break;
    }

    g.add_move(b_e->bm);
    out += std::format(" {} {}", b_e->bm, b_e->sc);
    b_e->reset();
  }

  return std::format("{} {}", game_result(), out);
}

}  // namespace surveyor_datagen
