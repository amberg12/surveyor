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

constexpr score pawn_material   = 180;
constexpr score knight_material = 590;
constexpr score bishop_material = 591;
constexpr score rook_material   = 866;
constexpr score queen_material  = 1534;

constexpr std::array<score, 48> pawn_psqt = {
  27,  51,  24,  -3,  39,  60,  88,  18,  22,  //
  47,  27,  30,  48,  28,  73,  28,  31,       //
  55,  29,  51,  48,  32,  55,  21,  83,       //
  82,  62,  51,  78,  64,  91,  71,  214,      //
  231, 205, 175, 175, 173, 227, 176, 363,      //
  339, 355, 297, 280, 273, 282, 287,
};

constexpr std::array<score, 64> knight_psqt = {
  -26, 23,  36,  68,  67,  74,  23,   1,    32,  //
  60,  98,  119, 122, 121, 84,  82,   53,        //
  106, 139, 170, 182, 152, 145, 82,   102,       //
  140, 185, 184, 202, 184, 174, 121,  118,       //
  154, 211, 251, 229, 254, 186, 166,  119,       //
  175, 206, 239, 253, 234, 195, 141,  78,        //
  117, 156, 162, 148, 203, 118, 103,  -165,      //
  26,  79,  86,  113, 32,  34,  -123,
};

constexpr std::array<score, 64> bishop_psqt = {
  135, 189, 139, 151, 143, 139, 166, 140, 195,  //
  187, 218, 179, 198, 204, 226, 183, 189,       //
  206, 217, 227, 226, 215, 202, 193, 164,       //
  204, 227, 251, 246, 223, 206, 171, 182,       //
  219, 233, 269, 260, 250, 222, 189, 191,       //
  208, 226, 239, 230, 254, 242, 242, 139,       //
  201, 193, 180, 196, 198, 198, 158, 120,       //
  155, 158, 147, 151, 139, 148, 98,
};

constexpr std::array<score, 64> rook_psqt = {
  270, 292, 314, 325, 326, 303, 311, 244, 266,  //
  293, 308, 305, 301, 296, 305, 268, 281,       //
  296, 303, 310, 306, 296, 316, 289, 307,       //
  320, 329, 336, 329, 312, 321, 308, 347,       //
  363, 366, 361, 351, 347, 352, 341, 363,       //
  388, 388, 383, 390, 374, 389, 368, 378,       //
  392, 410, 413, 404, 403, 383, 383, 383,       //
  385, 405, 394, 393, 383, 375, 384,
};

constexpr std::array<score, 64> queen_psqt = {
  653, 621, 636, 664, 648, 627, 626, 626, 647,  //
  654, 682, 680, 681, 678, 670, 672, 648,       //
  672, 681, 679, 689, 700, 709, 692, 660,       //
  680, 681, 721, 715, 712, 718, 717, 650,       //
  685, 708, 726, 754, 764, 754, 748, 669,       //
  691, 722, 753, 784, 837, 814, 812, 641,       //
  661, 705, 739, 766, 776, 744, 791, 606,       //
  663, 719, 739, 751, 735, 711, 683,
};

constexpr std::array<score, 64> king_psqt = {
  -40, 27,  3,   -92, -59, -71, 0,    -28,  -13,  //
  -21, -12, -25, -19, -18, -5,  -16,  -61,        //
  -7,  -3,  2,   10,  -6,  -9,  -44,  -56,        //
  -4,  21,  48,  41,  28,  6,   -38,  -33,        //
  33,  61,  65,  72,  72,  54,  -6,   -15,        //
  52,  59,  80,  82,  102, 86,  21,   -44,        //
  25,  29,  28,  54,  69,  73,  12,   -157,       //
  -98, -58, -26, -37, -4,  16,  -140,
};

}  // namespace surveyor::evaluation_constants
