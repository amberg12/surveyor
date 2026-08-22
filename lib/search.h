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

#ifndef SURVEYOR_SEARCH_H
#define SURVEYOR_SEARCH_H
#include "engine_output.h"
#include "game.h"
#include "history.h"
#include "node_type.h"
#include "repetition_table.h"
#include "search_ctrls.h"
#include "transposition_table.h"

#include <atomic>
#include <memory>
#include <thread>

namespace surveyor {

enum class engine_message {
  go,
  idle,
  destroy,
};

struct search_shared {
  ctrls::ctrls ctrls;

  std::atomic<engine_message> message = engine_message::idle;
  std::atomic_bool            stopped;

  std::shared_ptr<engine_output> output;

  tt::transposition_table tt{16};

  game g{position::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")};

  auto halt() -> void {
    stopped = true;
    message = engine_message::idle;
    message.notify_all();
  }
};

struct search_stack {
  continuation_history::subtable* conthist_subtable = nullptr;

  score static_eval = scoring::none;
  score raw_eval    = scoring::none;
  move  excluded    = move::null();

  move killer_1 = move::null();
  move killer_2 = move::null();

  auto clear_killers() -> void {
    killer_1 = move::null();
    killer_2 = move::null();
  }

  auto add_killer(move mv) -> void {
    if (killer_1 != mv) {
      killer_2 = killer_1;
      killer_1 = mv;
    }
  }
};

class worker {
public:
  worker(search_shared& shared);

  auto launch() -> void;

  auto nodes() -> u64;

  auto reset() -> void;

private:
  auto thread_main() -> void;

  auto begin_search() -> void;

  template<typename Ctrls>
  auto iterative_deepening(const position& pos) -> void;

  template<typename Ctrls>
  auto search(Ctrls&          ctrls,
              node_type       expected,
              const position& pos,
              line&           pv,
              score           alpha,
              score           beta,
              i32             ply,
              i32             depth,
              search_stack*   ss) -> score;

  template<typename Ctrls>
  auto quiesce(Ctrls&          ctrls,
               node_type       expected,
               const position& pos,
               line&           pv,
               score           alpha,
               score           beta,
               i32             ply,
               search_stack*   ss) -> score;

  auto make_move(const position& pos, const position& child, move mv, i32 ply, search_stack* ss) -> void;
  auto make_null_move(const position& child, i32 ply, search_stack* ss) -> void;
  auto unmake_move() -> void;

  search_shared& m_shared;
  std::jthread   m_thread;

  repetition_table m_repetition_table;

  correction_history   m_corrhist;
  piece_to_history     m_piece_to;
  capture_history      m_capthist;
  continuation_history m_conthist;

  u64 m_nodes;
};

}  // namespace surveyor

#endif  // SURVEYOR_SEARCH_H
