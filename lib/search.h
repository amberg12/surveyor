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
  std::atomic<engine_message> message = engine_message::idle;
  std::atomic_bool            stopped;

  auto halt() -> void {
    message = engine_message::idle;
    stopped = true;
  }
};


class search {
public:
  search(search_shared& shared);

  auto launch() -> void;

private:
  auto thread_main() -> void;

  search_shared& m_shared;
  std::jthread   m_thread;
};

}  // namespace surveyor

#endif  // SURVEYOR_SEARCH_H
