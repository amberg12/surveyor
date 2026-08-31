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

#include "datagen_manager.h"

#include "datagen_node.h"

#include <print>

namespace surveyor_datagen {

manager::manager(usize concurrency, i64 games)
    : m_target(games) {
  namespace rg = std::ranges;
  namespace rv = std::views;

  for (const usize i : rv::iota(usize{0}, concurrency)) {
    m_nodes.emplace_back(std::make_unique<node>(i, *this));
  }
}

manager::~manager() = default;

auto manager::run() -> void {
  for (auto& node : m_nodes) {
    node->launch();
  }

  for (auto& node : m_nodes) {
    node->join();
  }
}

auto manager::requires_games() const -> bool {
  return m_completed.load() < m_target;
}

auto manager::submit_work(std::span<std::string> work) -> void {
  m_completed.fetch_add(static_cast<i64>(work.size()));

  for (const auto& s : work) {
    std::println("{}", s);
  }

  std::fflush(stdout);
}

}  // namespace surveyor_datagen
