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

#ifndef UCI_DATAGEN_MANAGER_H
#define UCI_DATAGEN_MANAGER_H
#include "common.h"

#include <memory>
#include <span>
#include <string>
#include <vector>

namespace surveyor_datagen {
class node;

class manager {
public:
  manager(usize concurrency, i64 games);
  ~manager();

  auto run() -> void;

  auto requires_games() const -> bool;

  auto submit_work(std::span<std::string>) -> void;

private:
  std::vector<std::unique_ptr<node>> m_nodes;
  i64                                m_target;
  std::atomic_int64_t                m_completed;

  std::mutex m_submit_lock;
};

}  // namespace surveyor_datagen

#endif  // UCI_DATAGEN_MANAGER_H
