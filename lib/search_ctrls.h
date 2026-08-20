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

#ifndef SURVEYOR_SEARCH_LIMITS_H
#define SURVEYOR_SEARCH_LIMITS_H
#include "util/integer.h"

#include <variant>

namespace surveyor::ctrls {

struct search_control {
  time::time_point start_time;

  [[nodiscard]] auto elapsed() const -> time::duration {
    return time::clock::now() - start_time;
  }
};

struct infinite : public search_control {
  [[nodiscard]] constexpr auto soft_limit(u64 nodes) const -> bool {
    return false;
  }

  [[nodiscard]] constexpr auto hard_limit(u64 nodes) const -> bool {
    return false;
  }
};

struct nodes : public search_control {
  u64 soft_nodes = std::numeric_limits<u64>::max();
  u64 hard_nodes = std::numeric_limits<u64>::max();

  [[nodiscard]] constexpr auto soft_limit(u64 nodes) const -> bool {
    return nodes >= soft_nodes;
  }

  [[nodiscard]] constexpr auto hard_limit(u64 nodes) const -> bool {
    return nodes >= hard_nodes;
  }
};

using ctrls = std::variant<infinite, nodes>;
}  // namespace surveyor

#endif  // SURVEYOR_SEARCH_LIMITS_H
