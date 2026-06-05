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

namespace surveyor {

class node_type {
public:
  [[nodiscard]] static constexpr auto none() -> node_type {
    return underlying::none;
  }

  [[nodiscard]] static constexpr auto pv() -> node_type {
    return underlying::pv;
  }

  [[nodiscard]] static constexpr auto cut() -> node_type {
    return underlying::cut;
  }

  [[nodiscard]] static constexpr auto all() -> node_type {
    return underlying::all;
  }

  // Methods
  [[nodiscard]] constexpr auto has_value() const -> bool {
    return *this != node_type::none();
  }

  // Overloads
  friend constexpr auto operator==(const node_type& lhs, const node_type& rhs) -> bool = default;

private:
  enum class underlying {
    none,
    pv,
    cut,
    all,
  };

  node_type(underlying raw)
      : m_raw(raw) {
  }

  underlying m_raw = underlying::none;
};

}  // namespace surveyor
