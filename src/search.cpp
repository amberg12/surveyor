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
  score last_score = scoring::none;
  i32   last_depth{};
  i32   last_seldepth{};
  nodes last_nodes{};

  time::time_point   start_time = time::clock::now();
  time::milliseconds elapsed{};

  const auto print_line = [&]() {
    const std::string depth_string    = std::format("depth {}", last_depth);
    const std::string seldepth_string = std::format("seldepth {}", last_seldepth);
    const std::string score_string    = [&] {
      if (scoring::is_winning(last_score)) {
        return std::format("score mate {}", scoring::plies_to_mate(last_score) / 2 + 1);
      }

      if (scoring::is_losing(last_score)) {
        return std::format("score mate {}", scoring::plies_to_mate(last_score) / 2 - 1);
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
    score alpha = -scoring::inf;
    score beta  = scoring::inf;
    score delta = 25;

    if (m_depth >= 5) {
      alpha = last_score - delta;
      beta  = last_score + delta;
    }

    while (true) {
      s = search(node_type::pv(), root, pv, alpha, beta, ss.data() + 10, m_depth, 0);

      if (s <= alpha) {
        alpha = std::max(-scoring::inf, alpha - delta);
      } else if (s >= beta) {
        beta = std::min(static_cast<i32>(scoring::inf), beta + delta);
      } else {
        break;
      }

      if (m_shared->stopped()) {
        break;
      }

      delta += delta;
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
  const bool is_root  = ply == 0;
  const bool singular = ss->excluded.has_value();
  ss[1].clear_killers();

  if (m_shared->stopped() || m_ctrls.hard_stop(m_shared->stats())) {
    m_shared->stop();
    return 0;
  }

  if (depth <= 0) {
    return quiesce(expected, pos, pv, alpha, beta, ss, ply);
  }

  m_nodes += 1;

  if (!is_root) {
    if (const auto sc = pos.move_rule(ply)) {
      return *sc;
    }

    if (m_repetition_table.is_repetition(pos)) {
      return 0;
    }
  }

  std::optional<tt::entry> entry = singular ? std::nullopt : m_shared->tt().probe(pos, ply);

  if (!singular && expected != node_type::pv() && entry.has_value() && entry->depth >= depth &&
      [&] {
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

  const score raw_eval = [&] -> score {
    if (pos.checkers()) {
      return scoring::none;
    }

    if (entry.has_value() && entry->raw_eval != scoring::none) {
      return entry->raw_eval;
    }

    return evaluate(pos);
  }();

  const score static_eval = [&] -> score {
    if (pos.checkers()) {
      return scoring::none;
    }

    return raw_eval + m_sd.corrhist.read(pos);
  }();

  ss->static_eval = static_eval;
  ss->raw_eval    = raw_eval;

  const bool improving = [&] {
    if (pos.checkers()) {
      return false;
    }

    if (ply >= 2 && ss[-2].static_eval != scoring::none) {
      return static_eval > ss[-2].static_eval;
    }

    if (ply >= 4 && ss[-4].static_eval != scoring::none) {
      return static_eval > ss[-4].static_eval;
    }

    return false;
  }();

  // Internal iterative reductions
  if (!singular && expected != node_type::all() && depth >= 8
      && (!entry || !entry->mv.has_value())) {
    --depth;
  }

  // whole-node pruning is not valid in pv nodes, singular searches or when in check.
  if (!singular && expected != node_type::pv() && !pos.checkers()) {
    // Reverse futility pruning.
    if (static_eval >= beta + 128 * depth - 96 * improving && depth <= 6) {
      return static_eval;
    }

    // Null move pruning.
    if (depth >= 3 && static_eval >= beta) {
      const position null_child = make_null_move(pos, ply);
      ss->conthist_subtable     = nullptr;

      const i32 r = 3 + depth / 4 + std::min((static_eval - beta) / 250, 3);

      const score null_score =
        -search(node_type::all(), null_child, pv, -beta, -beta + 1, ss + 1, depth - r, ply + 1);

      unmake_move();

      if (m_shared->stopped()) {
        return 0;
      }

      if (null_score >= beta) {
        // We want to do fail soft, but we also cannot trust mate scores from nmp.
        return scoring::is_mate(null_score) ? beta : null_score;
      }
    }
  }

  const move tt_move = entry.has_value() ? entry->mv : move::null();

  move_picker mp{pos, tt_move, m_sd.piece_to, m_sd.capthist, ss, -250};

  score     best_score       = scoring::none;
  move      best_move        = move::null();
  node_type actual_node_type = node_type::all();
  usize     move_idx         = 0;

  move_list fail_low_quiets{};
  move_list fail_low_noisies{};

  for (move mv = mp.next_move(); mv.has_value(); mv = mp.next_move()) {
    if (mv == ss->excluded) {
      continue;
    }

    const i32 history = [&] {
      i32 out = 0;

      if (mv.is_noisy()) {
        out += m_sd.capthist.read(pos, mv);
      } else {
        out += m_sd.piece_to.read(pos, mv);

        for (const i32 conthist_ply : conthist_plies) {
          if (ss[-conthist_ply].conthist_subtable != nullptr) {
            out += ss[-conthist_ply].conthist_subtable->read(pos, mv);
          }
        }
      }

      return out;
    }();

    if (!scoring::is_losing(best_score) && !is_root && !pos.checkers()) {
      // Late move pruning
      if (!mv.is_noisy() && move_idx > (5 + depth * depth) / (2 - improving)) {
        mp.skip_quiet();
        continue;
      }

      // Futility pruning
      if (!mv.is_noisy() && static_eval + 256 + 128 * depth < alpha && abs(alpha) < 2000
          && depth <= 6) {
        mp.skip_quiet();
        continue;
      }

      // Noisy history pruning
      if (mv.is_noisy() && depth <= 4 && history <= -2560 * depth * depth) {
        continue;
      }

      // Quiet history pruning
      if (!mv.is_noisy() && depth <= 4 && history <= -2048 * depth * depth) {
        continue;
      }

      // See pruning
      if (depth <= 6 && see(pos, mv) <= (mv.is_noisy() ? -128 * depth : -96 * depth)) {
        continue;
      }
    }

    i32 extensions = 0;

    // Singular extensions
    if (!is_root && depth >= 9 && entry.has_value() && entry->node() != node_type::all()
        && entry->depth >= depth - 3 && mv == entry->mv) {
      line singular_pv;

      const score singular_beta = std::max(scoring::min, static_cast<score>(entry->sc - 2 * depth));
      const i32   singular_depth = (depth - 1) / 2;

      ss->excluded = mv;

      const score singular_score = search(expected.narrow(), pos, singular_pv, singular_beta - 1,
                                          singular_beta, ss, singular_depth, ply);

      ss->excluded = move::null();

      // Multicut
      if (singular_score >= singular_beta && singular_beta >= beta) {
        return singular_beta;
      }

      // Extend based on how singular the move is.
      if (singular_score < singular_beta) {
        extensions = 1;

        extensions += expected != node_type::pv() && singular_score < singular_beta - 20;
      }
      // Negative extensions
      else if (entry->sc >= beta) {
        extensions = -3;
      }
    }

    line child_pv;

    ++move_idx;
    const position child = make_move(pos, mv, ply, ss);
    m_shared->tt().prefetch(child);

    score search_score;

    const i32 new_depth = depth + extensions - 1;

    // Late move reductions
    if (depth >= 3 && move_idx > 3) {
      i32 r = 2048 + log2(depth) * log2(move_idx) * 256;

      r -= mv.is_noisy() ? 0 : 64 * history / 1024;

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

      if (mv.is_noisy()) {
        m_sd.capthist.write(pos, mv, bonus(depth));
      } else {
        ss->add_killer(mv);

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

      for (const move fail_low : fail_low_noisies) {
        m_sd.capthist.write(pos, fail_low, malus(depth));
      }

      break;
    }

    if (mv != best_move) {
      if (mv.is_noisy()) {
        fail_low_noisies.emplace_back(mv);
      } else {
        fail_low_quiets.emplace_back(mv);
      }
    }
  }

  if (best_score == scoring::none) {
    best_score = singular ? alpha : pos.checkers() ? scoring::mated_in(ply) : 0;
  }

  if (!singular) {
    if (!pos.checkers() && !best_move.is_noisy()
        && !(actual_node_type == node_type::all() && best_score >= static_eval)
        && !(actual_node_type == node_type::cut() && best_score <= static_eval)
        && !scoring::is_mate(best_score)) {
      m_sd.corrhist.update(pos, depth, static_eval, best_score);
    }

    m_shared->tt().write(pos, ply, best_move, best_score, raw_eval, depth, actual_node_type);
  }

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

  if (const auto sc = pos.move_rule(ply)) {
    // We do not trust any mate scores from qsearch, so we always return 0.
    return 0;
  }

  const std::optional<tt::entry> entry = m_shared->tt().probe(pos, ply);

  // TT Cutoffs
  if (expected != node_type::pv() && entry.has_value() && [&] {
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

  const score raw_eval = [&] {
    if (pos.checkers()) {
      return scoring::none;
    }

    if (entry.has_value() && entry->raw_eval != scoring::none) {
      return entry->raw_eval;
    }

    return evaluate(pos);
  }();

  const score static_eval = [&] -> score {
    if (pos.checkers()) {
      return scoring::none;
    }

    return raw_eval + m_sd.corrhist.read(pos);
  }();

  score best_score = [&] -> score {
    if (pos.checkers()) {
      return scoring::mated_in(ply);
    }

    return static_eval;
  }();

  alpha = std::max(best_score, alpha);

  if (best_score >= beta) {
    return best_score;
  }

  const move tt_move = entry.has_value() ? entry->mv : move::null();

  move_picker mp{pos, tt_move, m_sd.piece_to, m_sd.capthist, ss};

  if (pos.checkers() == 0) {
    mp.skip_quiet();
  }

  move best_move = move::null();
  i32  move_idx  = 0;

  for (move mv = mp.next_move(); mv.has_value(); mv = mp.next_move()) {
    line child_pv;

    if (!scoring::is_losing(best_score)) {
      // Late move pruning
      if (move_idx >= 3) {
        break;
      }

      const i32 see_score = see(pos, mv);

      if (!pos.checkers()) {
        // See pruning
        if (see_score < -10) {
          continue;
        }
      }

      if (const score futility = static_eval + 128;
          !scoring::is_mate(alpha) && futility < alpha && see_score <= 0) {
        best_score = std::max(best_score, futility);
        continue;
      }
    }

    ++move_idx;
    const position child = make_move(pos, mv, ply, ss);
    m_shared->tt().prefetch(child);

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
  ss[1].raw_eval = scoring::none;

  m_seldepth           = std::max(m_seldepth, ply + 1);
  const position child = pos.make_move(mv);
  m_repetition_table.push(child);
  return child;
}

template<search_controls Ctrls>
auto searcher<Ctrls>::make_null_move(const position& pos, i32 ply) -> position {
  m_seldepth           = std::max(m_seldepth, ply + 1);
  const position child = pos.make_null_move();
  m_shared->tt().prefetch(child);

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
