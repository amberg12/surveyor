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
inline const pair pawn_material = S(130, 257);
inline const pair knight_material = S(561, 674);
inline const pair bishop_material = S(581, 745);
inline const pair rook_material = S(774, 1217);
inline const pair queen_material = S(1676, 1964);

inline const pair bishop_pair = S(117, 146);

inline const std::array knight_mobility = {
  S(-50, -76), S(-16, -38), S(0, -20), S(5, 0), S(10, 18), S(12, 27), S(10, 30), S(12, 33), S(16, 25),
};
inline const std::array bishop_mobility = {
  S(-64, -88), S(-34, -49), S(-13, -19), S(-2, -13), S(1, 0), S(8, 14), S(11, 22), S(13, 23), S(22, 26), S(16, 32), S(24, 15), S(25, 20), S(-8, -6), S(0, 20),
};
inline const std::array rook_mobility = {
  S(-78, -77), S(-56, -45), S(-41, -25), S(-29, -13), S(-26, -5), S(-10, -5), S(-6, -2), S(3, 4), S(14, 15), S(23, 16), S(32, 23), S(34, 29), S(44, 34), S(57, 14), S(39, 38),
};
inline const std::array queen_mobility = {
  S(-34, -65), S(-29, -65), S(-21, -80), S(-11, -74), S(-4, -60), S(-2, -49), S(6, -33), S(4, -13), S(5, 8), S(5, 21), S(10, 33), S(11, 49), S(16, 50), S(13, 59), S(17, 59), S(10, 72), S(19, 61), S(22, 58), S(27, 54), S(35, 41), S(35, 33), S(28, 33), S(10, 8), S(-4, -2), S(-28, -34), S(-37, -42), S(-52, -61), S(-53, -62),
};

inline const pair pawn_threat_knight = S(84, 41);
inline const pair pawn_threat_bishop = S(89, 53);
inline const pair pawn_threat_rook = S(61, 47);
inline const pair pawn_threat_queen = S(47, 4);

inline const pair knight_threat_pawn = S(-18, 15);
inline const pair knight_threat_bishop = S(56, 46);
inline const pair knight_threat_rook = S(103, 8);
inline const pair knight_threat_queen = S(48, -8);

inline const pair bishop_threat_pawn = S(-7, 4);
inline const pair bishop_threat_knight = S(32, 23);
inline const pair bishop_threat_rook = S(79, 38);
inline const pair bishop_threat_queen = S(78, 26);

inline const pair rook_threat_pawn = S(-12, 34);
inline const pair rook_threat_knight = S(24, 26);
inline const pair rook_threat_bishop = S(36, 19);
inline const pair rook_threat_queen = S(101, 4);

inline const std::array passed_pawn = {
  S(-28, -108), S(-42, -93), S(-50, -6), S(-11, 77), S(52, 145), S(145, 283),
};
inline const std::array defended_passed_pawn = {
  S(7, -5), S(15, 26), S(30, 35), S(15, 74), S(48, 105), S(71, 192),
};
inline const std::array blocked_passed_pawn = {
  S(-3, -15), S(11, -3), S(-11, -12), S(-18, -28), S(-19, -58), S(-43, -155),
};
inline const std::array friendly_passer_tropism = {
  S(5, 70), S(5, 63), S(11, 41), S(2, 28), S(13, 33), S(19, 35), S(6, 26),
};
inline const std::array enemy_passer_tropism = {
  S(-54, -55), S(10, 33), S(22, 50), S(30, 58), S(27, 68), S(21, 69), S(6, 72),
};

inline const pair isolated_pawn = S(-7, -5);
inline const std::array defended_pawn = {
  S(21, 15), S(26, 18), S(27, 35), S(91, 82), S(69, 115),
};
inline const std::array phalanx = {
  S(6, -8), S(19, 8), S(30, 38), S(80, 89), S(52, 92), S(9, 30),
};

inline const std::array shelter_centre = {
  S(-37, -13), S(24, -15), S(-2, -8), S(2, -13), S(-10, -3), S(7, 3), S(15, 51),
};
inline const std::array shelter_mid = {
  S(-58, -19), S(40, -22), S(17, -16), S(18, -20), S(-3, -6), S(-20, 14), S(4, 69),
};
inline const std::array shelter_edge = {
  S(-37, -15), S(25, -37), S(23, -18), S(11, -19), S(-9, -4), S(-16, 24), S(3, 71),
};

inline const std::array king_ring = {
  S(-40, 15), S(-35, 13), S(-26, 1), S(-32, 7), S(-9, -84),
};

inline const std::array pawn_psqt = {
  S( -57,   -4), S( -17,   -5), S( -41,  -16), S( -47,  -19), S( -46,    2), S(   7,  -26), S(  52,  -57), S( -44,  -59),
  S( -60,  -24), S( -41,  -22), S( -24,  -48), S( -40,  -39), S( -36,  -36), S( -63,  -38), S(  20,  -83), S( -42,  -71),
  S( -63,  -12), S( -50,  -22), S( -19,  -44), S(  -9,  -67), S( -18,  -65), S( -24,  -52), S( -19,  -51), S( -55,  -60),
  S( -50,   11), S(   7,   -7), S( -12,  -27), S(  13,  -58), S(  17,  -62), S(   7,  -60), S(  21,  -37), S( -29,  -44),
  S( -17,   77), S(  20,   68), S(  53,   31), S(  78,    1), S(  64,   -3), S(  56,   -9), S(  30,   46), S(  -3,   29),
  S( 105,  171), S( 110,  166), S(  95,  140), S(  96,  123), S(  77,   91), S(  15,   65), S(  -9,  110), S(  -4,  110),
};
inline const std::array knight_psqt = {
  S( -41,  -26), S( -54,  -44), S( -40,  -24), S( -29,  -21), S( -34,  -16), S(  -2,  -29), S( -38,  -30), S( -29,  -37),
  S( -49,  -30), S( -40,  -24), S( -35,  -10), S( -10,    9), S(   9,    4), S(   7,  -21), S( -15,  -18), S( -16,  -28),
  S( -65,  -18), S( -23,    6), S(  -5,   13), S(  16,   38), S(  27,   23), S(  32,    6), S(  38,  -10), S( -27,  -22),
  S( -34,   -2), S(  -1,   11), S(  19,   38), S(  35,   43), S(  49,   46), S(  52,   17), S(  40,   12), S(  10,  -17),
  S(  -3,   12), S(  15,   19), S(  27,   46), S(  79,   54), S(  39,   58), S( 112,   27), S(  29,   29), S(  55,   -3),
  S( -24,  -17), S(  -2,   14), S(  43,   36), S(  69,   34), S(  71,   27), S(  66,   46), S(  26,   14), S(   5,   -2),
  S( -66,  -23), S( -40,   -4), S(   5,   -2), S(  32,   21), S(  18,    5), S(  29,    5), S( -33,  -20), S(  -6,  -28),
  S(-144,  -68), S( -23,  -20), S( -39,  -14), S(  -4,    2), S(   2,  -10), S( -50,  -25), S(  -7,   -9), S( -24,  -39),
};
inline const std::array bishop_psqt = {
  S( -14,  -38), S( -14,  -32), S( -11,  -19), S( -18,  -13), S( -18,  -30), S( -31,    0), S( -13,  -24), S(  -6,  -10),
  S(   7,  -23), S(   2,  -12), S(   8,   -9), S( -17,    9), S(   8,   -4), S(  17,  -19), S(  54,  -25), S(  -6,  -20),
  S( -20,  -12), S(  19,   12), S(  17,   24), S(   3,   12), S(   2,   45), S(  25,    8), S(  20,   -8), S(   7,   -7),
  S( -16,  -12), S( -20,   24), S(  15,   24), S(  25,   52), S(  36,   19), S(  15,   19), S(   5,    0), S(  -8,  -22),
  S( -19,    1), S( -13,   20), S(  -1,   29), S(  58,   32), S(  23,   37), S(  16,   12), S(   2,    9), S(  -5,  -16),
  S( -19,  -14), S(   0,   20), S(   1,   18), S(  31,    6), S(  54,   19), S(  53,   38), S(  43,   21), S(  11,  -14),
  S( -35,   -6), S( -24,    4), S(  -6,    0), S( -18,   -8), S( -22,    0), S(   4,    1), S( -17,   -5), S( -35,  -28),
  S( -13,   -9), S( -15,   -3), S( -30,  -17), S( -16,  -12), S( -18,   -2), S( -53,  -13), S( -11,  -16), S(   0,   -7),
};
inline const std::array rook_psqt = {
  S( -23,  -13), S( -16,  -19), S(  -2,  -11), S(  14,  -19), S(  33,  -44), S(  22,  -34), S( -19,   -6), S(  -4,  -59),
  S( -68,   -7), S( -42,  -15), S( -32,    0), S( -20,  -16), S( -18,  -26), S(  11,  -42), S(   3,  -41), S( -81,  -38),
  S( -52,    8), S( -41,    1), S( -34,   13), S( -29,   -8), S( -20,  -17), S(  -5,  -24), S(  19,  -30), S( -11,  -32),
  S( -41,   11), S( -44,   10), S( -27,    8), S(  -4,   -6), S( -16,  -17), S( -11,  -16), S( -11,  -14), S( -22,  -32),
  S( -35,   31), S( -27,   18), S(  -4,   16), S(   7,   10), S(   7,  -18), S(  26,   -5), S(   8,  -15), S(   3,   -6),
  S( -18,   35), S(  11,   22), S(   6,   22), S(  25,    6), S(  49,   -3), S(  55,    6), S(  28,   16), S(   8,   -2),
  S( -10,   44), S(  -7,   47), S(  31,   38), S(  54,   27), S(  45,   20), S(  73,   15), S(  33,   35), S(  62,   18),
  S(   9,   15), S(  13,   18), S(  15,   23), S(  28,   23), S(  31,   10), S(  12,   24), S(  20,   24), S(  34,   18),
};
inline const std::array queen_psqt = {
  S( -33,  -29), S( -26,  -34), S( -10,  -37), S(  11,  -40), S( -20,  -43), S( -65,  -63), S( -42,  -42), S( -42,  -36),
  S( -40,  -30), S( -26,  -11), S(  -8,  -13), S(  -3,  -13), S(   9,  -14), S(   4,  -35), S(  -2,  -41), S( -32,  -31),
  S( -37,  -26), S( -18,   -5), S( -13,   12), S( -12,    9), S(  -4,   43), S(  10,    8), S(  22,    1), S( -11,  -16),
  S( -27,    2), S( -36,    0), S( -10,   19), S(  -6,   56), S(   9,   35), S(   0,   30), S(  19,   11), S(  -7,    0),
  S( -24,    0), S( -21,   40), S(  -4,   25), S(   0,   62), S(  26,   56), S(  30,   25), S(  21,   43), S(  20,  -20),
  S( -18,   -9), S(  -5,   15), S(  12,   25), S(  11,   34), S(  44,   29), S(  65,   30), S(  65,   22), S(  29,  -10),
  S( -24,  -20), S( -28,   17), S(   2,   27), S(   5,   30), S(   9,   17), S(  57,   16), S(  49,   16), S(  80,    0),
  S( -23,  -47), S(  -5,  -20), S(   6,  -16), S(   0,  -16), S(   8,  -11), S(  22,    4), S(  14,  -14), S(  28,  -14),
};
inline const std::array king_psqt = {
  S( -30,  -46), S(  18,  -62), S(  42,  -41), S( -55,  -54), S(  40,  -88), S(  -5,  -58), S( 120,  -89), S(  81, -114),
  S(  -4,  -40), S(   3,  -31), S(   2,   -7), S( -33,    4), S( -20,    6), S(  37,   -5), S(  89,  -37), S(  83,  -64),
  S( -23,  -50), S(   1,  -15), S( -23,    0), S( -33,   20), S( -45,   27), S( -19,   13), S(  14,  -14), S( -44,  -28),
  S( -19,  -22), S( -18,   -9), S( -27,   19), S( -21,   21), S( -18,   29), S( -36,   27), S( -36,    0), S( -55,  -31),
  S( -12,   -6), S(   0,   30), S(   1,   37), S(  -1,   37), S(  -3,   49), S(   0,   63), S(  -5,   43), S( -26,  -12),
  S(   0,    9), S(   0,   28), S(   7,   53), S(   7,   45), S(  10,   57), S(  11,   79), S(  10,   59), S(   0,   21),
  S(  -1,   -9), S(   3,   13), S(   7,   31), S(   5,   22), S(   7,   24), S(   9,   40), S(   3,   30), S(   0,    0),
  S(  -1,   -9), S(   1,   -3), S(   1,    3), S(   0,    0), S(   0,    0), S(   2,    5), S(   0,    2), S(   0,   -4),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
