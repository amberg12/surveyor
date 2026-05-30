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
#include <cstdint>

namespace surveyor {

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
using u128 = unsigned __int128;
#pragma GCC diagnostic pop

using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
using i128 = signed __int128;
#pragma GCC diagnostic pop

using usize = std::size_t;
using isize = std::ptrdiff_t;
static_assert(sizeof(usize) == sizeof(isize));

template <std::integral T>
constexpr auto to_unsigned(T val) {
  using Out = std::make_unsigned_t<T>;
  return static_cast<Out>(val);
}

}  // namespace surveyor
