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
#include "piece.hpp"
#include "util/integer.hpp"

namespace surveyor::geometry {

using direction = i32;
using x88       = i32;

constexpr direction n_orth     = 16;
constexpr direction e_orth     = 1;
constexpr direction s_orth     = -16;
constexpr direction w_orth     = -1;
constexpr direction ne_diag    = n_orth + e_orth;
constexpr direction se_diag    = s_orth + e_orth;
constexpr direction sw_diag    = s_orth + w_orth;
constexpr direction nw_diag    = n_orth + w_orth;
constexpr direction nne_horsie = n_orth + n_orth + e_orth;
constexpr direction nee_horsie = n_orth + e_orth + e_orth;
constexpr direction see_horsie = s_orth + e_orth + e_orth;
constexpr direction sse_horsie = s_orth + s_orth + e_orth;
constexpr direction ssw_horsie = s_orth + s_orth + w_orth;
constexpr direction sww_horsie = s_orth + w_orth + w_orth;
constexpr direction nww_horsie = n_orth + w_orth + w_orth;
constexpr direction nnw_horsie = n_orth + n_orth + w_orth;

constexpr auto pawn_direction(color c) -> direction {
  return c == color::white() ? n_orth : s_orth;
}

constexpr auto to_x88(square sq) -> x88 {
  const x88 sq_num = sq.idx;
  return sq_num + (sq_num & ~7);
}

constexpr auto from_x88(x88 sq_num) -> square {
  return square{static_cast<u8>((sq_num + (sq_num & 7)) >> 1)};
}

constexpr auto shift(square src, direction dir) -> std::optional<square> {
  const x88 dst = to_x88(src) + dir;

  if (dst & 0x88) {
    return std::nullopt;
  }

  return from_x88(dst);
}

}  // namespace surveyor::geometry
