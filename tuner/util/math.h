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

#ifndef UCI_MATH_H
#define UCI_MATH_H
#include "common.h"

#include <cmath>

namespace surveyor_tuner {

template<typename T, typename U, usize cnt>
auto dot_product(const std::array<T, cnt> l, const std::array<U, cnt> r) {
  decltype(std::declval<T>() * std::declval<U>()) result{};

  for (usize i = 0; i < cnt; ++i) {
    result += l[i] * r[i];
  }

  return result;
}

inline auto sigmoid(f64 x) -> f64 {
  return 1.0 / (1.0 + std::exp(-x));
}

}  // namespace surveyor_tuner
#endif  // UCI_MATH_H
