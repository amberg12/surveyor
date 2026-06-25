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
#include "see.hpp"
#include "util/math.hpp"

#include <iostream>
#include <thread>

namespace surveyor {

template<search_controls Ctrls>
auto searcher<Ctrls>::begin() -> void {
  iterative_deepening();
}

template<search_controls Ctrls>
auto searcher<Ctrls>::iterative_deepening() -> void {
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

  std::array<search_stack, 300> ss;

  for (m_depth = 1; m_depth < 256; ++m_depth) {
    line pv;

    score s;
    score alpha = -score::inf();
    score beta  = score::inf();
    score delta = 100;

    if (m_depth >= 5) {
      alpha = last_score - delta;
      beta  = last_score + delta;
    }

    while (true) {
      s = search(node_type::pv(), root, pv, alpha, beta, ss.data() + 10, m_depth, 0);

      if (s <= alpha) {
        alpha = -score::inf();
      } else if (s >= beta) {
        beta = score::inf();
      } else {
        break;
      }

      if (m_shared->stopped()) {
        break;
      }
    }

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
auto searcher<Ctrls>::search(node_type       expected,
                             const position& pos,
                             line&           pv,
                             score           alpha,
                             score           beta,
                             search_stack*   ss,
                             i32             depth,
                             i32             ply) -> score {
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
    return quiesce(expected, pos, pv, alpha, beta, ss, ply);
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

  const score static_eval = evaluate(pos);

  // Internal iterative reductions
  if (expected != node_type::all() && depth >= 8 && (!entry || !entry->mv.has_value())) {
    --depth;
  }

  // whole-node pruning is not valid in pv nodes or when in check.
  if (expected != node_type::pv() && !pos.checkers()) {
    // Reverse futility pruning.
    if (static_eval - 128 * depth >= beta && depth <= 6) {
      return static_eval;
    }

    // Null move pruning.
    if (depth >= 3 && static_eval >= beta) {
      const position null_child = make_null_move(pos, ply);
      ss->conthist_subtable     = nullptr;

      const i32 r = 4;

      const score null_score =
        -search(node_type::all(), null_child, pv, -beta, -beta + 1, ss + 1, depth - r, ply + 1);

      unmake_move();

      if (m_shared->stopped()) {
        return 0;
      }

      if (null_score >= beta) {
        // We want to do fail soft, but we also cannot trust mate scores from nmp.
        return null_score.is_mate() ? beta : null_score;
      }
    }
  }

  const move tt_move = entry.has_value() ? entry->mv : move::null();

  move_picker mp{pos, tt_move, m_sd.piece_to, ss};

  score     best_score       = score::none();
  move      best_move        = move::null();
  node_type actual_node_type = node_type::all();
  usize     move_idx         = 0;

  move_list fail_low_quiets{};

  for (move mv = mp.next_move(); mv.has_value(); mv = mp.next_move()) {
    const i32 history = [&] {
      i32 out = 0;

      if (!mv.is_noisy()) {
        out += m_sd.piece_to.read(pos, mv);

        for (const i32 conthist_ply : conthist_plies) {
          if (ss[-conthist_ply].conthist_subtable != nullptr) {
            out += ss[-conthist_ply].conthist_subtable->read(pos, mv);
          }
        }
      }

      return out;
    }();

    if (!best_score.is_losing() && !is_root && !pos.checkers()) {
      // Late move pruning
      if (!mv.is_noisy() && move_idx > 5 + depth * depth) {
        mp.skip_quiet();
        continue;
      }

      // Futility pruning
      if (!mv.is_noisy() && static_eval + 256 + 128 * depth < alpha && abs(alpha) < 2000
          && depth <= 6) {
        mp.skip_quiet();
        continue;
      }

      if (move_idx > 1 && depth <= 4 && history <= -2048 * depth * depth) {
        continue;
      }
    }

    line child_pv;

    ++move_idx;
    const position child = make_move(pos, mv, ply, ss);

    score search_score;

    const i32 new_depth = depth - 1;

    // Late move reductions
    if (depth >= 3 && move_idx > 3) {
      i32 r = 2048 + log2(depth) * log2(move_idx) * 256;

      const i32 lmr_depth = std::clamp(new_depth - r / 1024, 0, new_depth);

      search_score =
        -search(expected.next(), child, child_pv, -alpha - 1, -alpha, ss + 1, lmr_depth, ply + 1);

      if (search_score > alpha && lmr_depth < new_depth) {
        search_score =
          -search(expected.next(), child, child_pv, -alpha - 1, -alpha, ss + 1, new_depth, ply + 1);
      }
    }
    // PV search
    else if (expected != node_type::pv() || (expected == node_type::pv() && move_idx > 1)) {
      search_score =
        -search(expected.next(), child, child_pv, -alpha - 1, -alpha, ss + 1, new_depth, ply + 1);
    }
    // Full Window Search
    if (expected == node_type::pv() && (move_idx == 1 || search_score > alpha)) {
      search_score =
        -search(node_type::pv(), child, child_pv, -beta, -alpha, ss + 1, new_depth, ply + 1);
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

      if (!mv.is_noisy()) {
        m_sd.piece_to.write(pos, mv, bonus(depth));

        for (i32 conthist_ply : conthist_plies) {
          if (ss[-conthist_ply].conthist_subtable) {
            ss[-conthist_ply].conthist_subtable->write(pos, mv, bonus(depth));
          }
        }

        for (const move fail_low : fail_low_quiets) {
          m_sd.piece_to.write(pos, fail_low, malus(depth));

          for (i32 conthist_ply : conthist_plies) {
            if (ss[-conthist_ply].conthist_subtable) {
              ss[-conthist_ply].conthist_subtable->write(pos, fail_low, malus(depth));
            }
          }
        }
      }

      break;
    }

    if (mv != best_move) {
      if (!mv.is_noisy()) {
        fail_low_quiets.emplace_back(mv);
      }
    }
  }

  if (best_score == score::none()) {
    best_score = pos.checkers() ? score::mated_in(ply) : 0;
  }

  m_shared->tt().write(pos, ply, best_move, best_score, depth, actual_node_type);

  return best_score;
}
template<search_controls Ctrls>
auto searcher<Ctrls>::quiesce(node_type       expected,
                              const position& pos,
                              line&           pv,
                              score           alpha,
                              score           beta,
                              search_stack*   ss,
                              i32             ply) -> score {
  m_nodes += 1;
  if (m_shared->stopped() || m_ctrls.hard_stop(m_shared->stats())) {
    m_shared->stop();
    return 0;
  }

  if (m_repetition_table.is_repetition(pos)) {
    return 0;
  }

  const std::optional<tt::entry> entry = m_shared->tt().probe(pos, ply);

  score best_score = pos.checkers() >= 1 ? score::mated_in(ply) : evaluate(pos);
  alpha            = std::max(best_score, alpha);

  if (best_score >= beta) {
    return best_score;
  }

  const move tt_move = entry.has_value() ? entry->mv : move::null();

  move_picker mp{pos, tt_move, m_sd.piece_to, ss};

  if (pos.checkers() == 0) {
    mp.skip_quiet();
  }

  move best_move = move::null();

  for (move mv = mp.next_move(); mv.has_value(); mv = mp.next_move()) {
    line child_pv;

    if (!pos.checkers()) {
      if (see(pos, mv) < -10) {
        continue;
      }
    }

    const position child = make_move(pos, mv, ply, ss);

    const score search_score = -quiesce(expected, child, child_pv, -beta, -alpha, ss + 1, ply + 1);

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
auto searcher<Ctrls>::make_move(const position& pos, move mv, i32 ply, search_stack* ss)
  -> position {
  ss->conthist_subtable = m_sd.conthist.read(pos, mv);

  m_seldepth           = std::max(m_seldepth, ply + 1);
  const position child = pos.make_move(mv);
  m_repetition_table.push(child);
  return child;
}

template<search_controls Ctrls>
auto searcher<Ctrls>::make_null_move(const position& pos, i32 ply) -> position {
  m_seldepth           = std::max(m_seldepth, ply + 1);
  const position child = pos.make_null_move();
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
