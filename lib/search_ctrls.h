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
  [[nodiscard]] constexpr auto soft_limit(u64 nodes, i32 depth) const -> bool {
    return false;
  }

  [[nodiscard]] constexpr auto hard_limit(u64 nodes, i32 depth) const -> bool {
    return false;
  }
};

struct nodes : public search_control {
  u64 soft_nodes = std::numeric_limits<u64>::max();
  u64 hard_nodes = std::numeric_limits<u64>::max();

  [[nodiscard]] constexpr auto soft_limit(u64 nodes, i32 depth) const -> bool {
    return nodes >= soft_nodes;
  }

  [[nodiscard]] constexpr auto hard_limit(u64 nodes, i32 depth) const -> bool {
    return nodes >= hard_nodes;
  }
};

struct fixed_time : public search_control {
  std::optional<time::milliseconds> soft_time = std::nullopt;
  std::optional<time::milliseconds> hard_time = std::nullopt;

  [[nodiscard]] constexpr auto soft_limit(u64 nodes, i32 depth) const -> bool {
    using namespace std::chrono_literals;

    if (!soft_time.has_value()) {
      return false;
    }

    return elapsed() >= std::max(*soft_time - 50ms, 0ms);
  }

  [[nodiscard]] constexpr auto hard_limit(u64 nodes, i32 depth) const -> bool {
    using namespace std::chrono_literals;

    if (!hard_time.has_value()) {
      return false;
    }

    return elapsed() >= std::max(*hard_time - 50ms, 0ms);
  }
};

struct depth : public search_control {
  std::optional<i32> soft_depth = std::nullopt;
  std::optional<i32> hard_depth = std::nullopt;

  [[nodiscard]] constexpr auto soft_limit(u64 nodes, i32 depth) const -> bool {
    if (!soft_depth.has_value()) {
      return false;
    }

    return depth >= *soft_depth;
  }

  [[nodiscard]] constexpr auto hard_limit(u64 nodes, i32 depth) const -> bool {
    if (!hard_depth.has_value()) {
      return false;
    }

    return depth >= *hard_depth;
  }
};

struct clock : public search_control {
  time::milliseconds t;
  time::milliseconds i;

  [[nodiscard]] constexpr auto soft_limit(u64 nodes, i32 depth) const -> bool {
    using namespace std::chrono_literals;

    const time::milliseconds hard_limit = std::max(t / 3 - 50ms, 0ms);
    const time::milliseconds soft_limit = std::min(t / 20 + i / 2, hard_limit);

    return elapsed() > soft_limit;
  }

  [[nodiscard]] constexpr auto hard_limit(u64 nodes, i32 depth) const -> bool {
    using namespace std::chrono_literals;

    const time::milliseconds hard_limit = std::max(t / 3 - 50ms, 0ms);

    return elapsed() > hard_limit;
  }
};

using ctrls = std::variant<infinite, nodes, fixed_time, depth, clock>;
}  // namespace surveyor

#endif  // SURVEYOR_SEARCH_LIMITS_H
