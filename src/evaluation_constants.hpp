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
#include "score.hpp"

namespace surveyor::evaluation_constants {

constexpr score pawn_material   = 0;
constexpr score knight_material = 0;
constexpr score bishop_material = 0;
constexpr score rook_material   = 0;
constexpr score queen_material  = 0;

constexpr std::array<score, 48> pawn_psqt{
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
};

constexpr std::array<score, 64> knight_psqt{
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
};

constexpr std::array<score, 64> bishop_psqt{
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
};

constexpr std::array<score, 64> rook_psqt{
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
};

constexpr std::array<score, 64> queen_psqt{
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
};

constexpr std::array<score, 64> king_psqt{
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
  0, 0, 0, 0, 0, 0, 0, 0,  //
};

}  // namespace surveyor::evaluation_constants
