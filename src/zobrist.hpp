/*
  Shellac - A UCI chess engine.
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
#include "util/multi_array.hpp"

#include <ranges>

namespace surveyor {

using z_key = u64;

namespace zobrist {
namespace zobrist_detail {
constexpr auto rng(u64& seed) -> u64 {
  seed += 0x9E37'79B9'7F4A'7C15ULL;

  u64 out = seed;
  out     = (out ^ out >> 30) * 0xBF58'476D'1CE4'E5B9ULL;
  out     = (out ^ out >> 27) * 0x94D0'49BB'1331'11EBULL;

  return out ^ out >> 31;
}
}  // namespace zobrist_detail

constexpr multi_array_t<z_key, 2, 6, 64> pieces = [] {
  multi_array_t<z_key, 2, 6, 64> out{};

  namespace rv = std::views;

  u64 seed = 0x246C'CB2D'3B76'1F29ULL;

  for (z_key& k : out | rv::join | rv::join) {
    k = zobrist_detail::rng(seed);
  }

  return out;
}();

constexpr std::array<z_key, 16> castling = [] {
  std::array<z_key, 16> out{};

  u64 seed = 0xA9B8'C7D6'E5F4'0312ULL;

  for (z_key& k : out) {
    k = zobrist_detail::rng(seed);
  }

  return out;
}();

constexpr std::array<z_key, 8> en_passant = [] {
  std::array<z_key, 8> out{};

  u64 seed = 0x4F5E'6D7C'8B9A'AB1CULL;

  for (z_key& k : out) {
    k = zobrist_detail::rng(seed);
  }

  return out;
}();

constexpr z_key stm = 0b1111111111111111111111111111111111111111111111111111111111111111;

}  // namespace zobrist


}  // namespace surveyor
