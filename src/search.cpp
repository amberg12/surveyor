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

#include "search.hpp"

#include "evaluate.hpp"
#include "move_generation.hpp"

#include <print>

namespace surveyor {

template<search_controls Ctrls>
auto searcher<Ctrls>::begin() -> void {
  iterative_deepening();
}

template<search_controls Ctrls>
auto searcher<Ctrls>::iterative_deepening() -> void {
  line  last_pv;
  score last_score = score::none();
  i32   last_depth{};
  i32   last_seldepth{};
  nodes last_nodes{};

  time::time_point   start_time = time::clock::now();
  time::milliseconds elapsed{};

  const auto print_line = [&]() {
    const std::string depth_string    = std::format("depth {}", last_depth);
    const std::string seldepth_string = std::format("seldepth {}", last_seldepth);
    const std::string score_string    = [&] {
      if (last_score.is_winning()) {
        return std::format("score mate {}", last_score.plies_to_mate() / 2 + 1);
      }

      if (last_score.is_losing()) {
        return std::format("score mate -{}", last_score.plies_to_mate() / 2 + 1);
      }

      return std::format("score cp {}", last_score);
    }();
    const std::string nodes_string = std::format("nodes {}", last_nodes);
    const std::string nps_string   = std::format("nps {}", time::nps(last_nodes, elapsed));
    const std::string pv_string    = [&] {
      std::string line;

      for (const move& mv : last_pv) {
        line += std::format("{}", mv);

        line += " ";
      }

      return std::format("pv {}", line);
    }();

    std::println("{} {} {} {} {} {}", depth_string, seldepth_string, score_string, nodes_string,
                 nps_string, pv_string);
  };

  for (m_depth = 1; m_depth < 256; ++m_depth) {
    line pv;

    const score s = search(m_shared->root(), pv, m_depth, 0);

    if (m_shared->stopped()) {
      break;
    }

    last_pv       = pv;
    last_score    = s;
    last_depth    = m_depth;
    last_seldepth = m_depth;
    last_nodes    = m_shared->get_nodes();
    elapsed       = time::cast<time::milliseconds>(time::clock::now() - start_time);

    if (m_ctrls.soft_stop(m_shared->stats())) {
      break;
    }
  }

  m_shared->stop();

  print_line();

  std::println("bestmove {}", *last_pv.begin());
}

template<search_controls Ctrls>
auto searcher<Ctrls>::search(const position& pos, line& pv, i32 depth, i32 ply) -> score {
  const bool is_root = ply == 0;

  m_nodes += 1;
  if (m_shared->stopped() || m_ctrls.hard_stop(m_shared->stats())) {
    m_shared->stop();
    return 0;
  }

  if (depth <= 0) {
    return evaluate(pos);
  }

  move_list moves = generate_moves(pos);

  score best_score = score::none();

  for (move mv : moves) {
    line child_pv;

    const position child = pos.make_move(mv);

    const score search_score = -search(child, child_pv, depth - 1, ply + 1);

    if (m_shared->stopped()) {
      return 0;
    }

    if (search_score > best_score) {
      best_score = search_score;

      pv.clear();
      pv.emplace_back(mv);
      for (const move pv_move : child_pv) {
        pv.emplace_back(pv_move);
      }
    }
  }

  if (best_score == score::none()) {
    return pos.checkers() ? score::mated_in(ply) : 0;
  }

  return best_score;
}

auto search_manager::go(search_limits limits) -> void {
  m_stopped = false;

  if (limits.infinite) {
    m_searcher = std::make_unique<searcher<search_ctrls::infinite>>(this);
  } else if (limits.node_limit.has_value()) {
    m_searcher =
      std::make_unique<searcher<search_ctrls::hard_nodes>>(this, limits.node_limit.value());
  } else if (limits.depth.has_value()) {
    m_searcher = std::make_unique<searcher<search_ctrls::depth>>(this, limits.depth.value());
  } else {
    const time::milliseconds t =
      m_pos.stm() == color::white() ? limits.wtime.value() : limits.btime.value();
    const time::milliseconds i =
      m_pos.stm() == color::white() ? limits.winc.value() : limits.binc.value();
    m_searcher = std::make_unique<searcher<search_ctrls::clock>>(this, time::clock::now(), t, i);
  }

  m_searcher->begin();
}

auto search_manager::set_position(position pos) -> void {
  m_pos = pos;
}

template class searcher<search_ctrls::clock>;
template class searcher<search_ctrls::depth>;
template class searcher<search_ctrls::hard_nodes>;
template class searcher<search_ctrls::infinite>;

}  // namespace surveyor
