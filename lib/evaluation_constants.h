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
inline const pair pawn_material = S(133, 252);
inline const pair knight_material = S(563, 680);
inline const pair bishop_material = S(578, 752);
inline const pair rook_material = S(774, 1228);
inline const pair queen_material = S(1670, 1997);

inline const pair bishop_pair = S(112, 148);

inline const std::array knight_mobility = {
  S(-50, -72), S(-18, -41), S(-2, -19), S(6, 0), S(8, 17), S(13, 28), S(13, 29), S(12, 32), S(16, 26),
};
inline const std::array bishop_mobility = {
  S(-61, -89), S(-35, -51), S(-16, -19), S(-2, -14), S(3, 3), S(8, 16), S(12, 22), S(13, 25), S(16, 27), S(21, 31), S(22, 17), S(21, 21), S(-2, -5), S(0, 14),
};
inline const std::array rook_mobility = {
  S(-76, -82), S(-53, -42), S(-44, -28), S(-27, -12), S(-30, -7), S(-13, -2), S(-7, 0), S(6, 5), S(13, 12), S(26, 18), S(26, 21), S(36, 29), S(45, 36), S(60, 16), S(39, 37),
};
inline const std::array queen_mobility = {
  S(-37, -67), S(-29, -67), S(-19, -86), S(-10, -74), S(-6, -62), S(0, -42), S(3, -36), S(2, -11), S(5, 5), S(8, 21), S(7, 32), S(11, 46), S(15, 46), S(16, 58), S(14, 59), S(14, 69), S(17, 63), S(20, 56), S(28, 59), S(29, 44), S(34, 37), S(26, 38), S(14, 8), S(3, 2), S(-28, -32), S(-37, -43), S(-52, -62), S(-53, -64),
};

inline const pair pawn_threat_knight = S(83, 38);
inline const pair pawn_threat_bishop = S(86, 51);
inline const pair pawn_threat_rook = S(63, 48);
inline const pair pawn_threat_queen = S(48, -1);

inline const pair knight_threat_pawn = S(-11, 17);
inline const pair knight_threat_bishop = S(57, 48);
inline const pair knight_threat_rook = S(97, 15);
inline const pair knight_threat_queen = S(48, -5);

inline const pair bishop_threat_pawn = S(-6, 7);
inline const pair bishop_threat_knight = S(30, 26);
inline const pair bishop_threat_rook = S(82, 41);
inline const pair bishop_threat_queen = S(80, 29);

inline const pair rook_threat_pawn = S(-13, 34);
inline const pair rook_threat_knight = S(24, 26);
inline const pair rook_threat_bishop = S(41, 19);
inline const pair rook_threat_queen = S(98, 9);

inline const std::array passed_pawn = {
  S(-29, -105), S(-44, -91), S(-50, 6), S(-10, 84), S(52, 147), S(154, 244),
};
inline const std::array defended_passed_pawn = {
  S(9, -8), S(15, 29), S(26, 37), S(15, 74), S(47, 106), S(53, 152),
};
inline const std::array blocked_passed_pawn = {
  S(-3, -13), S(10, -5), S(-8, -16), S(-21, -31), S(-17, -64), S(-32, -96),
};
inline const std::array friendly_passer_tropism = {
  S(6, 69), S(2, 66), S(11, 42), S(8, 27), S(13, 29), S(22, 28), S(6, 23),
};
inline const std::array enemy_passer_tropism = {
  S(-57, -52), S(12, 30), S(22, 47), S(32, 58), S(28, 65), S(23, 66), S(10, 69),
};

inline const pair isolated_pawn = S(-9, -5);
inline const std::array defended_pawn = {
  S(20, 19), S(28, 17), S(26, 34), S(88, 80), S(68, 123),
};
inline const std::array phalanx = {
  S(5, -9), S(20, 9), S(28, 41), S(81, 91), S(55, 93), S(7, 21),
};

inline const std::array shelter_centre = {
  S(-32, -14), S(25, -16), S(-4, -6), S(4, -10), S(-7, 0), S(0, 6), S(16, 41),
};
inline const std::array shelter_mid = {
  S(-56, -16), S(38, -21), S(19, -16), S(20, -19), S(-1, 0), S(-18, 13), S(-1, 59),
};
inline const std::array shelter_edge = {
  S(-42, -14), S(24, -33), S(20, -15), S(13, -21), S(-6, -3), S(-18, 26), S(8, 61),
};

inline const std::array king_ring = {
  S(-38, 13), S(-30, 18), S(-25, 5), S(-31, 12), S(-8, -85),
};

inline const std::array pawn_psqt = {
  S( -57,    2), S( -17,   -1), S( -37,  -10), S( -43,  -16), S( -42,    4), S(   6,  -25), S(  54,  -56), S( -44,  -54),
  S( -59,  -22), S( -43,  -20), S( -24,  -48), S( -39,  -37), S( -33,  -30), S( -63,  -35), S(  16,  -78), S( -43,  -71),
  S( -64,   -3), S( -50,  -15), S( -21,  -43), S( -11,  -61), S( -21,  -62), S( -27,  -50), S( -25,  -44), S( -52,  -50),
  S( -49,   14), S(   5,    0), S( -18,  -26), S(  16,  -55), S(  18,  -60), S(  10,  -59), S(  22,  -39), S( -29,  -39),
  S( -16,   82), S(  21,   74), S(  50,   35), S(  77,    4), S(  63,    2), S(  53,   -1), S(  31,   49), S(  -2,   31),
  S( 102,  137), S( 114,  146), S(  94,  127), S(  97,  108), S(  80,   74), S(  11,   52), S( -10,   87), S(   1,   86),
};
inline const std::array knight_psqt = {
  S( -45,  -31), S( -54,  -44), S( -41,  -23), S( -31,  -22), S( -34,  -18), S(  -4,  -27), S( -40,  -33), S( -25,  -33),
  S( -47,  -36), S( -48,  -22), S( -38,  -10), S(  -8,    7), S(   7,    1), S(  10,  -19), S( -15,  -23), S(  -9,  -28),
  S( -66,  -23), S( -19,    2), S(  -5,   13), S(  16,   34), S(  25,   26), S(  32,    5), S(  37,  -10), S( -32,  -21),
  S( -35,   -5), S(  -6,    8), S(  19,   40), S(  34,   42), S(  47,   50), S(  53,   18), S(  38,   14), S(   7,  -14),
  S( -10,   10), S(  12,   23), S(  30,   48), S(  75,   57), S(  39,   55), S( 116,   28), S(  35,   23), S(  57,   -6),
  S( -26,  -10), S(  -1,   11), S(  42,   34), S(  68,   34), S(  74,   26), S(  71,   46), S(  27,   17), S(   9,    0),
  S( -62,  -19), S( -38,   -7), S(   4,   -2), S(  27,   22), S(  17,    7), S(  33,    9), S( -30,  -21), S(  -9,  -23),
  S(-147,  -67), S( -21,  -23), S( -32,  -17), S(  -6,    1), S(   4,   -4), S( -49,  -18), S(  -5,   -7), S( -25,  -42),
};
inline const std::array bishop_psqt = {
  S( -17,  -39), S( -15,  -32), S( -10,  -23), S( -17,  -11), S( -17,  -30), S( -33,    2), S( -10,  -24), S(  -4,   -7),
  S(  10,  -23), S(   6,  -11), S(  10,  -14), S( -15,    5), S(  12,   -5), S(  16,  -15), S(  57,  -21), S( -13,  -23),
  S( -20,  -14), S(  21,   12), S(  16,   21), S(   3,   12), S(   4,   46), S(  27,    8), S(  18,   -8), S(   9,   -8),
  S( -10,  -15), S( -21,   19), S(  12,   26), S(  27,   51), S(  36,   19), S(  13,   17), S(   5,   -4), S(  -3,  -24),
  S( -17,   -4), S( -11,   20), S(   0,   34), S(  58,   39), S(  27,   38), S(  19,   17), S(  -1,    9), S(  -6,  -11),
  S( -17,   -8), S(   4,   19), S(   3,   23), S(  31,   10), S(  56,   17), S(  44,   36), S(  48,   14), S(  12,  -11),
  S( -38,   -7), S( -29,    2), S(  -7,    1), S( -15,   -5), S( -30,   -1), S(   7,   -2), S( -19,  -12), S( -37,  -29),
  S( -20,   -4), S( -13,   -4), S( -28,  -14), S( -17,   -8), S( -16,    0), S( -59,  -19), S( -13,   -9), S( -10,  -12),
};
inline const std::array rook_psqt = {
  S( -21,  -14), S( -15,  -23), S(   0,  -14), S(  13,  -22), S(  34,  -42), S(  25,  -39), S( -22,   -6), S(  -5,  -59),
  S( -65,   -5), S( -43,  -16), S( -31,    2), S( -20,  -17), S( -23,  -25), S(   6,  -37), S(   4,  -41), S( -78,  -38),
  S( -48,    5), S( -41,    1), S( -39,   11), S( -28,   -9), S( -19,  -19), S(  -2,  -21), S(  14,  -31), S( -14,  -35),
  S( -43,   13), S( -44,    9), S( -28,   10), S(  -5,   -6), S( -18,  -16), S( -10,  -16), S( -13,  -13), S( -20,  -32),
  S( -38,   29), S( -28,   19), S(  -9,   17), S(  10,    7), S(   6,  -19), S(  29,   -8), S(   6,   -7), S(   3,   -7),
  S( -14,   35), S(  12,   17), S(   8,   23), S(  22,    5), S(  45,   -2), S(  56,    3), S(  23,   19), S(   6,    4),
  S( -13,   46), S( -10,   50), S(  34,   34), S(  57,   29), S(  44,   23), S(  68,   21), S(  33,   38), S(  59,   20),
  S(  11,   17), S(  11,   17), S(  22,   21), S(  33,   18), S(  34,   13), S(  17,   22), S(  19,   27), S(  40,   16),
};
inline const std::array queen_psqt = {
  S( -28,  -30), S( -29,  -35), S( -12,  -34), S(  14,  -40), S( -19,  -42), S( -70,  -65), S( -46,  -47), S( -49,  -39),
  S( -38,  -31), S( -25,  -17), S( -10,  -15), S(  -2,  -12), S(   8,   -7), S(   8,  -38), S(  -6,  -36), S( -25,  -29),
  S( -41,  -24), S( -18,   -3), S( -10,   12), S(  -9,    7), S(  -5,   45), S(  11,    6), S(  20,    2), S( -10,  -19),
  S( -26,   -2), S( -33,    0), S( -11,   22), S(  -3,   51), S(  14,   29), S(   5,   27), S(  15,    9), S(  -7,    3),
  S( -25,    1), S( -17,   38), S(  -9,   28), S(   3,   60), S(  23,   57), S(  30,   19), S(  20,   41), S(  22,  -26),
  S( -18,  -10), S(  -3,    8), S(  15,   25), S(  14,   30), S(  45,   36), S(  61,   28), S(  61,   22), S(  28,  -10),
  S( -23,  -21), S( -30,   11), S(   2,   29), S(   3,   33), S(  13,   18), S(  61,   16), S(  51,   17), S(  75,   -5),
  S( -22,  -42), S( -13,  -17), S(   1,   -9), S(  -2,  -12), S(  13,   -7), S(  21,    5), S(  15,   -5), S(  23,   -4),
};
inline const std::array king_psqt = {
  S( -29,  -43), S(  19,  -59), S(  43,  -45), S( -56,  -56), S(  37,  -87), S(   0,  -61), S( 120,  -95), S(  80, -117),
  S(  -7,  -39), S(   5,  -31), S(   2,  -11), S( -34,    2), S( -22,    4), S(  33,   -9), S(  88,  -40), S(  86,  -64),
  S( -21,  -46), S(   0,  -26), S( -20,   -1), S( -28,   17), S( -40,   22), S( -19,   13), S(  15,  -16), S( -45,  -28),
  S( -19,  -22), S( -27,   -4), S( -23,   12), S( -20,   21), S( -19,   25), S( -38,   25), S( -37,    2), S( -55,  -36),
  S( -13,   -5), S(  -1,   29), S(  -2,   38), S(  -3,   40), S(  -7,   50), S(   1,   60), S( -10,   38), S( -23,   -7),
  S(   0,   16), S(   3,   34), S(   6,   53), S(   6,   51), S(   8,   55), S(  13,   80), S(  11,   61), S(  -1,   24),
  S(   0,   -3), S(   4,   22), S(   5,   26), S(   6,   21), S(   8,   28), S(  10,   44), S(   3,   29), S(   0,    4),
  S(  -1,   -9), S(   0,   -7), S(   1,    6), S(   0,    2), S(   1,    5), S(   2,    3), S(   0,    1), S(   0,    0),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
