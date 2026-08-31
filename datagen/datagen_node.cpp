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
constexpr i32 max_game_plies = 300;

auto stamp_start_time(ctrls::ctrls limits) -> ctrls::ctrls {
  std::visit(
    [](auto& x) {
      x.start_time = time::clock::now();
    },
    limits);

  return limits;
}
}  // namespace

struct node::extractor : public engine_output {
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

node::node(i32 id, manager& m)
    : m_manager(m) {
  m_rng.seed(id * 0x8008153);

  m_a_extractor = std::make_shared<extractor>();
  m_b_extractor = std::make_shared<extractor>();

  m_engine_a = std::make_unique<engine>();
  m_engine_b = std::make_unique<engine>();

  m_engine_a->resize_hash(1);
  m_engine_b->resize_hash(1);

  m_engine_a->set_output(m_a_extractor);
  m_engine_b->set_output(m_b_extractor);
}

node::~node() = default;

auto node::launch() -> void {
  m_thread = std::jthread([this] {
    this->thread_main();
  });
}

auto node::join() -> void {
  if (m_thread.joinable()) {
    m_thread.join();
  }
}

auto node::thread_main() -> void {
  namespace rv = std::views;

  std::vector<std::string> work;

  while (m_manager.requires_games()) {
    work.clear();

    for ([[maybe_unused]] const i32 work_slice : rv::iota(0, 4)) {
      if (!m_manager.requires_games()) {
        break;
      }

      work.emplace_back(generate_game());
    }

    if (!work.empty()) {
      m_manager.submit_work(work);
    }
  }
}

auto node::generate_game() -> std::string {
  namespace rv = std::views;

  constexpr ctrls::ctrls verify = ctrls::nodes{.soft_nodes = 20000, .hard_nodes = 8000000};
  constexpr ctrls::ctrls search = ctrls::nodes{.soft_nodes = 5000, .hard_nodes = 8000000};

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

  for ([[maybe_unused]] const i32 attempt : rv::iota(0, 32)) {
    g = game{position::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")};

    std::string out = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    bool restart = false;

    for ([[maybe_unused]] const i32 i : rv::iota(0, std::uniform_int_distribution(5, 9)(m_rng))) {
      const move_list ml = generate_moves(g.root());

      if (ml.empty() || is_game_over()) {
        restart = true;
        break;
      }

      const move selected_move =
        ml[std::uniform_int_distribution<usize>(usize{0}, ml.size() - 1)(m_rng)];

      g.add_move(selected_move);
      out += std::format(" {} {}", selected_move, 0);
    }

    if (restart || is_game_over()) {
      continue;
    }

    m_a_extractor->reset();

    m_engine_a->go(g, stamp_start_time(verify));
    m_engine_a->await();

    if (std::abs(m_a_extractor->sc) > 200) {
      continue;
    }

    m_a_extractor->reset();
    m_b_extractor->reset();

    for (i32 ply = 0; ply < max_game_plies; ++ply) {
      if (is_game_over()) {
        return std::format("{} {}", game_result(), out);
      }

      m_engine_a->go(g, stamp_start_time(search));
      m_engine_a->await();

      if (is_game_over()) {
        return std::format("{} {}", game_result(), out);
      }

      g.add_move(m_a_extractor->bm);
      out += std::format(" {} {}", m_a_extractor->bm, m_a_extractor->sc);
      m_a_extractor->reset();

      if (is_game_over()) {
        return std::format("{} {}", game_result(), out);
      }

      m_engine_b->go(g, stamp_start_time(search));
      m_engine_b->await();

      if (is_game_over()) {
        return std::format("{} {}", game_result(), out);
      }

      g.add_move(m_b_extractor->bm);
      out += std::format(" {} {}", m_b_extractor->bm, m_b_extractor->sc);
      m_b_extractor->reset();
    }

    return std::format("{} {}", game_result(), out);
  }

  return std::format("{} rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", game_result());
}

}  // namespace surveyor_datagen
