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

#include <print>
#include <thread>

namespace surveyor {

search::search(search_shared& shared)
    : m_shared(shared) {
}

auto search::launch() -> void {
  m_thread = std::jthread([this] {
    this->thread_main();
  });
}

auto search::thread_main() -> void {
  while (true) {
    switch (m_shared.message) {
    case engine_message::go: {
      std::println("I am being asked to go!");
    } break;
    case engine_message::idle: {
    } break;
    case engine_message::destroy: {
      return;
    }
    }
  }
}

}  // namespace surveyor
