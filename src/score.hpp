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

#include <compare>
#include <format>

namespace surveyor {

class score {
private:
  static constexpr i32 max_mate_ply = 512;

public:
  // Constructor
  constexpr score() {
    *this = none();
  }

  /* implicit */ constexpr score(std::integral auto value)
      : m_value(static_cast<i16>(value)) {
  }

  [[nodiscard]] static constexpr auto none() -> score {
    return -32'000;
  }

  [[nodiscard]] static constexpr auto inf() -> score {
    return 31'000;
  }

  [[nodiscard]] static constexpr auto min_score() -> score {
    return -30'900;
  }

  [[nodiscard]] static constexpr auto max_score() -> score {
    return 30'900;
  }

  [[nodiscard]] static constexpr auto min_normal_score() -> score {
    return min_score().m_value + max_mate_ply + 1;
  }

  [[nodiscard]] static constexpr auto max_normal_score() -> score {
    return max_score().m_value - max_mate_ply - 1;
  }

  [[nodiscard]] static constexpr auto mated_in(i32 ply) -> score {
    return min_score().m_value + ply;
  }

  // Methods
  constexpr auto is_winning() const -> bool {
    return m_value > max_normal_score().m_value;
  }

  constexpr auto is_losing() const -> bool {
    return m_value < min_normal_score().m_value;
  }

  constexpr auto is_mate() const -> bool {
    return is_winning() || is_losing();
  }

  constexpr auto plies_to_mate() const -> i32 {
    if (m_value < 0) {
      return m_value - min_score().m_value;
    } else {
      return max_score().m_value + m_value;
    }
  }

  // Overloads
  friend constexpr auto operator-(const score& s) -> score {
    return -s.m_value;
  }

  friend constexpr auto operator<=>(const score& lhs, const score& rhs)
    -> std::strong_ordering = default;

private:
  friend struct std::formatter<score>;

  i16 m_value = 0;
};

}  // namespace surveyor

template<>
struct std::formatter<surveyor::score> : std::formatter<std::string> {
  auto format(const surveyor::score& s, std::format_context& ctx) const {
    return std::formatter<std::string>::format(std::format("{}", s.m_value), ctx);
  }
};
