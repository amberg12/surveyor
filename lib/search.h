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
#include "search_ctrls.h"

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

  game g{position::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")};

  auto halt() -> void {
    message = engine_message::idle;
    stopped = true;
  }
};


class worker {
public:
  worker(search_shared& shared);

  auto launch() -> void;

private:
  auto thread_main() -> void;

  auto begin_search() -> void;

  template <typename Ctrls>
  auto iterative_deepening(const position& pos) -> void;

  template <typename Ctrls>
  auto search(Ctrls& ctrls, const position& pos, line& pv, i32 ply, i32 depth) -> score;

  search_shared& m_shared;
  std::jthread   m_thread;
};

}  // namespace surveyor

#endif  // SURVEYOR_SEARCH_H
