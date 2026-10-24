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
inline const pair pawn_material = S(136, 265);
inline const pair knight_material = S(561, 680);
inline const pair bishop_material = S(589, 745);
inline const pair rook_material = S(770, 1224);
inline const pair queen_material = S(1665, 1890);

inline const pair bishop_pair = S(113, 140);

inline const std::array knight_mobility = {
  S(-50, -72), S(-16, -42), S(-3, -21), S(3, 0), S(8, 17), S(14, 26), S(13, 27), S(14, 32), S(16, 32),
};
inline const std::array bishop_mobility = {
  S(-65, -88), S(-32, -52), S(-18, -24), S(-7, -16), S(-4, 0), S(7, 9), S(8, 20), S(7, 23), S(20, 28), S(21, 31), S(24, 21), S(29, 27), S(2, -1), S(6, 22),
};
inline const std::array rook_mobility = {
  S(-72, -78), S(-51, -39), S(-42, -23), S(-29, -13), S(-23, -5), S(-11, -7), S(-5, 2), S(6, 5), S(15, 10), S(26, 20), S(30, 18), S(34, 28), S(36, 31), S(53, 14), S(32, 37),
};
inline const std::array queen_mobility = {
  S(-31, -63), S(-24, -61), S(-15, -80), S(-12, -67), S(-4, -53), S(-1, -34), S(4, -29), S(4, -5), S(3, 10), S(6, 25), S(7, 36), S(9, 48), S(9, 45), S(13, 54), S(13, 57), S(11, 64), S(20, 61), S(21, 51), S(29, 50), S(31, 33), S(36, 27), S(27, 31), S(12, 0), S(0, -4), S(-30, -34), S(-40, -45), S(-51, -58), S(-53, -61),
};

inline const pair pawn_threat_knight = S(76, 22);
inline const pair pawn_threat_bishop = S(86, 37);
inline const pair pawn_threat_rook = S(56, 28);
inline const pair pawn_threat_queen = S(42, -4);

inline const pair pp_threat_knight = S(30, 18);
inline const pair pp_threat_bishop = S(19, 0);
inline const pair pp_threat_rook = S(10, 14);
inline const pair pp_threat_queen = S(26, -47);

inline const pair knight_threat_pawn = S(9, 28);
inline const pair knight_threat_bishop = S(56, 32);
inline const pair knight_threat_rook = S(94, -10);
inline const pair knight_threat_queen = S(37, -15);

inline const pair bishop_threat_pawn = S(7, 12);
inline const pair bishop_threat_knight = S(33, 25);
inline const pair bishop_threat_rook = S(81, 18);
inline const pair bishop_threat_queen = S(81, 36);

inline const pair rook_threat_pawn = S(2, 38);
inline const pair rook_threat_knight = S(46, 27);
inline const pair rook_threat_bishop = S(51, 28);
inline const pair rook_threat_queen = S(78, 6);

inline const pair queen_threat_pawn = S(-2, 40);
inline const pair queen_threat_knight = S(8, 54);
inline const pair queen_threat_bishop = S(5, 73);
inline const pair queen_threat_rook = S(-10, 43);

inline const pair king_threat_pawn = S(19, 78);
inline const pair king_threat_knight = S(-10, 10);
inline const pair king_threat_bishop = S(13, 1);
inline const pair king_threat_rook = S(-43, -5);

inline const pair knight_check_threat = S(-31, -6);
inline const pair bishop_check_threat = S(-20, -26);
inline const pair rook_check_threat = S(-56, -15);
inline const pair queen_check_threat = S(-20, -75);

inline const pair hanging = S(21, 40);

inline const std::array passed_pawn = {
  S(-30, -101), S(-43, -89), S(-53, 2), S(-10, 87), S(62, 151), S(160, 244),
};
inline const std::array defended_passed_pawn = {
  S(8, -7), S(15, 25), S(27, 37), S(16, 74), S(51, 109), S(50, 149),
};
inline const std::array blocked_passed_pawn = {
  S(-1, -7), S(7, -2), S(-12, -16), S(-24, -32), S(-17, -65), S(-26, -96),
};
inline const std::array friendly_passer_tropism = {
  S(3, 71), S(5, 68), S(15, 40), S(11, 28), S(17, 32), S(24, 30), S(8, 24),
};
inline const std::array enemy_passer_tropism = {
  S(-25, -1), S(7, 14), S(17, 46), S(28, 56), S(27, 55), S(18, 58), S(11, 65),
};

inline const pair isolated_pawn = S(-7, -5);
inline const pair doubled_pawn = S(-4, -40);
inline const std::array defended_pawn = {
  S(16, 8), S(21, 4), S(19, 17), S(85, 59), S(63, 105),
};
inline const std::array phalanx = {
  S(5, -15), S(18, 4), S(25, 37), S(78, 86), S(53, 90), S(7, 20),
};

inline const std::array shelter_centre = {
  S(-30, -11), S(16, -18), S(-3, -10), S(0, -16), S(-8, -1), S(1, 10), S(22, 48),
};
inline const std::array shelter_mid = {
  S(-51, -12), S(27, -26), S(16, -19), S(15, -23), S(1, 0), S(-14, 18), S(4, 63),
};
inline const std::array shelter_edge = {
  S(-35, -15), S(20, -35), S(16, -22), S(11, -20), S(-7, -1), S(-19, 30), S(13, 65),
};

inline const std::array king_ring = {
  S(-38, 9), S(-35, 11), S(-19, 0), S(-10, 9), S(8, 9),
};

inline const std::array pawn_psqt = {
  S( -58,   -4), S( -26,   -8), S( -44,  -14), S( -53,  -20), S( -48,   -1), S(  -6,  -30), S(  42,  -59), S( -45,  -58),
  S( -53,  -24), S( -47,  -24), S( -26,  -49), S( -41,  -36), S( -43,  -34), S( -63,  -32), S(  14,  -74), S( -42,  -69),
  S( -62,   -8), S( -50,  -19), S( -21,  -46), S( -12,  -65), S( -17,  -66), S( -29,  -52), S( -25,  -46), S( -51,  -56),
  S( -46,   13), S(   4,   -3), S( -15,  -25), S(  23,  -59), S(  19,  -66), S(  10,  -58), S(  24,  -36), S( -33,  -46),
  S( -17,   85), S(  17,   77), S(  52,   41), S(  73,   12), S(  64,    7), S(  51,    3), S(  30,   55), S(  -4,   35),
  S( 104,  141), S( 116,  149), S( 100,  131), S( 102,  115), S(  87,   82), S(  23,   63), S(  15,   96), S(  10,   91),
};
inline const std::array knight_psqt = {
  S( -41,  -26), S( -45,  -41), S( -39,  -19), S( -26,  -20), S( -33,  -17), S(  -6,  -27), S( -34,  -30), S( -19,  -30),
  S( -39,  -32), S( -42,  -18), S( -30,   -6), S(  -7,   11), S(  15,    2), S(   5,  -17), S( -14,  -22), S(  -2,  -23),
  S( -55,  -18), S( -15,    3), S(   0,    8), S(  21,   29), S(  29,   21), S(  37,    0), S(  37,  -13), S( -23,  -19),
  S( -28,   -2), S(  -4,    9), S(  20,   36), S(  41,   37), S(  26,   46), S(  52,   16), S(  19,   11), S(  16,  -11),
  S(  -7,   13), S(   7,   23), S(  22,   42), S(  47,   49), S(  39,   52), S(  87,   24), S(  32,   20), S(  48,   -4),
  S( -21,   -9), S(   0,   12), S(  27,   24), S(  48,   21), S(  67,   18), S(  56,   38), S(  20,   14), S(   2,   -1),
  S( -54,  -13), S( -31,   -5), S(   4,   -1), S(  24,   21), S(  13,    8), S(  40,   13), S( -23,  -17), S(  -7,  -19),
  S(-140,  -61), S( -19,  -20), S( -30,  -16), S(  -5,    0), S(   5,   -3), S( -44,  -14), S(  -5,   -6), S( -22,  -39),
};
inline const std::array bishop_psqt = {
  S( -17,  -35), S( -20,  -29), S( -13,  -16), S( -20,   -8), S( -22,  -28), S( -35,    1), S( -12,  -23), S(  -8,   -4),
  S(   8,  -21), S(   4,   -5), S(   6,  -12), S( -19,    9), S(   8,   -4), S(   1,  -17), S(  42,  -25), S( -16,  -20),
  S( -17,   -9), S(  15,   11), S(  13,   18), S(  -6,    8), S(  -1,   36), S(  18,    1), S(  11,  -12), S(   2,   -6),
  S( -10,  -10), S( -17,   16), S(   8,   20), S(  23,   44), S(  20,   13), S(  13,   11), S(   3,   -6), S(  -2,  -21),
  S( -11,    0), S(  -8,   17), S(   6,   31), S(  42,   28), S(  33,   33), S(  15,   10), S(  14,    7), S(  -3,  -12),
  S( -15,   -3), S(   3,   18), S(   3,   21), S(  34,    6), S(  53,   15), S(  54,   36), S(  40,    9), S(  24,   -6),
  S( -30,    0), S( -27,    3), S(  -5,    3), S( -11,   -6), S( -19,    0), S(  15,   -1), S(  -3,   -8), S( -15,  -25),
  S( -20,    1), S( -11,   -4), S( -27,  -13), S( -13,   -6), S( -14,    0), S( -50,  -14), S( -11,   -7), S(  -2,   -7),
};
inline const std::array rook_psqt = {
  S( -23,   -4), S(  -8,   -9), S(   5,   -3), S(  16,  -21), S(  27,  -40), S(  19,  -34), S( -30,    2), S(  -8,  -53),
  S( -60,    1), S( -37,   -6), S( -26,    7), S( -16,  -14), S( -21,  -24), S(   0,  -30), S(  -8,  -37), S( -77,  -32),
  S( -47,    8), S( -36,    6), S( -32,   15), S( -18,   -7), S( -12,  -13), S(   5,  -21), S(   8,  -27), S( -14,  -32),
  S( -38,   18), S( -38,   11), S( -20,    8), S(   1,   -7), S( -13,  -15), S(  -1,  -16), S( -16,  -11), S( -18,  -29),
  S( -35,   31), S( -26,   22), S(  -2,   19), S(  14,    3), S(  10,  -17), S(  40,  -11), S(   0,   -5), S(   0,   -7),
  S( -13,   31), S(  12,   15), S(   9,   20), S(  21,    2), S(  43,   -7), S(  44,   -4), S(   9,   15), S(  -7,    1),
  S(  -7,   35), S(  -9,   40), S(  34,   22), S(  53,   17), S(  34,    8), S(  56,   13), S(  19,   33), S(  49,   13),
  S(  12,   11), S(  14,   13), S(  23,   16), S(  36,   14), S(  37,   11), S(  15,   17), S(  21,   24), S(  37,   12),
};
inline const std::array queen_psqt = {
  S( -10,   -5), S( -15,  -19), S(   0,  -12), S(  18,   -3), S( -12,  -34), S( -61,  -54), S( -38,  -40), S( -38,  -31),
  S( -23,  -16), S( -10,    3), S(   0,    9), S(   4,   17), S(  10,   13), S(  13,  -25), S(  -5,  -28), S( -16,  -22),
  S( -28,   -7), S(  -6,   10), S(  -2,   30), S(   0,   25), S(   3,   40), S(  18,   11), S(  28,    3), S(  -4,  -11),
  S( -18,   -5), S( -23,    4), S(  -7,   25), S(   2,   44), S(  12,   12), S(  16,    8), S(  14,    4), S(   5,    6),
  S( -23,   -5), S( -18,   16), S(  -8,   13), S(  -1,   33), S(  17,   23), S(  27,   -8), S(  22,   17), S(  32,  -37),
  S( -23,  -12), S( -18,   -6), S(  -7,   -2), S(  -7,    9), S(  22,   14), S(  35,    6), S(  43,    5), S(  19,   -7),
  S( -20,  -12), S( -41,   -1), S( -21,   11), S( -32,    4), S( -18,   -3), S(  35,    3), S(  38,   11), S(  65,   -3),
  S( -22,  -26), S(  -9,   -9), S(   5,   -2), S(   2,    0), S(  17,    2), S(  20,    7), S(  15,   -3), S(  30,   10),
};
inline const std::array king_psqt = {
  S( -33,  -42), S(   9,  -49), S(  36,  -36), S( -64,  -44), S(  28,  -74), S( -12,  -48), S( 102,  -83), S(  61, -107),
  S( -13,  -36), S(   2,  -25), S(   2,   -5), S( -29,    5), S( -20,   10), S(  33,   -7), S(  78,  -37), S(  73,  -66),
  S( -23,  -47), S(   0,  -21), S( -10,    2), S( -11,   21), S( -24,   22), S(  -7,   17), S(  17,  -16), S( -48,  -28),
  S( -17,  -20), S( -22,   -5), S( -14,   15), S( -11,   24), S(  -7,   30), S( -27,   27), S( -31,    0), S( -52,  -37),
  S( -11,   -4), S(   0,   21), S(   1,   35), S(   0,   40), S(  -2,   48), S(   4,   54), S(  -9,   29), S( -25,  -13),
  S(  -2,   12), S(   2,   24), S(   7,   47), S(   8,   47), S(   9,   51), S(  12,   69), S(   8,   46), S(  -2,   19),
  S(   0,   -5), S(   2,   15), S(   4,   22), S(   7,   20), S(   8,   25), S(  10,   39), S(   1,   21), S(  -1,    2),
  S(  -1,  -10), S(   0,   -8), S(   0,    5), S(   1,    2), S(   1,    4), S(   1,    1), S(   0,    0), S(   0,   -1),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
