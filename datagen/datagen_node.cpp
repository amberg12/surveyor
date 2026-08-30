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

#include "datagen_manager.h"

namespace surveyor_datagen {

auto node::launch() -> void {
  m_thread = std::jthread([this] {
    this->thread_main();
  });
}

auto node::thread_main() -> void {
  namespace rv = std::views;

  std::vector<std::string> work;

  while (m_manager.requires_games()) {
    work.clear();

    for ([[maybe_unused]] const i32 work_slice : rv::iota(0, 5)) {
      work.emplace_back("foo");
    }

    m_manager.submit_work(work);
  }
}

}  // namespace surveyor_datagen
