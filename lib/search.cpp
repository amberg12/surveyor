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

#include "evaluate.h"
#include "game.h"
#include "move_generation.h"
#include "move_picker.h"
#include "position.h"
#include "util/math.h"

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

auto worker::nodes() -> u64 {
  return m_nodes;
}

auto worker::reset() -> void {
  m_corrhist = {};
  m_capthist = {};
  m_conthist = {};
  m_piece_to = {};
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

  m_repetition_table = g.repetition_table();
  m_nodes            = 0;

  if (std::holds_alternative<ctrls::infinite>(m_shared.ctrls)) {
    iterative_deepening<ctrls::infinite>(g.root());
  }

  if (std::holds_alternative<ctrls::nodes>(m_shared.ctrls)) {
    iterative_deepening<ctrls::nodes>(g.root());
  }

  if (std::holds_alternative<ctrls::fixed_time>(m_shared.ctrls)) {
    iterative_deepening<ctrls::fixed_time>(g.root());
  }

  if (std::holds_alternative<ctrls::depth>(m_shared.ctrls)) {
    iterative_deepening<ctrls::depth>(g.root());
  }

  if (std::holds_alternative<ctrls::clock>(m_shared.ctrls)) {
    iterative_deepening<ctrls::clock>(g.root());
  }
}

auto worker::make_move(
  const position& pos, const position& child, move mv, i32 ply, search_stack* ss) -> void {
  m_shared.tt.prefetch(child);
  m_repetition_table.push(child);

  ss[1].raw_eval    = scoring::none;
  ss[1].static_eval = scoring::none;

  ss->conthist_subtable = m_conthist.read(pos, mv);

  m_shared.tt.prefetch(child);
}

auto worker::make_null_move(const position& child, i32 ply, search_stack* ss) -> void {
  m_shared.tt.prefetch(child);
  m_repetition_table.push(child);
  ss->conthist_subtable = nullptr;
}

auto worker::unmake_move() -> void {
  m_repetition_table.pop();
}

template<typename Ctrls>
auto worker::iterative_deepening(const position& pos) -> void {
  Ctrls ctrls = std::get<Ctrls>(m_shared.ctrls);

  i32   last_depth = -1;
  score last_score = scoring::none;
  line  last_pv;

  auto print_info = [&] {
    m_shared.output->info({
      .depth   = last_depth,
      .sc      = last_score,
      .elapsed = ctrls.elapsed(),
      .nodes   = m_nodes,
      .pv      = last_pv,
    });
  };

  std::array<search_stack, 300> ss;

  for (i32 depth = 1; depth < 255; ++depth) {
    line pv;

    score sc;
    score alpha = -scoring::inf;
    score beta  = scoring::inf;
    score delta = 25;

    if (depth >= 5) {
      alpha = std::max<score>(-scoring::inf, last_score - delta);
      beta  = std::min<score>(scoring::inf, last_score + delta);
    }

    while (true) {
      sc = search<Ctrls>(ctrls, node_type::pv(), pos, pv, alpha, beta, 0, depth, ss.data() + 10);

      if (sc <= alpha) {
        alpha = std::max<score>(-scoring::inf, alpha - delta);
      } else if (sc >= beta) {
        beta = std::min<score>(scoring::inf, beta + delta);
      } else {
        break;
      }

      if (m_shared.stopped) {
        break;
      }

      delta += delta;
    }

    if (m_shared.stopped) {
      break;
    }

    last_depth = depth;
    last_score = sc;
    last_pv    = pv;

    if (ctrls.soft_limit(m_nodes, depth)) {
      break;
    }

    print_info();
  }

  // Emergency Move-Picker
  if (last_pv.empty()) {
    last_depth = 0;

    const std::optional<tt::entry> entry = m_shared.tt.probe(pos, 0);

    const move tt_move = entry.has_value() ? entry->mv : move::null();

    move_picker mp{pos, tt_move, m_piece_to, m_capthist, ss.data() + 10, -250};
    last_pv.emplace_back(mp.next_move());

    if (entry.has_value()) {
      last_score = entry->sc;
    } else {
      const position child = pos.make_move(last_pv[0]);
      last_score = evaluate(child);
    }
  }

  m_shared.halt();
  print_info();
  m_shared.output->best_move(last_pv[0]);
}

template<typename Ctrls>
auto worker::search(Ctrls&          ctrls,
                    node_type       expected,
                    const position& pos,
                    line&           pv,
                    score           alpha,
                    score           beta,
                    i32             ply,
                    i32             depth,
                    search_stack*   ss) -> score {
  const bool is_root  = ply == 0;
  const bool singular = ss->excluded.has_value();
  ss[1].clear_killers();

  if (m_shared.stopped || ctrls.hard_limit(m_nodes, ply)) {
    m_shared.stopped = true;
    return 0;
  }

  if (depth <= 0) {
    return quiesce<Ctrls>(ctrls, expected, pos, pv, alpha, beta, ply, ss);
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

  std::optional<tt::entry> entry = singular ? std::nullopt : m_shared.tt.probe(pos, ply);

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

    return raw_eval + m_corrhist.read(pos);
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
      line null_pv;

      const position null_child = pos.make_null_move();
      make_null_move(null_child, ply, ss);
      ss->conthist_subtable = nullptr;

      const i32 r = 3 + depth / 4 + std::min((static_eval - beta) / 250, 3);

      const score null_score = -search(ctrls, node_type::all(), null_child, null_pv, -beta,
                                       -beta + 1, ply + 1, depth - r, ss + 1);

      unmake_move();

      if (m_shared.stopped) {
        return 0;
      }

      if (null_score >= beta) {
        // We want to do fail soft, but we also cannot trust mate scores from nmp.
        return scoring::is_mate(null_score) ? beta : null_score;
      }
    }
  }

  const move tt_move = entry.has_value() ? entry->mv : move::null();

  move_picker mp{pos, tt_move, m_piece_to, m_capthist, ss, -250};

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
        out += m_capthist.read(pos, mv);
      } else {
        out += m_piece_to.read(pos, mv);

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

      const score singular_score =
        search(ctrls, expected.narrow(), pos, singular_pv, singular_beta - 1, singular_beta, ply,
               singular_depth, ss);

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

    const position child = pos.make_move(mv);
    make_move(pos, child, mv, ply, ss);

    score search_score;

    const i32 new_depth = depth + extensions - 1;

    // Late move reductions
    if (depth >= 3 && move_idx > 3) {
      i32 r = 2048 + log2(depth) * log2(move_idx) * 256;

      r -= mv.is_noisy() ? 0 : 64 * history / 1024;

      const i32 lmr_depth = std::clamp(new_depth - r / 1024, 0, new_depth);

      search_score = -search(ctrls, expected.next(), child, child_pv, -alpha - 1, -alpha, ply + 1,
                             lmr_depth, ss + 1);

      if (search_score > alpha && lmr_depth < new_depth) {
        search_score = -search(ctrls, expected.next(), child, child_pv, -alpha - 1, -alpha, ply + 1,
                               new_depth, ss + 1);
      }
    }
    // PV search
    else if (expected != node_type::pv() || (expected == node_type::pv() && move_idx > 1)) {
      search_score = -search(ctrls, expected.next(), child, child_pv, -alpha - 1, -alpha, ply + 1,
                             new_depth, ss + 1);
    }
    // Full Window Search
    if (expected == node_type::pv() && (move_idx == 1 || search_score > alpha)) {
      search_score =
        -search(ctrls, node_type::pv(), child, child_pv, -beta, -alpha, ply + 1, new_depth, ss + 1);
    }

    unmake_move();

    if (m_shared.stopped) {
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
        m_capthist.write(pos, mv, bonus(depth));
      } else {
        ss->add_killer(mv);

        m_piece_to.write(pos, mv, bonus(depth));

        for (i32 conthist_ply : conthist_plies) {
          if (ss[-conthist_ply].conthist_subtable) {
            ss[-conthist_ply].conthist_subtable->write(pos, mv, bonus(depth));
          }
        }

        for (const move fail_low : fail_low_quiets) {
          m_piece_to.write(pos, fail_low, malus(depth));

          for (i32 conthist_ply : conthist_plies) {
            if (ss[-conthist_ply].conthist_subtable) {
              ss[-conthist_ply].conthist_subtable->write(pos, fail_low, malus(depth));
            }
          }
        }
      }

      for (const move fail_low : fail_low_noisies) {
        m_capthist.write(pos, fail_low, malus(depth));
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
      m_corrhist.update(pos, depth, static_eval, best_score);
    }

    m_shared.tt.write(pos, ply, best_move, best_score, raw_eval, depth, actual_node_type);
  }

  return best_score;
}

template<typename Ctrls>
auto worker::quiesce(Ctrls&          ctrls,
                     node_type       expected,
                     const position& pos,
                     line&           pv,
                     score           alpha,
                     score           beta,
                     i32             ply,
                     search_stack*   ss) -> score {
  m_nodes += 1;

  if (m_shared.stopped || ctrls.hard_limit(m_nodes, ply)) {
    m_shared.stopped = true;
    return 0;
  }

  if (m_repetition_table.is_repetition(pos)) {
    return 0;
  }

  if (const auto sc = pos.move_rule(ply)) {
    // We do not trust any mate scores from qsearch, so we always return 0.
    return 0;
  }

  const std::optional<tt::entry> entry = m_shared.tt.probe(pos, ply);

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

    return raw_eval + m_corrhist.read(pos);
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

  move_picker mp{pos, tt_move, m_piece_to, m_capthist, ss};

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
    const position child = pos.make_move(mv);
    make_move(pos, child, mv, ply, ss);

    const score search_score =
      -quiesce(ctrls, expected, child, child_pv, -beta, -alpha, ply + 1, ss + 1);

    unmake_move();

    if (m_shared.stopped) {
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

}  // namespace surveyor
