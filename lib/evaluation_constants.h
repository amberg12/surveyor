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
inline const pair pawn_material = S(127, 224);
inline const pair knight_material = S(562, 670);
inline const pair bishop_material = S(577, 743);
inline const pair rook_material = S(777, 1232);
inline const pair queen_material = S(1672, 1966);

inline const pair bishop_pair = S(117, 145);

inline const std::array knight_mobility = {
  S(-49, -77), S(-13, -40), S(-2, -20), S(4, -1), S(11, 17), S(9, 27), S(14, 32), S(9, 33), S(14, 26),
};
inline const std::array bishop_mobility = {
  S(-64, -86), S(-33, -48), S(-13, -21), S(-4, -12), S(4, 0), S(8, 14), S(10, 23), S(14, 21), S(18, 27), S(17, 31), S(26, 15), S(24, 20), S(-7, -6), S(0, 21),
};
inline const std::array rook_mobility = {
  S(-76, -74), S(-54, -43), S(-45, -24), S(-29, -8), S(-28, -4), S(-14, 2), S(-6, 4), S(6, 8), S(17, 13), S(25, 18), S(33, 23), S(32, 27), S(43, 28), S(55, 7), S(41, 22),
};
inline const std::array queen_mobility = {
  S(-24, -65), S(-26, -64), S(-21, -80), S(-12, -76), S(-5, -62), S(-2, -50), S(4, -34), S(3, -13), S(4, 7), S(8, 22), S(10, 34), S(13, 49), S(15, 50), S(11, 59), S(14, 59), S(8, 72), S(16, 61), S(21, 59), S(26, 55), S(34, 41), S(36, 32), S(28, 34), S(11, 9), S(-4, -3), S(-28, -35), S(-37, -42), S(-52, -61), S(-53, -62),
};

inline const pair pawn_threat_knight = S(81, 41);
inline const pair pawn_threat_bishop = S(88, 51);
inline const pair pawn_threat_rook = S(59, 41);
inline const pair pawn_threat_queen = S(47, 3);

inline const pair knight_threat_pawn = S(-14, 16);
inline const pair knight_threat_bishop = S(56, 47);
inline const pair knight_threat_rook = S(105, 11);
inline const pair knight_threat_queen = S(46, -8);

inline const pair bishop_threat_pawn = S(-4, 9);
inline const pair bishop_threat_knight = S(31, 26);
inline const pair bishop_threat_rook = S(82, 39);
inline const pair bishop_threat_queen = S(77, 26);

inline const std::array passed_pawn = {
  S(-34, -105), S(-48, -90), S(-42, -7), S(-8, 75), S(39, 154), S(140, 360),
};
inline const std::array defended_passed_pawn = {
  S(25, -22), S(26, 3), S(29, 27), S(18, 68), S(55, 107), S(81, 217),
};
inline const std::array blocked_passed_pawn = {
  S(3, -46), S(10, -11), S(-5, -21), S(-20, -32), S(-21, -64), S(-50, -170),
};
inline const std::array friendly_passer_tropism = {
  S(1, 106), S(-9, 85), S(6, 51), S(-1, 34), S(13, 38), S(31, 38), S(4, 33),
};
inline const std::array enemy_passer_tropism = {
  S(-58, -51), S(11, 37), S(18, 60), S(31, 79), S(27, 89), S(16, 92), S(0, 79),
};

inline const pair isolated_pawn = S(-4, -14);
inline const std::array defended_pawn = {
  S(19, 27), S(25, 18), S(25, 35), S(93, 92), S(71, 121),
};
inline const std::array phalanx = {
  S(7, -6), S(18, 14), S(29, 38), S(77, 93), S(49, 87), S(7, 26),
};

inline const std::array shelter_centre = {
  S(-20, -8), S(20, -3), S(7, 2), S(-7, 6), S(-4, -3), S(4, 8), S(1, -1), S(0, 0),
};
inline const std::array shelter_mid = {
  S(-30, -21), S(48, -19), S(1, -2), S(-32, 2), S(0, 9), S(6, 13), S(7, 18), S(0, 0),
};
inline const std::array shelter_edge = {
  S(-20, -11), S(39, -13), S(0, 5), S(-24, 5), S(0, 6), S(4, 9), S(2, 0), S(0, 0),
};

inline const std::array king_ring = {
  S(-41, 19), S(-32, 13), S(-27, 0), S(-30, 7), S(-6, -82),
};

inline const std::array pawn_psqt = {
  S( -49,    3), S( -14,    0), S( -32,    1), S( -30,   -5), S( -32,   16), S(  25,  -12), S(  73,  -53), S( -32,  -51),
  S( -52,  -16), S( -33,  -19), S( -20,  -32), S( -31,  -22), S( -32,  -19), S( -54,  -28), S(  22,  -76), S( -31,  -64),
  S( -59,    3), S( -42,   -8), S( -14,  -32), S(  -3,  -46), S( -14,  -52), S( -23,  -44), S( -14,  -43), S( -48,  -43),
  S( -44,   22), S(  14,    2), S(  -4,  -14), S(  18,  -44), S(  21,  -45), S(   3,  -41), S(  17,  -27), S( -35,  -25),
  S(  -9,   82), S(  23,   62), S(  49,   26), S(  78,   -1), S(  61,   -5), S(  64,    5), S(  24,   55), S(  -3,   48),
  S(  86,  111), S(  78,   91), S(  47,   73), S(  36,   48), S(  44,   35), S(   4,   34), S( -11,   76), S( -13,   78),
};
inline const std::array knight_psqt = {
  S( -40,  -26), S( -56,  -44), S( -42,  -27), S( -29,  -22), S( -33,  -18), S(  -2,  -30), S( -36,  -29), S( -29,  -37),
  S( -48,  -30), S( -41,  -24), S( -33,   -9), S(  -6,    8), S(  12,    4), S(   7,  -22), S( -16,  -15), S( -15,  -26),
  S( -65,  -17), S( -22,    5), S(  -7,   12), S(  15,   37), S(  25,   22), S(  34,    9), S(  40,   -9), S( -30,  -24),
  S( -30,    0), S(   0,   11), S(  23,   37), S(  37,   38), S(  53,   46), S(  54,   19), S(  39,   12), S(  10,  -16),
  S(  -2,   14), S(  19,   19), S(  30,   44), S(  79,   52), S(  39,   57), S( 112,   25), S(  29,   27), S(  57,    0),
  S( -23,  -14), S(  -2,   15), S(  40,   33), S(  68,   31), S(  67,   27), S(  65,   46), S(  25,   18), S(   5,   -1),
  S( -67,  -21), S( -40,   -3), S(   3,   -2), S(  29,   20), S(  14,    5), S(  24,    4), S( -34,  -20), S(  -8,  -28),
  S(-143,  -67), S( -24,  -19), S( -41,  -15), S(  -6,    2), S(   0,  -10), S( -51,  -25), S(  -8,   -8), S( -24,  -39),
};
inline const std::array bishop_psqt = {
  S( -12,  -38), S( -12,  -35), S(  -7,  -18), S( -16,  -15), S( -17,  -31), S( -30,    1), S( -13,  -24), S(  -1,   -8),
  S(   9,  -22), S(   5,  -10), S(  10,   -9), S( -16,    8), S(  14,   -4), S(  18,  -21), S(  54,  -21), S(  -3,  -19),
  S( -18,  -11), S(  20,   10), S(  14,   20), S(   4,   12), S(   3,   47), S(  26,    8), S(  20,   -9), S(   6,   -5),
  S( -16,  -12), S( -17,   23), S(  14,   22), S(  24,   49), S(  35,   18), S(  14,   20), S(   7,   -2), S(  -7,  -20),
  S( -18,    2), S( -11,   18), S(  -1,   28), S(  57,   30), S(  25,   36), S(  15,   12), S(   2,   10), S(  -7,  -13),
  S( -21,  -15), S(   1,   20), S(   0,   18), S(  30,    5), S(  54,   18), S(  54,   38), S(  43,   21), S(  15,  -13),
  S( -37,   -4), S( -31,    7), S(  -7,    0), S( -22,   -9), S( -27,    0), S(   0,    1), S( -19,   -4), S( -37,  -25),
  S( -15,   -9), S( -17,   -4), S( -33,  -17), S( -18,  -11), S( -18,   -2), S( -54,  -12), S( -12,  -15), S(   0,   -8),
};
inline const std::array rook_psqt = {
  S( -30,  -27), S( -19,  -29), S(  -6,  -20), S(   9,  -33), S(  30,  -53), S(  20,  -46), S( -28,  -15), S( -13,  -71),
  S( -73,  -18), S( -45,  -22), S( -35,  -12), S( -22,  -31), S( -19,  -37), S(   4,  -50), S(   0,  -47), S( -89,  -47),
  S( -56,    1), S( -43,   -3), S( -35,    5), S( -29,  -19), S( -22,  -23), S(  -8,  -28), S(  15,  -34), S( -17,  -37),
  S( -46,   13), S( -45,   14), S( -22,   10), S(  -3,   -6), S( -14,  -15), S( -11,  -13), S( -11,  -13), S( -27,  -33),
  S( -41,   40), S( -28,   31), S(   0,   27), S(  11,   18), S(  12,   -5), S(  28,    4), S(  10,   -5), S(  -1,    3),
  S( -20,   45), S(  15,   33), S(  10,   34), S(  34,   21), S(  60,    8), S(  61,   16), S(  33,   23), S(   8,    2),
  S(  -7,   52), S(  -5,   57), S(  38,   46), S(  60,   40), S(  50,   31), S(  78,   18), S(  30,   36), S(  60,   23),
  S(  18,   12), S(  19,   17), S(  18,   21), S(  33,   20), S(  34,    8), S(  13,   22), S(  22,   24), S(  40,   17),
};
inline const std::array queen_psqt = {
  S( -31,  -29), S( -25,  -34), S( -11,  -37), S(  13,  -41), S( -19,  -43), S( -65,  -63), S( -41,  -41), S( -41,  -36),
  S( -38,  -31), S( -23,  -12), S(  -5,  -14), S(   0,  -12), S(   9,  -15), S(   5,  -36), S(  -4,  -41), S( -31,  -30),
  S( -36,  -27), S( -13,   -6), S( -14,   12), S( -10,    8), S(  -1,   41), S(  13,    8), S(  20,    0), S(  -8,  -16),
  S( -25,    3), S( -33,    1), S( -10,   18), S(  -5,   57), S(  10,   36), S(   2,   31), S(  19,   12), S(  -6,    0),
  S( -24,    3), S( -20,   42), S(  -4,   26), S(   0,   64), S(  25,   57), S(  30,   26), S(  19,   44), S(  22,  -19),
  S( -20,   -7), S(  -4,   15), S(  10,   25), S(  11,   35), S(  42,   30), S(  65,   30), S(  64,   21), S(  32,  -10),
  S( -26,  -19), S( -30,   18), S(   0,   26), S(   3,   30), S(   5,   16), S(  53,   13), S(  46,   16), S(  81,    0),
  S( -26,  -46), S(  -9,  -22), S(   2,  -17), S(  -3,  -16), S(   5,  -13), S(  20,    3), S(  11,  -16), S(  22,  -17),
};
inline const std::array king_psqt = {
  S( -28,  -45), S(  21,  -60), S(  37,  -38), S( -64,  -53), S(  33,  -86), S(  -8,  -58), S( 124,  -91), S(  85, -118),
  S(  -1,  -39), S(   1,  -31), S(  -2,   -6), S( -40,    4), S( -29,    6), S(  32,  -11), S(  89,  -39), S(  89,  -64),
  S( -25,  -53), S(   1,  -18), S( -22,   -3), S( -35,   16), S( -48,   21), S( -18,    9), S(  18,  -20), S( -43,  -35),
  S( -18,  -26), S( -18,  -10), S( -26,   17), S( -22,   20), S( -20,   23), S( -34,   24), S( -32,   -3), S( -53,  -36),
  S( -11,   -8), S(   0,   32), S(   0,   37), S(   0,   38), S(  -3,   49), S(   0,   61), S(  -3,   42), S( -26,  -14),
  S(   0,   11), S(   2,   34), S(   8,   57), S(   9,   49), S(  10,   57), S(  12,   83), S(  11,   61), S(   0,   20),
  S(  -1,   -7), S(   4,   19), S(   8,   36), S(   6,   26), S(   8,   27), S(   9,   42), S(   3,   31), S(   0,    1),
  S(   0,   -7), S(   2,    0), S(   2,    8), S(   0,    2), S(   1,    2), S(   2,    7), S(   0,    3), S(   0,   -4),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
