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

#ifndef SURVEYOR_CAST_ITERATOR_H
#define SURVEYOR_CAST_ITERATOR_H
#include <concepts>

namespace surveyor {
template<typename It, typename To>
  requires requires(It iter) {
    { ++iter } -> std::same_as<It&>;
    { *iter };
    requires std::constructible_from<To, decltype(*iter)>;
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
    return static_cast<To>(*m_it);
  }

  friend constexpr auto operator==(const cast_iterator&, const cast_iterator&) -> bool = default;

private:
  It m_it;
};

}  // namespace surveyor

#endif  // SURVEYOR_CAST_ITERATOR_H
