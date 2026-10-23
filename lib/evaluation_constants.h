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
inline const pair pawn_material = S(137, 269);
inline const pair knight_material = S(557, 677);
inline const pair bishop_material = S(587, 748);
inline const pair rook_material = S(772, 1222);
inline const pair queen_material = S(1671, 1909);

inline const pair bishop_pair = S(112, 139);

inline const std::array knight_mobility = {
  S(-50, -72), S(-18, -42), S(-3, -22), S(5, 0), S(8, 16), S(12, 27), S(14, 30), S(14, 32), S(17, 31),
};
inline const std::array bishop_mobility = {
  S(-66, -88), S(-33, -54), S(-15, -24), S(-7, -15), S(0, 0), S(6, 13), S(9, 22), S(8, 23), S(17, 25), S(21, 30), S(23, 21), S(27, 25), S(1, -1), S(6, 22),
};
inline const std::array rook_mobility = {
  S(-71, -78), S(-49, -40), S(-41, -23), S(-25, -11), S(-25, -4), S(-10, -5), S(-4, 0), S(3, 3), S(13, 8), S(23, 14), S(28, 20), S(33, 26), S(36, 32), S(54, 17), S(34, 40),
};
inline const std::array queen_mobility = {
  S(-28, -63), S(-22, -61), S(-15, -80), S(-8, -66), S(0, -51), S(1, -31), S(6, -25), S(5, 0), S(8, 18), S(6, 31), S(8, 42), S(6, 53), S(14, 52), S(16, 59), S(13, 60), S(11, 65), S(18, 59), S(21, 48), S(26, 46), S(31, 29), S(34, 21), S(23, 21), S(7, -5), S(-4, -11), S(-33, -38), S(-43, -50), S(-52, -60), S(-54, -62),
};

inline const pair pawn_threat_knight = S(80, 23);
inline const pair pawn_threat_bishop = S(87, 37);
inline const pair pawn_threat_rook = S(56, 27);
inline const pair pawn_threat_queen = S(39, -8);

inline const pair pp_threat_knight = S(29, 18);
inline const pair pp_threat_bishop = S(21, -1);
inline const pair pp_threat_rook = S(8, 13);
inline const pair pp_threat_queen = S(30, -42);

inline const pair knight_threat_pawn = S(9, 31);
inline const pair knight_threat_bishop = S(55, 31);
inline const pair knight_threat_rook = S(95, -10);
inline const pair knight_threat_queen = S(39, -14);

inline const pair bishop_threat_pawn = S(7, 14);
inline const pair bishop_threat_knight = S(34, 25);
inline const pair bishop_threat_rook = S(80, 17);
inline const pair bishop_threat_queen = S(72, 25);

inline const pair rook_threat_pawn = S(5, 39);
inline const pair rook_threat_knight = S(44, 24);
inline const pair rook_threat_bishop = S(50, 27);
inline const pair rook_threat_queen = S(78, -1);

inline const pair king_threat_pawn = S(19, 77);
inline const pair king_threat_knight = S(-10, 9);
inline const pair king_threat_bishop = S(12, 0);
inline const pair king_threat_rook = S(-42, -6);

inline const pair knight_check_threat = S(-32, -5);
inline const pair bishop_check_threat = S(-24, -25);
inline const pair rook_check_threat = S(-56, -18);
inline const pair queen_check_threat = S(-20, -76);

inline const pair hanging = S(28, 44);

inline const std::array passed_pawn = {
  S(-30, -100), S(-44, -90), S(-50, 4), S(-9, 89), S(62, 155), S(158, 244),
};
inline const std::array defended_passed_pawn = {
  S(10, -2), S(14, 24), S(25, 36), S(16, 75), S(49, 108), S(50, 149),
};
inline const std::array blocked_passed_pawn = {
  S(0, -4), S(7, -4), S(-13, -16), S(-24, -32), S(-17, -64), S(-27, -96),
};
inline const std::array friendly_passer_tropism = {
  S(2, 71), S(5, 67), S(18, 45), S(13, 29), S(13, 35), S(27, 30), S(6, 23),
};
inline const std::array enemy_passer_tropism = {
  S(-26, 0), S(8, 14), S(17, 46), S(29, 57), S(25, 59), S(20, 59), S(11, 65),
};

inline const pair isolated_pawn = S(-8, -4);
inline const pair doubled_pawn = S(-3, -39);
inline const std::array defended_pawn = {
  S(17, 9), S(21, 7), S(19, 19), S(84, 58), S(63, 105),
};
inline const std::array phalanx = {
  S(6, -12), S(18, 8), S(27, 35), S(78, 86), S(53, 90), S(7, 20),
};

inline const std::array shelter_centre = {
  S(-27, -11), S(17, -21), S(-6, -11), S(0, -17), S(-7, 1), S(2, 10), S(22, 48),
};
inline const std::array shelter_mid = {
  S(-52, -11), S(31, -27), S(15, -20), S(15, -22), S(0, -1), S(-14, 19), S(5, 64),
};
inline const std::array shelter_edge = {
  S(-37, -13), S(23, -35), S(16, -20), S(9, -22), S(-6, -2), S(-20, 29), S(14, 65),
};

inline const std::array king_ring = {
  S(-41, 7), S(-27, 9), S(-21, 1), S(-9, 9), S(8, 12),
};

inline const std::array pawn_psqt = {
  S( -57,   -3), S( -25,   -6), S( -43,  -16), S( -52,  -22), S( -50,   -1), S(  -3,  -29), S(  43,  -58), S( -42,  -55),
  S( -52,  -23), S( -45,  -23), S( -28,  -48), S( -39,  -36), S( -40,  -35), S( -65,  -29), S(  12,  -73), S( -39,  -71),
  S( -64,   -9), S( -50,  -21), S( -23,  -49), S( -12,  -66), S( -18,  -67), S( -30,  -52), S( -25,  -46), S( -49,  -55),
  S( -47,   15), S(   5,   -2), S( -14,  -24), S(  22,  -56), S(  18,  -67), S(   8,  -60), S(  23,  -37), S( -31,  -45),
  S( -16,   84), S(  16,   78), S(  50,   41), S(  71,   10), S(  63,    7), S(  50,    3), S(  29,   54), S(  -4,   34),
  S( 104,  140), S( 116,  148), S(  98,  132), S( 101,  114), S(  86,   81), S(  24,   62), S(  16,   97), S(  10,   91),
};
inline const std::array knight_psqt = {
  S( -41,  -26), S( -43,  -41), S( -38,  -19), S( -24,  -19), S( -32,  -18), S(  -5,  -28), S( -33,  -31), S( -19,  -29),
  S( -38,  -31), S( -43,  -18), S( -31,   -7), S(  -4,   12), S(  16,    2), S(   7,  -18), S( -15,  -23), S(  -3,  -23),
  S( -53,  -18), S( -13,    3), S(   1,    9), S(  21,   30), S(  29,   21), S(  38,   -1), S(  37,  -13), S( -24,  -20),
  S( -27,   -2), S(  -4,    9), S(  22,   36), S(  41,   37), S(  25,   45), S(  53,   16), S(  19,   11), S(  17,  -12),
  S(  -7,   13), S(   6,   22), S(  21,   41), S(  48,   49), S(  37,   51), S(  86,   24), S(  30,   21), S(  47,   -4),
  S( -21,   -8), S(   0,   13), S(  25,   24), S(  47,   21), S(  65,   17), S(  55,   38), S(  19,   15), S(   2,    0),
  S( -54,  -13), S( -31,   -4), S(   3,    0), S(  23,   21), S(  13,    9), S(  39,   14), S( -23,  -17), S(  -7,  -18),
  S(-141,  -61), S( -18,  -20), S( -30,  -16), S(  -5,    0), S(   5,   -2), S( -44,  -14), S(  -5,   -7), S( -21,  -39),
};
inline const std::array bishop_psqt = {
  S( -19,  -36), S( -20,  -29), S( -12,  -16), S( -20,   -7), S( -23,  -29), S( -37,    1), S( -12,  -23), S(  -8,   -5),
  S(   8,  -21), S(   6,   -4), S(   6,  -13), S( -20,    8), S(   7,   -3), S(   2,  -17), S(  44,  -21), S( -15,  -20),
  S( -17,  -10), S(  16,   11), S(  13,   18), S(  -5,    7), S(   0,   35), S(  20,    3), S(  13,  -13), S(   2,   -4),
  S(  -9,  -10), S( -16,   18), S(   6,   19), S(  24,   44), S(  21,   13), S(  13,   11), S(   2,   -7), S(  -2,  -20),
  S( -11,    0), S(  -8,   17), S(   4,   29), S(  42,   29), S(  33,   33), S(  14,   10), S(  14,    6), S(  -4,  -12),
  S( -14,   -2), S(   3,   18), S(   2,   22), S(  34,    6), S(  51,   15), S(  52,   36), S(  40,    9), S(  25,   -7),
  S( -29,    0), S( -26,    3), S(  -4,    3), S( -12,   -6), S( -19,   -1), S(  14,   -1), S(  -2,   -8), S( -16,  -25),
  S( -20,    1), S( -11,   -3), S( -27,  -13), S( -13,   -6), S( -14,    0), S( -50,  -15), S( -10,   -7), S(  -2,   -7),
};
inline const std::array rook_psqt = {
  S( -23,   -5), S(  -8,  -10), S(   2,   -6), S(  14,  -19), S(  29,  -43), S(  21,  -39), S( -30,    3), S(  -8,  -50),
  S( -61,    1), S( -38,   -7), S( -26,    6), S( -17,  -15), S( -19,  -23), S(   0,  -31), S(  -8,  -38), S( -77,  -33),
  S( -46,   10), S( -36,    7), S( -32,   16), S( -19,   -8), S( -14,  -15), S(   5,  -20), S(   6,  -29), S( -12,  -31),
  S( -38,   19), S( -37,   12), S( -19,   10), S(   2,   -6), S( -14,  -16), S(  -2,  -16), S( -17,  -11), S( -19,  -30),
  S( -37,   29), S( -26,   20), S(  -3,   18), S(  13,    2), S(  11,  -16), S(  40,  -11), S(   0,   -5), S(   0,   -8),
  S( -13,   33), S(  13,   17), S(   7,   19), S(  22,    4), S(  43,   -7), S(  44,   -4), S(   9,   16), S(  -7,    1),
  S(  -6,   38), S(  -8,   42), S(  34,   22), S(  52,   15), S(  35,    9), S(  56,   13), S(  18,   33), S(  49,   12),
  S(  12,   11), S(  13,   12), S(  23,   16), S(  36,   16), S(  36,   11), S(  15,   18), S(  20,   25), S(  37,   11),
};
inline const std::array queen_psqt = {
  S( -14,  -10), S( -18,  -23), S(  -8,  -20), S(  17,  -21), S( -16,  -41), S( -66,  -59), S( -41,  -42), S( -41,  -33),
  S( -27,  -19), S( -14,    0), S(  -3,    2), S(   2,    9), S(  10,    3), S(   9,  -29), S(  -9,  -31), S( -20,  -24),
  S( -31,  -10), S(  -9,    9), S(  -4,   28), S(  -3,   19), S(   0,   36), S(  19,   11), S(  25,    0), S(  -7,  -14),
  S( -20,   -6), S( -23,    3), S(  -8,   30), S(   1,   49), S(  13,   14), S(  16,    9), S(  15,    3), S(   2,    1),
  S( -24,   -5), S( -16,   19), S(  -7,   18), S(   2,   43), S(  19,   27), S(  29,   -2), S(  24,   18), S(  29,  -36),
  S( -24,  -12), S( -15,   -3), S(  -3,    2), S(  -3,   13), S(  26,   18), S(  35,    9), S(  45,    9), S(  17,   -9),
  S( -17,   -7), S( -38,    9), S( -14,   20), S( -26,   12), S( -13,    4), S(  42,   11), S(  39,   14), S(  66,   -2),
  S( -17,  -27), S(  -6,   -9), S(   7,   -2), S(   5,   -1), S(  21,    3), S(  20,    7), S(  18,   -3), S(  35,    9),
};
inline const std::array king_psqt = {
  S( -32,  -42), S(   9,  -49), S(  37,  -36), S( -65,  -44), S(  27,  -74), S( -11,  -47), S( 104,  -85), S(  57, -110),
  S( -13,  -37), S(   1,  -25), S(   3,   -5), S( -28,    7), S( -21,    7), S(  35,   -4), S(  78,  -39), S(  74,  -63),
  S( -23,  -47), S(   0,  -22), S(  -9,    4), S( -11,   22), S( -23,   24), S(  -6,   16), S(  16,  -17), S( -48,  -29),
  S( -17,  -20), S( -22,   -5), S( -14,   15), S( -11,   25), S(  -7,   29), S( -27,   27), S( -31,    0), S( -53,  -38),
  S( -12,   -5), S(   0,   21), S(   1,   36), S(   0,   39), S(  -2,   48), S(   4,   56), S(  -9,   28), S( -25,  -13),
  S(  -1,   12), S(   2,   24), S(   7,   47), S(   8,   47), S(   9,   50), S(  12,   69), S(   8,   45), S(  -2,   19),
  S(   0,   -5), S(   2,   15), S(   4,   22), S(   7,   20), S(   8,   25), S(  10,   39), S(   1,   22), S(  -1,    2),
  S(  -1,  -10), S(   0,   -8), S(   0,    5), S(   1,    2), S(   1,    5), S(   1,    1), S(   0,    0), S(   0,   -1),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
