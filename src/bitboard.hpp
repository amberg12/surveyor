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
#include "square.hpp"
#include "util/integer.hpp"

namespace surveyor {

struct bitboard {
  u64 raw = 0;

  static constexpr auto square_bb(square sq) -> bitboard {
    return {1ull << sq.idx};
  }

  constexpr auto set(square sq) -> void {
    *this |= square_bb(sq);
  }

  constexpr auto del(square sq) -> void {
    *this &= ~square_bb(sq);
  }

  // Overloads
  friend constexpr auto operator~(bitboard bb) -> bitboard {
    return bitboard{~bb.raw};
  }

  friend constexpr auto operator|(bitboard lhs, bitboard rhs) -> bitboard {
    return {lhs.raw | rhs.raw};
  }

  friend constexpr auto operator|=(bitboard& lhs, bitboard rhs) -> bitboard& {
    lhs = lhs | rhs;
    return lhs;
  }

  friend constexpr auto operator&(bitboard lhs, bitboard rhs) -> bitboard {
    return {lhs.raw & rhs.raw};
  }

  friend constexpr auto operator&=(bitboard& lhs, bitboard rhs) -> bitboard& {
    lhs = lhs & rhs;
    return lhs;
  }
};

}
