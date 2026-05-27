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
#include <concepts>

namespace surveyor {

template<typename It, typename To>
  requires requires(It iter) {
    { To{*iter} } -> std::same_as<To>;
    { ++iter };
  }

struct cast_iterator {
  using value_type = To;

  template<typename... Args>
  explicit constexpr cast_iterator(Args... args)
      : m_it(args...) {
  }

  constexpr auto operator++() -> cast_iterator& {
    ++m_it;

    return *this;
  }

  constexpr auto operator*() const {
    return To{*m_it};
  }

private:
  It m_it;
};

}  // namespace surveyor
