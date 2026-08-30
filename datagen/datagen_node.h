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

#ifndef UCI_DATAGEN_NODE_H
#define UCI_DATAGEN_NODE_H
#include "common.h"

#include <random>

namespace surveyor_datagen {
struct manager;

class node {
public:
  node(manager& m)
      : m_manager(m) {
  }

  auto launch() -> void;

private:
  auto thread_main() -> void;

  auto generate_game() -> std::string;

  manager& m_manager;

  std::jthread m_thread;

  std::mt19937_64 m_rng;
};
}  // namespace surveyor_datagen

#endif  // UCI_DATAGEN_NODE_H
