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

#ifndef SURVEYOR_MULTI_ARRAY_H
#define SURVEYOR_MULTI_ARRAY_H
#include "integer.h"

namespace surveyor {

template<typename T, usize size, usize... sizes>
struct multi_array {
  using type = std::array<typename multi_array<T, sizes...>::type, size>;
};

template<typename T, usize size>
struct multi_array<T, size> {
  using type = std::array<T, size>;
};

template<typename T, usize... sizes>
using multi_array_t = multi_array<T, sizes...>::type;

}  // namespace surveyor

#endif  // SURVEYOR_MULTI_ARRAY_H
