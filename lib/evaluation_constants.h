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
inline const pair pawn_material = S(129, 250);
inline const pair knight_material = S(560, 664);
inline const pair bishop_material = S(577, 744);
inline const pair rook_material = S(778, 1229);
inline const pair queen_material = S(1670, 1961);

inline const pair bishop_pair = S(115, 145);

inline const std::array knight_mobility = {
  S(-50, -75), S(-16, -38), S(-3, -19), S(4, -1), S(8, 15), S(13, 27), S(14, 32), S(12, 30), S(18, 27),
};
inline const std::array bishop_mobility = {
  S(-68, -87), S(-31, -49), S(-16, -23), S(-3, -16), S(2, 1), S(9, 15), S(8, 23), S(15, 23), S(21, 29), S(18, 31), S(26, 16), S(25, 19), S(-7, -5), S(0, 22),
};
inline const std::array rook_mobility = {
  S(-75, -77), S(-53, -45), S(-43, -24), S(-29, -8), S(-29, -3), S(-14, 4), S(-8, 7), S(7, 10), S(17, 15), S(25, 17), S(32, 20), S(33, 25), S(45, 31), S(53, 6), S(40, 21),
};
inline const std::array queen_mobility = {
  S(-34, -65), S(-29, -65), S(-21, -80), S(-15, -74), S(-4, -60), S(0, -50), S(1, -36), S(3, -14), S(5, 6), S(8, 21), S(10, 32), S(11, 48), S(15, 49), S(13, 58), S(14, 58), S(11, 73), S(20, 63), S(23, 60), S(28, 54), S(35, 42), S(36, 34), S(28, 34), S(11, 9), S(-3, -1), S(-28, -34), S(-37, -41), S(-52, -61), S(-53, -62),
};

inline const pair pawn_threat_knight = S(83, 41);
inline const pair pawn_threat_bishop = S(87, 51);
inline const pair pawn_threat_rook = S(62, 46);
inline const pair pawn_threat_queen = S(48, 4);

inline const pair knight_threat_pawn = S(-20, 20);
inline const pair knight_threat_bishop = S(53, 46);
inline const pair knight_threat_rook = S(105, 11);
inline const pair knight_threat_queen = S(46, -9);

inline const pair bishop_threat_pawn = S(-3, 9);
inline const pair bishop_threat_knight = S(31, 27);
inline const pair bishop_threat_rook = S(84, 41);
inline const pair bishop_threat_queen = S(80, 26);

inline const std::array passed_pawn = {
  S(-27, -108), S(-45, -95), S(-51, 1), S(-9, 78), S(53, 145), S(148, 280),
};
inline const std::array defended_passed_pawn = {
  S(9, -9), S(15, 27), S(29, 37), S(15, 73), S(50, 104), S(69, 193),
};
inline const std::array blocked_passed_pawn = {
  S(-1, -14), S(8, -5), S(-11, -14), S(-18, -32), S(-19, -62), S(-43, -167),
};
inline const std::array friendly_passer_tropism = {
  S(5, 72), S(5, 68), S(12, 42), S(4, 27), S(9, 30), S(23, 34), S(6, 25),
};
inline const std::array enemy_passer_tropism = {
  S(-55, -51), S(9, 34), S(23, 50), S(29, 59), S(30, 67), S(22, 70), S(6, 71),
};

inline const pair isolated_pawn = S(-5, -6);
inline const std::array defended_pawn = {
  S(21, 19), S(30, 18), S(30, 33), S(90, 81), S(69, 117),
};
inline const std::array phalanx = {
  S(5, -11), S(17, 7), S(29, 40), S(81, 90), S(52, 94), S(9, 30),
};

inline const std::array shelter_centre = {
  S(-33, -13), S(21, -15), S(-3, -9), S(0, -16), S(-8, -1), S(7, 4), S(15, 51),
};
inline const std::array shelter_mid = {
  S(-55, -18), S(38, -22), S(17, -19), S(17, -20), S(-2, -5), S(-20, 16), S(4, 71),
};
inline const std::array shelter_edge = {
  S(-39, -19), S(26, -33), S(24, -19), S(11, -19), S(-7, -3), S(-17, 24), S(3, 70),
};

inline const std::array king_ring = {
  S(-35, 15), S(-30, 14), S(-30, 1), S(-33, 8), S(-8, -85),
};

inline const std::array pawn_psqt = {
  S( -55,   -5), S( -21,   -1), S( -39,  -10), S( -47,  -15), S( -46,    5), S(   3,  -24), S(  55,  -61), S( -42,  -54),
  S( -57,  -24), S( -43,  -25), S( -27,  -47), S( -39,  -36), S( -35,  -33), S( -63,  -37), S(  18,  -81), S( -45,  -70),
  S( -65,  -11), S( -44,  -21), S( -22,  -45), S( -10,  -64), S( -18,  -66), S( -26,  -51), S( -21,  -50), S( -54,  -60),
  S( -47,    8), S(   5,   -6), S( -10,  -26), S(  14,  -59), S(  19,  -63), S(   5,  -61), S(  23,  -37), S( -31,  -45),
  S( -17,   70), S(  21,   67), S(  55,   29), S(  78,    0), S(  64,   -4), S(  56,   -9), S(  29,   45), S(  -2,   31),
  S( 106,  167), S( 110,  162), S(  96,  138), S(  94,  118), S(  76,   88), S(  15,   64), S(  -9,  107), S(  -3,  109),
};
inline const std::array knight_psqt = {
  S( -41,  -27), S( -52,  -42), S( -41,  -26), S( -29,  -21), S( -33,  -18), S(  -2,  -30), S( -37,  -28), S( -29,  -37),
  S( -48,  -31), S( -40,  -25), S( -33,  -11), S(  -8,   10), S(   9,    2), S(   8,  -20), S( -14,  -17), S( -15,  -27),
  S( -63,  -18), S( -22,    5), S(  -6,   12), S(  17,   37), S(  27,   23), S(  33,    6), S(  40,   -9), S( -31,  -23),
  S( -35,   -1), S(   0,   12), S(  22,   37), S(  38,   40), S(  49,   45), S(  55,   18), S(  41,   13), S(   9,  -15),
  S(  -3,   13), S(  18,   20), S(  28,   44), S(  80,   52), S(  36,   57), S( 113,   26), S(  31,   29), S(  55,    0),
  S( -24,  -15), S(  -2,   16), S(  40,   34), S(  66,   32), S(  69,   27), S(  66,   46), S(  24,   16), S(   6,   -1),
  S( -68,  -20), S( -39,   -4), S(   3,   -1), S(  30,   20), S(  16,    4), S(  26,    3), S( -33,  -20), S(  -7,  -28),
  S(-145,  -68), S( -24,  -19), S( -42,  -15), S(  -5,    2), S(   1,  -10), S( -51,  -26), S(  -8,   -9), S( -24,  -39),
};
inline const std::array bishop_psqt = {
  S( -12,  -39), S( -13,  -34), S(  -7,  -21), S( -17,  -15), S( -17,  -32), S( -27,    2), S( -12,  -24), S(  -4,   -9),
  S(   8,  -23), S(   7,  -10), S(   9,  -11), S( -19,    7), S(   9,   -5), S(  18,  -20), S(  57,  -21), S(  -4,  -20),
  S( -18,   -9), S(  20,   11), S(  16,   22), S(   4,   12), S(   3,   44), S(  26,   11), S(  19,  -10), S(   7,   -5),
  S( -16,  -12), S( -19,   23), S(  15,   23), S(  26,   51), S(  36,   19), S(  11,   18), S(   6,    0), S(  -8,  -20),
  S( -20,    2), S( -12,   19), S(  -1,   27), S(  60,   32), S(  25,   38), S(  16,   11), S(   3,    9), S(  -7,  -13),
  S( -19,  -13), S(   1,   19), S(   0,   17), S(  29,    4), S(  53,   18), S(  52,   38), S(  44,   21), S(  13,  -12),
  S( -37,   -4), S( -29,    6), S(  -8,   -1), S( -20,  -10), S( -27,    0), S(   2,    0), S( -20,   -5), S( -37,  -26),
  S( -14,   -9), S( -16,   -3), S( -33,  -17), S( -18,  -12), S( -18,   -1), S( -54,  -13), S( -11,  -15), S(   0,   -7),
};
inline const std::array rook_psqt = {
  S( -31,  -29), S( -18,  -29), S(  -5,  -21), S(  10,  -32), S(  25,  -50), S(  17,  -50), S( -28,  -20), S( -11,  -72),
  S( -71,  -18), S( -45,  -22), S( -35,  -11), S( -25,  -31), S( -23,  -38), S(   3,  -49), S(   0,  -47), S( -87,  -47),
  S( -56,    2), S( -44,   -2), S( -34,    7), S( -31,  -18), S( -21,  -22), S(  -8,  -27), S(  15,  -33), S( -16,  -38),
  S( -46,   11), S( -45,   12), S( -24,    8), S(  -3,   -7), S( -16,  -16), S(  -9,  -12), S( -10,  -13), S( -27,  -33),
  S( -39,   38), S( -28,   30), S(  -1,   24), S(  11,   16), S(  12,   -6), S(  29,    5), S(  11,   -7), S(   0,    0),
  S( -18,   46), S(  16,   35), S(  10,   33), S(  35,   22), S(  58,    7), S(  60,   18), S(  34,   23), S(   9,    3),
  S(  -7,   52), S(  -5,   58), S(  38,   49), S(  58,   41), S(  48,   32), S(  80,   21), S(  32,   38), S(  62,   22),
  S(  18,   12), S(  19,   16), S(  18,   22), S(  32,   21), S(  35,    9), S(  13,   23), S(  23,   24), S(  40,   17),
};
inline const std::array queen_psqt = {
  S( -30,  -29), S( -25,  -34), S(  -9,  -36), S(  12,  -40), S( -20,  -43), S( -65,  -63), S( -41,  -42), S( -41,  -36),
  S( -40,  -31), S( -23,  -11), S( -10,  -15), S(   0,  -12), S(  10,  -14), S(   5,  -37), S(  -2,  -41), S( -31,  -31),
  S( -35,  -27), S( -13,   -4), S( -14,   12), S(  -7,    9), S(  -3,   42), S(  14,    7), S(  19,    0), S(  -8,  -16),
  S( -26,    2), S( -35,    0), S( -11,   17), S(  -8,   54), S(  10,   36), S(   2,   30), S(  20,   11), S(  -6,    0),
  S( -23,    2), S( -20,   41), S(  -4,   26), S(  -1,   63), S(  25,   56), S(  31,   25), S(  21,   44), S(  23,  -20),
  S( -18,   -7), S(  -4,   16), S(  10,   26), S(  10,   35), S(  42,   29), S(  65,   31), S(  64,   22), S(  31,   -9),
  S( -25,  -19), S( -32,   19), S(   0,   27), S(   3,   30), S(   6,   16), S(  55,   15), S(  48,   16), S(  81,    1),
  S( -26,  -47), S(  -9,  -21), S(   3,  -16), S(  -2,  -16), S(   7,  -11), S(  21,    3), S(  12,  -15), S(  22,  -16),
};
inline const std::array king_psqt = {
  S( -30,  -47), S(  18,  -63), S(  42,  -42), S( -57,  -57), S(  42,  -87), S(  -5,  -59), S( 122,  -89), S(  83, -114),
  S(  -4,  -41), S(   3,  -32), S(   3,   -6), S( -34,    2), S( -21,    7), S(  34,   -8), S(  90,  -39), S(  81,  -66),
  S( -24,  -50), S(   1,  -16), S( -22,    1), S( -34,   19), S( -45,   26), S( -20,   11), S(  14,  -15), S( -44,  -29),
  S( -19,  -23), S( -18,   -8), S( -27,   19), S( -20,   22), S( -18,   30), S( -36,   28), S( -36,    0), S( -55,  -31),
  S( -12,   -6), S(   0,   31), S(   1,   38), S(  -1,   38), S(  -3,   50), S(   0,   63), S(  -5,   43), S( -26,  -12),
  S(   0,   10), S(   1,   29), S(   7,   54), S(   8,   46), S(  10,   58), S(  11,   80), S(  10,   60), S(   0,   21),
  S(  -1,   -9), S(   3,   14), S(   7,   31), S(   6,   22), S(   7,   24), S(   9,   40), S(   3,   30), S(   0,    0),
  S(  -1,   -8), S(   1,   -3), S(   1,    4), S(   0,    0), S(   0,    1), S(   2,    5), S(   0,    2), S(   0,   -4),
};

}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
