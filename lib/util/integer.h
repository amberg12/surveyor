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

#ifndef SURVEYOR_INTEGER_H
#define SURVEYOR_INTEGER_H
#include <chrono>
#include <concepts>
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

template<std::integral T>
constexpr auto to_unsigned(T val) {
  using Out = std::make_unsigned_t<T>;
  return static_cast<Out>(val);
}

template<std::integral T>
constexpr auto signum(T val) {
  return val < 0 ? -1 : val == 0 ? 0 : 1;
}

using f32 = float;
using f64 = double;

namespace time {
using clock         = std::chrono::steady_clock;
using time_point    = std::chrono::time_point<clock>;
using duration      = time_point::duration;
using float_seconds = std::chrono::duration<f64>;
using milliseconds  = std::chrono::duration<i64, std::milli>;

template<typename T>
constexpr T cast(const auto& x) {
  return std::chrono::duration_cast<T>(x);
}

constexpr auto nps(u64 nodes, const auto& elapsed) -> u64 {
  return static_cast<u64>(static_cast<f64>(nodes) / cast<float_seconds>(elapsed).count());
}
}  // namespace time
}  // namespace surveyor
#endif  // SURVEYOR_INTEGER_H
