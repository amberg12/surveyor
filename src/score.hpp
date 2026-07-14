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
#include "util/integer.hpp"

namespace surveyor {

using score = i16;

namespace scoring {
constexpr i16 max_mate_ply = 512;

constexpr score none = -32000;
constexpr score inf  = 31000;

constexpr score min = -30900;
constexpr score max = 30900;

constexpr score min_normal_score = min + max_mate_ply + 1;
constexpr score max_normal_score = max - max_mate_ply - 1;

constexpr auto mated_in(i32 ply) -> score {
  return static_cast<score>(min + ply);
}

constexpr auto is_winning(score sc) -> bool {
  return sc > max_normal_score;
}

constexpr auto is_losing(score sc) -> bool {
  return sc < min_normal_score;
}

constexpr auto is_mate(score sc) -> bool {
  return is_winning(sc) || is_losing(sc);
}

constexpr auto plies_to_mate(score sc) -> i32 {
  if (!is_mate(sc)) {
    return 0;
  }

  return is_winning(sc) ? max - sc : min - sc;
}
}

}  // namespace surveyor