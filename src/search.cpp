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
#include "move_picker.hpp"

#include <iostream>
#include <thread>

namespace surveyor {

template<search_controls Ctrls>
auto searcher<Ctrls>::begin() -> void {
  iterative_deepening();
}

template<search_controls Ctrls>
auto searcher<Ctrls>::iterative_deepening() -> void {
  m_sd = {};  // TODO: remove when maluses are done

  auto [root, repetitions] = m_shared->root();
  m_repetition_table       = repetitions;

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
    const std::string nodes_string    = std::format("nodes {}", last_nodes);
    const std::string nps_string      = std::format("nps {}", time::nps(last_nodes, elapsed));
    const std::string hashfull_string = std::format("hashfull {}", m_shared->tt().hashfull());
    const std::string pv_string       = [&] {
      std::string line;

      for (const move& mv : last_pv) {
        line += std::format("{}", mv);

        line += " ";
      }

      return std::format("pv {}", line);
    }();

    std::cout << "info " << depth_string << " " << seldepth_string << " " << score_string << " "
              << nodes_string << " " << nps_string << " " << hashfull_string << " " << pv_string
              << '\n';
  };

  for (m_depth = 1; m_depth < 256; ++m_depth) {
    line pv;

    const score s = search(node_type::pv(), root, pv, -score::inf(), score::inf(), m_depth, 0);

    if (m_shared->stopped()) {
      break;
    }

    last_pv       = pv;
    last_score    = s;
    last_depth    = m_depth;
    last_seldepth = m_seldepth;
    last_nodes    = m_shared->get_nodes();
    elapsed       = time::cast<time::milliseconds>(time::clock::now() - start_time);

    if (m_ctrls.soft_stop(m_shared->stats())) {
      break;
    }
  }

  m_shared->stop();

  print_line();

  std::cout << "bestmove " << std::format("{}", *last_pv.begin()) << '\n' << std::flush;
}

template<search_controls Ctrls>
auto searcher<Ctrls>::search(
  node_type expected, const position& pos, line& pv, score alpha, score beta, i32 depth, i32 ply)
  -> score {
  const bool is_root = ply == 0;

  m_nodes += 1;
  if (m_shared->stopped() || m_ctrls.hard_stop(m_shared->stats())) {
    m_shared->stop();
    return 0;
  }

  if (!is_root) {
    if (m_repetition_table.is_repetition(pos)) {
      return 0;
    }
  }


  if (depth <= 0) {
    return quiesce(expected, pos, pv, alpha, beta, ply);
  }

  std::optional<tt::entry> entry = m_shared->tt().probe(pos, ply);

  if (expected != node_type::pv() && entry.has_value() && entry->depth >= depth && [&] {
        if (entry->node() == node_type::pv()) {
          return true;
        }

        if (entry->node() == node_type::all()) {
          return entry->sc <= alpha;
        }

        if (entry->node() == node_type::cut()) {
          return entry->sc >= beta;
        }

        return false;
      }()) {
    return entry->sc;
  }

  const move tt_move = entry.has_value() ? entry->mv : move::null();

  move_picker mp{pos, tt_move, m_sd.piece_to};

  score     best_score       = score::none();
  move      best_move        = move::null();
  node_type actual_node_type = node_type::all();
  usize     move_idx         = 0;

  move_list fail_low_quiets{};

  for (move mv = mp.next_move(); mv.has_value(); mv = mp.next_move()) {
    line child_pv;

    ++move_idx;
    const position child = make_move(pos, mv, ply);

    score search_score;
    if (expected != node_type::pv() || (expected == node_type::pv() && move_idx > 1)) {
      search_score =
        -search(expected.next(), child, child_pv, -alpha - 1, -alpha, depth - 1, ply + 1);
    }

    if (expected == node_type::pv() && (move_idx == 1 || search_score > alpha)) {
      search_score = -search(node_type::pv(), child, child_pv, -beta, -alpha, depth - 1, ply + 1);
    }

    unmake_move();

    if (m_shared->stopped()) {
      return 0;
    }

    if (search_score > best_score) {
      best_score = search_score;
    }

    if (search_score > alpha) {
      actual_node_type = node_type::pv();
      alpha            = search_score;
      best_move        = mv;

      pv.clear();
      pv.emplace_back(mv);
      for (const move pv_move : child_pv) {
        pv.emplace_back(pv_move);
      }
    }

    if (search_score >= beta) {
      actual_node_type = node_type::cut();

      m_sd.piece_to.write(pos, mv, bonus(depth));

      break;
    }
  }

  if (best_score == score::none()) {
    best_score = pos.checkers() ? score::mated_in(ply) : 0;
  }

  m_shared->tt().write(pos, ply, best_move, best_score, depth, actual_node_type);

  return best_score;
}
template<search_controls Ctrls>
auto searcher<Ctrls>::quiesce(
  node_type expected, const position& pos, line& pv, score alpha, score beta, i32 ply) -> score {
  m_nodes += 1;
  if (m_shared->stopped() || m_ctrls.hard_stop(m_shared->stats())) {
    m_shared->stop();
    return 0;
  }

  if (m_repetition_table.is_repetition(pos)) {
    return 0;
  }

  score best_score = pos.checkers() >= 1 ? score::mated_in(ply) : evaluate(pos);
  alpha            = std::max(best_score, alpha);

  if (best_score >= beta) {
    return best_score;
  }

  move_picker mp{pos, move::null(), m_sd.piece_to};

  if (pos.checkers() == 0) {
    mp.skip_quiet();
  }

  move best_move = move::null();

  for (move mv = mp.next_move(); mv.has_value(); mv = mp.next_move()) {
    line child_pv;

    const position child = make_move(pos, mv, ply);

    const score search_score = -quiesce(expected, child, child_pv, -beta, -alpha, ply + 1);

    unmake_move();

    if (m_shared->stopped()) {
      return 0;
    }

    if (search_score > best_score) {
      best_score = search_score;
    }

    if (search_score > alpha) {
      alpha     = search_score;
      best_move = mv;

      pv.clear();
      pv.emplace_back(mv);
      for (const move pv_move : child_pv) {
        pv.emplace_back(pv_move);
      }
    }

    if (search_score >= beta) {
      break;
    }
  }

  return best_score;
}

template<search_controls Ctrls>
auto searcher<Ctrls>::make_move(const position& pos, move mv, i32 ply) -> position {
  m_seldepth     = std::max(m_seldepth, ply + 1);
  position child = pos.make_move(mv);
  m_repetition_table.push(child);
  return child;
}

template<search_controls Ctrls>
auto searcher<Ctrls>::unmake_move() -> void {
  m_repetition_table.pop();
}

auto search_manager::go(search_limits limits) -> void {
  m_tt.age();

  m_thread = std::jthread([limits, this] {
    m_stopped = false;

    if (limits.infinite) {
      m_searcher = std::make_unique<searcher<search_ctrls::infinite>>(this, m_sd);
    } else if (limits.node_limit.has_value()) {
      m_searcher =
        std::make_unique<searcher<search_ctrls::hard_nodes>>(this, m_sd, limits.node_limit.value());
    } else if (limits.depth.has_value()) {
      m_searcher =
        std::make_unique<searcher<search_ctrls::depth>>(this, m_sd, limits.depth.value());
    } else {
      const time::milliseconds t =
        m_pos.stm() == color::white() ? limits.wtime.value() : limits.btime.value();
      const time::milliseconds i =
        m_pos.stm() == color::white() ? limits.winc.value() : limits.binc.value();
      m_searcher =
        std::make_unique<searcher<search_ctrls::clock>>(this, m_sd, time::clock::now(), t, i);
    }

    m_searcher->begin();
  });
}

auto search_manager::set_position(position pos, repetition_table repetitions) -> void {
  m_pos         = pos;
  m_repetitions = repetitions;
}

template class searcher<search_ctrls::clock>;
template class searcher<search_ctrls::depth>;
template class searcher<search_ctrls::hard_nodes>;
template class searcher<search_ctrls::infinite>;

}  // namespace surveyor
