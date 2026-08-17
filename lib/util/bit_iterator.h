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

#ifndef SURVEYOR_BIT_ITERATOR_H
#define SURVEYOR_BIT_ITERATOR_H

#include "bit.h"
#include "integer.h"

#include <bit>
#include <concepts>

namespace surveyor {

template<std::integral T>
struct bit_iterator {
  using value_type = T;

  explicit constexpr bit_iterator(T value)
      : m_value(value) {
  }

  constexpr auto operator++() -> bit_iterator& {
    m_value = clear_lsb(m_value);

    return *this;
  }

  constexpr auto operator*() const {
    return std::countr_zero(to_unsigned(lsb(m_value)));
  }

  friend constexpr auto operator==(const bit_iterator&, const bit_iterator&) -> bool = default;

private:
  T m_value;
};

}  // namespace surveyor

#endif  // SURVEYOR_BIT_ITERATOR_H
