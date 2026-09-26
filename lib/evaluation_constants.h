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
inline const pair pawn_material = S(136, 251);
inline const pair knight_material = S(571, 650);
inline const pair bishop_material = S(593, 733);
inline const pair rook_material = S(793, 1210);
inline const pair queen_material = S(1677, 2043);

inline const pair bishop_pair = S(124, 149);

inline const std::array knight_mobility = {
  S(-48, -74), S(-13, -38), S(-3, -18), S(2, 3), S(8, 19), S(12, 23), S(10, 30), S(14, 30), S(18, 23),
};
inline const std::array bishop_mobility = {
  S(-64, -89), S(-38, -49), S(-19, -21), S(-7, -11), S(1, 3), S(9, 16), S(14, 24), S(15, 22), S(20, 25), S(19, 32), S(33, 14), S(26, 18), S(-8, -6), S(-2, 19),
};
inline const std::array rook_mobility = {
  S(-86, -75), S(-62, -46), S(-48, -23), S(-34, -11), S(-32, -1), S(-19, 3), S(-12, 6), S(4, 10), S(16, 14), S(28, 17), S(40, 23), S(39, 26), S(52, 27), S(64, 6), S(48, 20),
};
inline const std::array queen_mobility = {
  S(-33, -68), S(-35, -70), S(-30, -86), S(-17, -85), S(-14, -73), S(-8, -61), S(-9, -50), S(-1, -31), S(1, -7), S(0, 8), S(6, 21), S(8, 41), S(15, 46), S(10, 56), S(14, 59), S(9, 75), S(19, 69), S(25, 67), S(32, 64), S(41, 56), S(44, 49), S(40, 54), S(23, 25), S(8, 16), S(-19, -23), S(-31, -34), S(-50, -60), S(-51, -61),
};

inline const pair pawn_threat_knight = S(76, 42);
inline const pair pawn_threat_bishop = S(100, 51);
inline const pair pawn_threat_rook = S(60, 47);
inline const pair pawn_threat_queen = S(49, 8);

inline const pair knight_threat_pawn = S(-14, 13);
inline const pair knight_threat_bishop = S(60, 48);
inline const pair knight_threat_rook = S(109, 8);
inline const pair knight_threat_queen = S(47, -11);

inline const std::array passed_pawn = {
  S(2, 6), S(-1, 12), S(-6, 89), S(25, 157), S(81, 216), S(165, 360),
};
inline const std::array defended_passed_pawn = {
  S(8, 2), S(12, 36), S(22, 47), S(8, 89), S(47, 121), S(67, 206),
};
inline const std::array blocked_passed_pawn = {
  S(-1, -12), S(10, -4), S(-3, -24), S(-11, -51), S(-15, -80), S(-43, -171),
};

inline const pair isolated_pawn = S(-7, -11);
inline const std::array defended_pawn = {
  S(20, 20), S(26, 19), S(30, 31), S(92, 75), S(69, 113),
};
inline const std::array phalanx = {
  S(11, -11), S(20, 10), S(29, 36), S(76, 89), S(51, 97), S(9, 32),
};

inline const std::array shelter_centre = {
  S(-20, -7), S(23, -3), S(9, 4), S(-8, 8), S(-6, -2), S(2, 4), S(0, -4), S(0, 0),
};
inline const std::array shelter_mid = {
  S(-38, -17), S(56, -18), S(2, -4), S(-31, 2), S(0, 11), S(5, 9), S(6, 17), S(0, 0),
};
inline const std::array shelter_edge = {
  S(-24, -9), S(45, -18), S(3, 3), S(-25, 6), S(-2, 9), S(2, 10), S(1, 0), S(0, 0),
};

inline const std::array pawn_psqt = {
  S( -56,  -11), S( -20,  -13), S( -44,  -19), S( -45,  -21), S( -41,    7), S(  11,  -22), S(  55,  -56), S( -51,  -58),
  S( -55,  -34), S( -39,  -27), S( -29,  -54), S( -38,  -39), S( -36,  -36), S( -64,  -40), S(  18,  -81), S( -42,  -71),
  S( -67,  -12), S( -52,  -24), S( -22,  -49), S(  -8,  -66), S( -19,  -72), S( -31,  -60), S( -24,  -54), S( -63,  -60),
  S( -53,   11), S(   6,   -5), S( -12,  -29), S(   7,  -62), S(  13,  -65), S(  -6,  -60), S(   8,  -39), S( -45,  -42),
  S( -20,   82), S(  17,   73), S(  57,   30), S(  83,   -4), S(  83,  -17), S(  69,  -10), S(  45,   44), S(   4,   35),
  S( 109,  184), S( 111,  178), S(  99,  149), S(  96,  121), S(  78,   86), S(  19,   73), S(   2,  122), S(  -5,  128),
};
inline const std::array knight_psqt = {
  S( -42,  -27), S( -58,  -41), S( -43,  -25), S( -32,  -21), S( -35,  -16), S(  -6,  -28), S( -40,  -26), S( -31,  -37),
  S( -51,  -33), S( -42,  -27), S( -38,   -9), S( -14,   12), S(   7,    5), S(   0,  -19), S( -18,  -19), S( -16,  -28),
  S( -74,  -17), S( -27,    5), S( -15,   13), S(  11,   38), S(  22,   24), S(  28,   12), S(  38,   -7), S( -40,  -22),
  S( -39,   -1), S(  -8,   11), S(  13,   38), S(  23,   41), S(  42,   47), S(  47,   21), S(  38,   12), S(   8,  -16),
  S(  -8,   15), S(  11,   22), S(  21,   47), S(  77,   52), S(  56,   49), S( 128,   23), S(  61,   16), S(  71,   -3),
  S( -27,  -13), S(  -4,   18), S(  35,   37), S(  77,   29), S(  91,   25), S(  81,   43), S(  55,   11), S(  17,    0),
  S( -70,  -18), S( -44,   -3), S(   2,   -2), S(  34,   19), S(  23,    3), S(  35,    1), S( -33,  -21), S(   0,  -27),
  S(-145,  -67), S( -25,  -19), S( -42,  -15), S(  -6,    2), S(   2,  -11), S( -52,  -26), S(  -8,   -9), S( -21,  -38),
};
inline const std::array bishop_psqt = {
  S( -19,  -40), S( -16,  -35), S( -23,  -23), S( -25,  -20), S( -25,  -34), S( -43,   -2), S( -14,  -27), S( -12,  -12),
  S(   4,  -25), S(  -2,  -10), S(   5,   -9), S( -30,    7), S(  -1,   -7), S(   9,  -21), S(  43,  -21), S( -11,  -22),
  S( -14,  -12), S(  15,   11), S(  10,   24), S(  -2,   17), S(  -7,   47), S(  19,   11), S(  14,  -10), S(   4,   -6),
  S( -18,  -14), S( -14,   22), S(  11,   29), S(  29,   53), S(  42,   25), S(   0,   24), S(   3,   -1), S(  -3,  -21),
  S( -23,    1), S(  -8,   15), S(   6,   28), S(  74,   34), S(  41,   43), S(  26,   15), S(  15,    7), S(   1,  -12),
  S( -27,  -15), S(  -2,   19), S(  10,   16), S(  47,    4), S(  67,   21), S(  74,   43), S(  59,   22), S(  38,  -12),
  S( -42,   -9), S( -24,    3), S(  -8,   -2), S( -23,   -9), S( -11,    0), S(   6,    3), S(  -3,   -4), S( -34,  -25),
  S( -21,  -11), S( -21,   -6), S( -36,  -16), S( -20,  -11), S( -17,    0), S( -55,  -12), S( -11,  -15), S(  -4,   -8),
};
inline const std::array rook_psqt = {
  S( -32,  -31), S( -26,  -30), S(  -9,  -21), S(   6,  -33), S(  24,  -54), S(  14,  -46), S( -25,  -19), S( -13,  -75),
  S( -76,  -21), S( -51,  -24), S( -41,  -12), S( -26,  -30), S( -26,  -39), S(   4,  -48), S(   5,  -48), S( -90,  -50),
  S( -66,    0), S( -52,   -4), S( -43,    4), S( -33,  -18), S( -25,  -25), S(  -6,  -29), S(  23,  -33), S( -16,  -41),
  S( -56,   13), S( -54,   11), S( -31,    9), S( -12,   -8), S( -23,  -16), S(  -5,  -14), S(  -5,  -12), S( -25,  -32),
  S( -50,   39), S( -40,   30), S( -10,   27), S(   3,   20), S(   3,   -5), S(  33,    5), S(  18,   -6), S(   4,    3),
  S( -27,   48), S(   6,   36), S(   2,   37), S(  29,   22), S(  56,   10), S(  70,   19), S(  44,   25), S(  20,    6),
  S(  -3,   56), S(   1,   58), S(  46,   47), S(  68,   42), S(  60,   33), S(  92,   20), S(  45,   38), S(  75,   22),
  S(  20,   11), S(  23,   18), S(  26,   22), S(  39,   21), S(  42,   10), S(  16,   23), S(  30,   25), S(  51,   14),
};
inline const std::array queen_psqt = {
  S( -42,  -40), S( -37,  -49), S( -23,  -64), S(   6,  -90), S( -35,  -70), S( -77,  -76), S( -47,  -47), S( -50,  -44),
  S( -53,  -45), S( -36,  -27), S( -14,  -45), S( -15,  -55), S(   1,  -63), S(  -5,  -51), S( -12,  -52), S( -39,  -35),
  S( -42,  -41), S( -25,  -32), S( -26,   -8), S( -21,  -17), S( -13,    8), S(   7,   -4), S(  14,   -1), S( -14,  -21),
  S( -36,  -30), S( -41,  -17), S( -20,    0), S( -18,   50), S(  -1,   25), S(  -8,   41), S(  12,   20), S( -10,   15),
  S( -38,  -26), S( -36,    9), S(  -7,   12), S(  -2,   59), S(  21,   79), S(  36,   58), S(  16,   74), S(  28,   29),
  S( -35,  -26), S( -21,   -4), S(  -5,    9), S(  13,   41), S(  57,   59), S( 111,   84), S(  97,   67), S(  68,   44),
  S( -30,  -21), S( -36,   18), S(   4,   30), S(   7,   40), S(  36,   50), S(  84,   55), S(  66,   34), S(  93,   22),
  S( -25,  -33), S(   1,   -5), S(  21,    3), S(  23,   19), S(  45,   33), S(  54,   38), S(  36,    8), S(  42,   12),
};
inline const std::array king_psqt = {
  S( -15,  -49), S(  51,  -77), S(  77,  -59), S( -38,  -73), S(  67, -110), S(  24,  -85), S( 168, -116), S( 131, -138),
  S(   6,  -46), S(   4,  -42), S(  -2,  -17), S( -47,   -4), S( -43,   -1), S(  29,  -20), S(  84,  -49), S( 112,  -82),
  S( -23,  -53), S(  -9,  -18), S( -47,    3), S( -69,   26), S( -84,   33), S( -66,   19), S( -17,  -12), S( -39,  -37),
  S( -19,  -22), S( -23,   -3), S( -38,   32), S( -29,   37), S( -33,   43), S( -57,   41), S( -53,    9), S( -54,  -28),
  S( -10,   -5), S(  -2,   40), S(   0,   49), S(   0,   50), S(  -4,   65), S(  -3,   77), S(  -7,   56), S( -24,   -9),
  S(   0,   12), S(   2,   36), S(   9,   61), S(  10,   55), S(  11,   64), S(  13,   92), S(  12,   68), S(   1,   25),
  S(   0,   -9), S(   4,   15), S(   8,   33), S(   6,   23), S(   7,   27), S(   9,   41), S(   3,   32), S(   0,   -2),
  S(   0,   -8), S(   2,   -2), S(   2,    5), S(   0,    0), S(   0,    0), S(   2,    5), S(   0,    3), S(   0,   -4),
};

}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
