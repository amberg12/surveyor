/*
  Surveyor - A UCI chess engine.
  Copyright (C) 2026 Amber Goulding

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once
#include "util/integer.hpp"

#include <concepts>

namespace surveyor {

using nodes = u64;

struct search_stats {
  nodes            node_limit;
  time::time_point current_time;
  i32              depth;
};

template<typename S>
concept search_controls = requires(S ctrl, search_stats ss) {
  { ctrl.soft_stop(ss) } -> std::same_as<bool>;
  { ctrl.hard_stop(ss) } -> std::same_as<bool>;
};

namespace search_ctrls {
class clock {
public:
  clock(time::time_point s, time::milliseconds t, time::milliseconds i)
      : m_start(s)
      , m_time(t)
      , m_inc(i) {
  }

  auto soft_stop(const search_stats& ss) const -> bool {
    using namespace std::chrono_literals;
    const time::milliseconds safe_time  = std::max(m_time - 50ms, 0ms);
    const time::milliseconds soft_limit = safe_time / 20 + m_inc / 2;

    return ss.current_time > m_start + soft_limit;
  }

  auto hard_stop(const search_stats& ss) const -> bool {
    using namespace std::chrono_literals;
    const time::milliseconds safe_time  = std::max(m_time - 50ms, 0ms);
    const time::milliseconds hard_limit = safe_time / 20 + m_inc / 2;

    return ss.current_time > m_start + hard_limit;
  }

private:
  time::time_point   m_start;
  time::milliseconds m_time;
  time::milliseconds m_inc;
};

class depth {
public:
  depth(i32 d)
      : m_depth(d) {
  }

  static constexpr auto soft_stop(const search_stats& ss) -> bool {
    return false;
  }

  auto hard_stop(const search_stats& ss) const -> bool {
    return ss.depth > m_depth;
  }

private:
  i32 m_depth;
};

class hard_nodes {
public:
  explicit hard_nodes(nodes n)
      : m_node_limit(n) {
  }

  auto soft_stop(const search_stats& ss) const -> bool {
    return ss.node_limit > m_node_limit;
  }

  auto hard_stop(const search_stats& ss) const -> bool {
    return ss.node_limit > m_node_limit;
  }

private:
  nodes m_node_limit;
};

class infinite {
public:
  static constexpr auto soft_stop(const search_stats&) -> bool {
    return false;
  }

  static constexpr auto hard_stop(const search_stats&) -> bool {
    return false;
  }
};
}  // namespace search_ctrls

}  // namespace surveyor
