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
inline const pair pawn_material = S(135, 251);
inline const pair knight_material = S(570, 656);
inline const pair bishop_material = S(589, 730);
inline const pair rook_material = S(788, 1211);
inline const pair queen_material = S(1674, 2041);

inline const pair bishop_pair = S(124, 150);

inline const std::array knight_mobility = {
  S(-48, -74), S(-13, -32), S(-3, -12), S(1, 5), S(6, 22), S(13, 30), S(13, 26), S(12, 24), S(19, 8),
};
inline const std::array bishop_mobility = {
  S(-65, -89), S(-39, -48), S(-17, -21), S(-6, -11), S(4, 2), S(6, 15), S(15, 26), S(14, 21), S(21, 27), S(17, 31), S(32, 14), S(27, 18), S(-8, -6), S(-2, 19),
};
inline const std::array rook_mobility = {
  S(-85, -77), S(-63, -44), S(-51, -25), S(-36, -11), S(-33, -2), S(-20, 1), S(-9, 8), S(3, 9), S(17, 17), S(31, 20), S(39, 21), S(39, 22), S(52, 28), S(64, 6), S(49, 24),
};
inline const std::array queen_mobility = {
  S(-33, -68), S(-35, -69), S(-31, -86), S(-18, -84), S(-13, -73), S(-7, -62), S(-5, -49), S(0, -30), S(0, -8), S(4, 8), S(5, 21), S(9, 41), S(12, 45), S(12, 57), S(14, 61), S(11, 76), S(17, 68), S(21, 66), S(31, 64), S(40, 56), S(43, 49), S(39, 54), S(22, 25), S(8, 16), S(-19, -23), S(-31, -34), S(-50, -60), S(-51, -61),
};

inline const pair pawn_threat_knight = S(75, 44);
inline const pair pawn_threat_bishop = S(100, 50);
inline const pair pawn_threat_rook = S(58, 48);
inline const pair pawn_threat_queen = S(48, 7);

inline const std::array passed_pawn = {
  S(5, 6), S(-3, 8), S(-9, 86), S(24, 158), S(83, 218), S(166, 360),
};
inline const std::array defended_passed_pawn = {
  S(7, 0), S(11, 36), S(24, 47), S(10, 89), S(47, 122), S(67, 206),
};
inline const std::array blocked_passed_pawn = {
  S(-6, -12), S(10, -5), S(-3, -24), S(-11, -52), S(-15, -80), S(-42, -170),
};

inline const pair isolated_pawn = S(-3, -7);
inline const std::array defended_pawn = {
  S(22, 22), S(27, 19), S(30, 31), S(91, 73), S(68, 112),
};
inline const std::array phalanx = {
  S(9, -9), S(18, 9), S(31, 37), S(75, 89), S(52, 97), S(9, 32),
};

inline const std::array shelter_centre = {
  S(-21, -3), S(24, -6), S(8, 3), S(-8, 10), S(-6, -2), S(2, 3), S(0, -4), S(0, 0),
};
inline const std::array shelter_mid = {
  S(-37, -18), S(55, -20), S(3, -3), S(-31, 5), S(0, 10), S(5, 8), S(6, 17), S(0, 0),
};
inline const std::array shelter_edge = {
  S(-25, -11), S(44, -22), S(4, 5), S(-24, 10), S(-2, 9), S(1, 10), S(1, -1), S(0, 0),
};

inline const std::array pawn_psqt = {
  S( -57,  -12), S( -21,  -11), S( -43,  -15), S( -47,  -20), S( -41,    5), S(   9,  -21), S(  52,  -58), S( -50,  -60),
  S( -58,  -34), S( -41,  -30), S( -27,  -51), S( -40,  -36), S( -33,  -34), S( -62,  -40), S(  14,  -82), S( -41,  -71),
  S( -66,  -13), S( -52,  -24), S( -20,  -51), S(  -9,  -70), S( -19,  -72), S( -33,  -56), S( -22,  -56), S( -62,  -59),
  S( -50,   15), S(   2,  -10), S( -15,  -31), S(  13,  -63), S(  14,  -68), S(  -8,  -61), S(  10,  -39), S( -47,  -41),
  S( -20,   81), S(  17,   74), S(  58,   30), S(  84,   -3), S(  82,  -17), S(  69,  -12), S(  46,   45), S(   5,   36),
  S( 110,  186), S( 111,  176), S(  99,  149), S(  97,  121), S(  78,   86), S(  19,   73), S(   3,  122), S(  -4,  129),
};
inline const std::array knight_psqt = {
  S( -44,  -30), S( -59,  -49), S( -46,  -31), S( -36,  -28), S( -37,  -21), S(  -8,  -35), S( -47,  -35), S( -33,  -40),
  S( -51,  -35), S( -46,  -30), S( -40,  -12), S( -17,    9), S(   5,    0), S(   0,  -21), S( -21,  -24), S( -17,  -32),
  S( -80,  -23), S( -31,    3), S( -24,   22), S(   8,   43), S(  17,   30), S(  22,   10), S(  36,   -7), S( -43,  -28),
  S( -41,   -5), S( -12,   13), S(   6,   46), S(  17,   53), S(  39,   53), S(  36,   35), S(  37,   12), S(   2,  -20),
  S(  -9,   11), S(   1,   25), S(  19,   58), S(  75,   60), S(  43,   65), S( 132,   29), S(  46,   24), S(  72,   -6),
  S( -26,  -16), S(  16,   17), S(  45,   45), S(  88,   39), S( 115,   30), S(  84,   52), S(  76,    6), S(  13,   -2),
  S( -65,  -24), S( -41,   -7), S(  23,   -3), S(  53,   18), S(  27,    6), S(  50,    0), S( -33,  -23), S(   4,  -30),
  S(-149,  -70), S( -25,  -21), S( -42,  -17), S(  -5,    2), S(   2,  -12), S( -52,  -27), S(  -8,  -10), S( -23,  -41),
};
inline const std::array bishop_psqt = {
  S( -17,  -39), S( -14,  -35), S( -17,  -22), S( -23,  -20), S( -23,  -34), S( -39,   -1), S( -14,  -27), S( -10,  -10),
  S(   6,  -25), S(   1,  -11), S(   4,  -10), S( -30,    8), S(  -1,   -5), S(  10,  -20), S(  44,  -23), S( -10,  -23),
  S( -12,  -12), S(  15,   11), S(   8,   23), S(  -3,   14), S( -11,   47), S(  20,   10), S(  13,  -10), S(   4,   -7),
  S( -18,  -15), S( -15,   20), S(  12,   28), S(  29,   54), S(  39,   24), S(   1,   22), S(  -1,    0), S(  -3,  -21),
  S( -22,    0), S(  -7,   14), S(   6,   30), S(  70,   33), S(  36,   43), S(  26,   15), S(  14,    7), S(   0,   -9),
  S( -26,  -14), S(  -2,   19), S(   9,   15), S(  44,    2), S(  67,   21), S(  72,   43), S(  58,   22), S(  38,  -11),
  S( -42,   -7), S( -22,    2), S(  -9,   -2), S( -23,   -8), S( -12,    0), S(   7,    3), S(  -2,   -4), S( -34,  -24),
  S( -19,  -11), S( -21,   -5), S( -36,  -17), S( -20,  -11), S( -17,    0), S( -55,  -12), S( -11,  -14), S(  -4,   -8),
};
inline const std::array rook_psqt = {
  S( -30,  -28), S( -25,  -31), S(  -9,  -22), S(   8,  -32), S(  23,  -54), S(  14,  -49), S( -22,  -18), S( -16,  -74),
  S( -75,  -21), S( -50,  -25), S( -40,  -12), S( -29,  -33), S( -26,  -39), S(   4,  -49), S(   6,  -49), S( -88,  -50),
  S( -64,    0), S( -50,   -4), S( -44,    4), S( -35,  -19), S( -26,  -25), S(  -5,  -28), S(  23,  -32), S( -14,  -41),
  S( -56,   12), S( -55,   12), S( -33,    9), S( -11,   -8), S( -25,  -16), S(  -6,  -13), S(  -7,  -11), S( -24,  -33),
  S( -49,   38), S( -40,   30), S( -10,   27), S(   1,   19), S(   1,   -6), S(  32,    5), S(  17,   -5), S(   4,    3),
  S( -28,   48), S(   6,   38), S(   2,   38), S(  31,   23), S(  55,   10), S(  70,   19), S(  43,   25), S(  19,    5),
  S(  -5,   53), S(   1,   58), S(  46,   46), S(  67,   42), S(  60,   33), S(  92,   21), S(  44,   38), S(  76,   24),
  S(  22,   13), S(  23,   18), S(  25,   21), S(  39,   21), S(  43,   10), S(  16,   23), S(  30,   24), S(  51,   15),
};
inline const std::array queen_psqt = {
  S( -41,  -40), S( -37,  -49), S( -22,  -65), S(   8,  -91), S( -35,  -69), S( -77,  -77), S( -47,  -48), S( -50,  -44),
  S( -52,  -45), S( -35,  -28), S( -15,  -47), S( -16,  -55), S(   3,  -64), S(  -4,  -51), S( -11,  -51), S( -38,  -35),
  S( -42,  -41), S( -25,  -33), S( -29,   -9), S( -18,  -17), S( -16,    6), S(   5,   -5), S(  12,   -1), S( -12,  -22),
  S( -38,  -30), S( -40,  -17), S( -19,   -1), S( -16,   51), S(  -1,   26), S(  -8,   41), S(   8,   20), S( -11,   14),
  S( -38,  -27), S( -36,   10), S(  -8,   12), S(  -4,   59), S(  22,   81), S(  38,   59), S(  16,   74), S(  29,   29),
  S( -36,  -26), S( -22,   -4), S(  -6,    9), S(  13,   41), S(  57,   59), S( 112,   85), S(  97,   67), S(  68,   44),
  S( -30,  -21), S( -36,   19), S(   4,   30), S(   6,   41), S(  37,   49), S(  84,   55), S(  66,   35), S(  94,   22),
  S( -24,  -33), S(   2,   -5), S(  21,    3), S(  23,   19), S(  45,   32), S(  53,   38), S(  37,    8), S(  42,   13),
};
inline const std::array king_psqt = {
  S( -15,  -48), S(  51,  -77), S(  74,  -59), S( -36,  -72), S(  68, -109), S(  24,  -83), S( 171, -115), S( 132, -139),
  S(   6,  -45), S(   4,  -42), S(  -1,  -16), S( -48,   -7), S( -44,    0), S(  30,  -24), S(  84,  -50), S( 111,  -84),
  S( -23,  -55), S(  -9,  -16), S( -47,    4), S( -69,   27), S( -84,   33), S( -66,   19), S( -17,  -14), S( -39,  -37),
  S( -19,  -22), S( -23,   -3), S( -38,   32), S( -29,   39), S( -33,   42), S( -58,   42), S( -52,    9), S( -54,  -28),
  S( -10,   -6), S(  -2,   40), S(   0,   49), S(   0,   50), S(  -4,   65), S(  -2,   78), S(  -7,   56), S( -24,   -9),
  S(   0,   12), S(   2,   36), S(   9,   60), S(  10,   55), S(  11,   64), S(  13,   92), S(  12,   68), S(   1,   24),
  S(   0,   -9), S(   4,   15), S(   8,   34), S(   6,   23), S(   8,   28), S(   9,   41), S(   3,   32), S(   0,   -2),
  S(   0,   -9), S(   2,   -2), S(   2,    5), S(   0,    0), S(   1,    0), S(   2,    5), S(   0,    3), S(   0,   -4),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
