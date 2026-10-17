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

#ifndef SURVEYOR_EVALUATION_CONSTANTS_H
#define SURVEYOR_EVALUATION_CONSTANTS_H
#include "eval_types.h"

namespace surveyor::evaluation_constants {
inline const pair pawn_material = S(133, 260);
inline const pair knight_material = S(566, 681);
inline const pair bishop_material = S(588, 754);
inline const pair rook_material = S(777, 1229);
inline const pair queen_material = S(1671, 1988);

inline const pair bishop_pair = S(113, 146);

inline const std::array knight_mobility = {
  S(-52, -73), S(-20, -43), S(-1, -22), S(1, -1), S(7, 17), S(13, 26), S(15, 33), S(14, 30), S(21, 33),
};
inline const std::array bishop_mobility = {
  S(-70, -94), S(-39, -57), S(-17, -26), S(-8, -19), S(-1, 0), S(5, 10), S(8, 21), S(6, 21), S(20, 28), S(25, 36), S(29, 23), S(29, 28), S(2, 0), S(8, 26),
};
inline const std::array rook_mobility = {
  S(-79, -83), S(-54, -45), S(-40, -28), S(-30, -14), S(-30, -10), S(-9, -6), S(-8, -1), S(1, 3), S(11, 10), S(23, 15), S(29, 22), S(36, 32), S(46, 37), S(63, 20), S(41, 48),
};
inline const std::array queen_mobility = {
  S(-39, -67), S(-33, -67), S(-24, -86), S(-20, -76), S(-7, -62), S(-9, -43), S(-3, -37), S(-4, -13), S(3, 3), S(5, 18), S(8, 30), S(7, 41), S(14, 43), S(15, 52), S(18, 57), S(15, 67), S(20, 63), S(23, 57), S(33, 60), S(35, 46), S(41, 40), S(33, 43), S(21, 13), S(8, 7), S(-24, -28), S(-35, -40), S(-51, -61), S(-53, -63),
};

inline const pair pawn_threat_knight = S(78, 26);
inline const pair pawn_threat_bishop = S(84, 37);
inline const pair pawn_threat_rook = S(58, 31);
inline const pair pawn_threat_queen = S(37, -10);

inline const pair pp_threat_knight = S(37, 26);
inline const pair pp_threat_bishop = S(22, -4);
inline const pair pp_threat_rook = S(27, 22);
inline const pair pp_threat_queen = S(35, -30);

inline const pair knight_threat_pawn = S(10, 32);
inline const pair knight_threat_bishop = S(49, 31);
inline const pair knight_threat_rook = S(93, -11);
inline const pair knight_threat_queen = S(36, -15);

inline const pair bishop_threat_pawn = S(9, 15);
inline const pair bishop_threat_knight = S(37, 26);
inline const pair bishop_threat_rook = S(79, 19);
inline const pair bishop_threat_queen = S(72, 23);

inline const pair rook_threat_pawn = S(-2, 42);
inline const pair rook_threat_knight = S(49, 27);
inline const pair rook_threat_bishop = S(53, 31);
inline const pair rook_threat_queen = S(72, -8);

inline const pair king_threat_pawn = S(36, 74);
inline const pair king_threat_knight = S(-3, 9);
inline const pair king_threat_bishop = S(38, 13);
inline const pair king_threat_rook = S(-44, -6);

inline const pair hanging = S(22, 39);

inline const std::array passed_pawn = {
  S(-28, -103), S(-40, -91), S(-51, 5), S(-12, 86), S(52, 153), S(153, 245),
};
inline const std::array defended_passed_pawn = {
  S(10, -4), S(14, 27), S(26, 40), S(14, 75), S(47, 108), S(48, 148),
};
inline const std::array blocked_passed_pawn = {
  S(-3, -14), S(8, -3), S(-11, -18), S(-18, -31), S(-9, -64), S(-30, -98),
};
inline const std::array friendly_passer_tropism = {
  S(6, 73), S(0, 67), S(11, 41), S(10, 26), S(13, 32), S(23, 31), S(7, 23),
};
inline const std::array enemy_passer_tropism = {
  S(-37, 0), S(10, 13), S(20, 43), S(30, 55), S(26, 58), S(16, 60), S(7, 64),
};

inline const pair isolated_pawn = S(-7, -2);
inline const std::array defended_pawn = {
  S(18, 10), S(21, 8), S(26, 23), S(85, 61), S(61, 106),
};
inline const std::array phalanx = {
  S(6, -9), S(20, 7), S(25, 36), S(77, 89), S(53, 91), S(7, 21),
};

inline const std::array shelter_centre = {
  S(-33, -14), S(23, -16), S(-2, -5), S(4, -17), S(-8, 1), S(-1, 7), S(18, 45),
};
inline const std::array shelter_mid = {
  S(-55, -16), S(38, -23), S(22, -15), S(17, -22), S(-5, 0), S(-17, 17), S(0, 60),
};
inline const std::array shelter_edge = {
  S(-40, -16), S(24, -34), S(20, -19), S(11, -21), S(-8, -1), S(-17, 30), S(11, 63),
};

inline const std::array king_ring = {
  S(-39, 9), S(-29, 10), S(-27, 0), S(-30, 7), S(-9, -83),
};

inline const std::array pawn_psqt = {
  S( -55,   -2), S( -21,   -4), S( -40,  -12), S( -49,  -21), S( -45,    0), S(   2,  -29), S(  51,  -59), S( -45,  -57),
  S( -58,  -26), S( -41,  -24), S( -27,  -53), S( -43,  -39), S( -34,  -35), S( -67,  -38), S(  12,  -80), S( -39,  -74),
  S( -61,   -5), S( -51,  -16), S( -21,  -43), S( -13,  -63), S( -25,  -67), S( -28,  -51), S( -31,  -46), S( -55,  -56),
  S( -48,   14), S(   4,    0), S( -14,  -26), S(  20,  -57), S(  20,  -65), S(   7,  -59), S(  19,  -35), S( -30,  -40),
  S( -13,   84), S(  21,   78), S(  49,   41), S(  73,    9), S(  57,    7), S(  52,    3), S(  29,   55), S(   0,   35),
  S( 105,  140), S( 116,  149), S(  97,  132), S(  98,  113), S(  86,   81), S(  19,   60), S(  10,   96), S(   7,   92),
};
inline const std::array knight_psqt = {
  S( -43,  -28), S( -54,  -43), S( -40,  -21), S( -29,  -21), S( -33,  -18), S(  -2,  -24), S( -37,  -32), S( -23,  -32),
  S( -44,  -33), S( -46,  -20), S( -38,  -10), S(  -5,    8), S(  11,    1), S(  10,  -19), S( -11,  -21), S(  -7,  -27),
  S( -59,  -21), S( -21,    0), S( -10,   10), S(  12,   30), S(  21,   24), S(  30,    3), S(  36,   -9), S( -30,  -20),
  S( -34,   -4), S(  -8,    6), S(  17,   36), S(  31,   41), S(  43,   49), S(  51,   22), S(  41,   13), S(  13,   -9),
  S( -10,   10), S(  15,   20), S(  18,   41), S(  75,   53), S(  38,   56), S( 115,   25), S(  37,   25), S(  66,   -3),
  S( -24,  -10), S(  -4,   11), S(  31,   26), S(  46,   24), S(  64,   20), S(  59,   42), S(  25,   17), S(   7,    0),
  S( -56,  -16), S( -33,   -7), S(   2,   -1), S(  30,   23), S(  17,   10), S(  38,   13), S( -26,  -19), S(  -2,  -19),
  S(-143,  -62), S( -20,  -22), S( -30,  -17), S(  -7,   -1), S(   5,   -3), S( -47,  -17), S(  -4,   -6), S( -23,  -41),
};
inline const std::array bishop_psqt = {
  S( -17,  -36), S( -16,  -28), S(  -9,  -16), S( -19,   -7), S( -17,  -26), S( -31,    6), S( -10,  -21), S(  -3,   -4),
  S(   9,  -21), S(   4,   -7), S(  10,  -11), S( -17,    7), S(   9,   -2), S(  12,  -15), S(  53,  -19), S( -13,  -21),
  S( -20,   -9), S(  19,    9), S(  11,   16), S(   0,    8), S(   0,   38), S(  24,    4), S(  15,  -11), S(   9,   -4),
  S( -10,  -11), S( -21,   15), S(  12,   19), S(  18,   43), S(  25,   16), S(  13,   13), S(   6,   -4), S(  -3,  -21),
  S( -13,   -2), S(  -5,   14), S(  -3,   29), S(  46,   30), S(  27,   31), S(  23,   12), S(  14,    6), S(   1,  -10),
  S( -15,   -4), S(   0,   17), S(  -2,   21), S(  26,    6), S(  50,   17), S(  41,   35), S(  43,   13), S(  16,   -6),
  S( -34,   -3), S( -27,    2), S(  -8,    1), S( -13,   -5), S( -25,   -1), S(  11,    0), S( -12,  -10), S( -22,  -26),
  S( -18,    0), S( -13,   -6), S( -27,  -13), S( -16,   -8), S( -15,    0), S( -51,  -16), S( -11,   -8), S(  -7,  -10),
};
inline const std::array rook_psqt = {
  S( -26,  -14), S( -17,  -21), S(   0,  -11), S(  11,  -24), S(  34,  -43), S(  23,  -36), S( -23,   -4), S(  -5,  -59),
  S( -66,   -6), S( -45,  -13), S( -30,    2), S( -19,  -17), S( -22,  -25), S(   6,  -35), S(   2,  -40), S( -79,  -38),
  S( -52,    5), S( -41,    3), S( -36,   13), S( -24,   -7), S( -13,  -16), S(   1,  -21), S(  17,  -27), S( -14,  -33),
  S( -47,   15), S( -39,    9), S( -24,   10), S(   2,   -5), S( -16,  -13), S(   0,  -11), S(  -7,   -8), S( -21,  -26),
  S( -40,   31), S( -24,   21), S(   0,   18), S(  11,    5), S(  21,  -12), S(  43,   -5), S(  20,   -1), S(   5,   -3),
  S( -19,   33), S(   7,   17), S(   6,   23), S(  26,    8), S(  45,   -1), S(  55,    1), S(  20,   18), S(   6,    2),
  S( -19,   39), S( -18,   44), S(  26,   30), S(  46,   20), S(  34,   15), S(  58,   15), S(  25,   30), S(  52,   14),
  S(   8,   14), S(  11,   14), S(  22,   18), S(  32,   17), S(  34,   12), S(  16,   21), S(  18,   25), S(  40,   14),
};
inline const std::array queen_psqt = {
  S( -27,  -27), S( -28,  -32), S( -11,  -29), S(  10,  -33), S( -18,  -39), S( -69,  -63), S( -45,  -46), S( -47,  -37),
  S( -38,  -29), S( -27,  -16), S( -10,  -12), S(  -3,   -9), S(   6,   -5), S(   8,  -38), S(  -5,  -34), S( -24,  -28),
  S( -42,  -23), S( -17,   -3), S( -11,    9), S( -12,    6), S(  -5,   41), S(  16,    5), S(  24,    3), S( -10,  -16),
  S( -25,   -2), S( -30,   -3), S(  -9,   19), S(  -4,   42), S(  11,   27), S(  12,   22), S(  21,   12), S(   0,    6),
  S( -24,    0), S( -12,   31), S(  -8,   20), S(   1,   54), S(  31,   51), S(  40,   16), S(  34,   38), S(  36,  -23),
  S( -22,   -9), S(  -9,    5), S(   8,   23), S(   8,   28), S(  40,   35), S(  55,   26), S(  57,   22), S(  28,   -5),
  S( -26,  -18), S( -39,   10), S(  -7,   27), S(  -4,   31), S(   7,   15), S(  57,   15), S(  45,   16), S(  73,   -3),
  S( -23,  -39), S( -13,  -16), S(   2,   -6), S(  -1,   -9), S(  14,   -4), S(  22,    7), S(  17,   -3), S(  24,   -1),
};
inline const std::array king_psqt = {
  S( -28,  -39), S(  18,  -53), S(  44,  -37), S( -54,  -49), S(  43,  -81), S(   2,  -53), S( 124,  -86), S(  81, -108),
  S(  -3,  -32), S(   7,  -25), S(   4,   -7), S( -32,    5), S( -20,   10), S(  36,   -3), S(  90,  -33), S(  87,  -57),
  S( -20,  -45), S(  -1,  -23), S( -19,    0), S( -26,   21), S( -42,   24), S( -21,   17), S(  11,  -12), S( -46,  -24),
  S( -20,  -21), S( -28,   -8), S( -23,   12), S( -21,   22), S( -19,   27), S( -38,   25), S( -38,   -1), S( -56,  -37),
  S( -14,   -6), S(  -3,   20), S(  -2,   34), S(  -4,   38), S(  -8,   46), S(   1,   54), S( -10,   28), S( -26,  -12),
  S(  -1,   12), S(   1,   23), S(   6,   45), S(   6,   46), S(   8,   51), S(  11,   69), S(   9,   47), S(  -2,   21),
  S(   0,   -3), S(   3,   17), S(   4,   23), S(   6,   20), S(   7,   25), S(  10,   39), S(   2,   25), S(   0,    4),
  S(  -1,   -9), S(   0,   -7), S(   1,    6), S(   0,    2), S(   1,    6), S(   1,    3), S(   0,    1), S(   0,    0),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
