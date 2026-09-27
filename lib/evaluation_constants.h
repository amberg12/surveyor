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
inline const pair pawn_material = S(132, 251);
inline const pair knight_material = S(577, 650);
inline const pair bishop_material = S(592, 730);
inline const pair rook_material = S(799, 1211);
inline const pair queen_material = S(1681, 2044);

inline const pair bishop_pair = S(119, 142);

inline const std::array knight_mobility = {
  S(-48, -74), S(-12, -37), S(-4, -21), S(5, 1), S(5, 19), S(9, 28), S(10, 30), S(16, 29), S(18, 23),
};
inline const std::array bishop_mobility = {
  S(-69, -91), S(-38, -50), S(-17, -21), S(-7, -12), S(1, 0), S(3, 13), S(10, 22), S(14, 21), S(22, 27), S(19, 33), S(33, 16), S(29, 19), S(-5, -3), S(2, 25),
};
inline const std::array rook_mobility = {
  S(-84, -75), S(-61, -44), S(-47, -26), S(-36, -10), S(-35, -1), S(-20, 2), S(-10, 4), S(2, 11), S(15, 14), S(29, 17), S(38, 23), S(40, 23), S(52, 28), S(66, 8), S(49, 22),
};
inline const std::array queen_mobility = {
  S(-33, -68), S(-35, -69), S(-31, -86), S(-19, -84), S(-13, -72), S(-8, -62), S(-6, -49), S(-2, -31), S(6, -7), S(1, 8), S(6, 21), S(7, 41), S(11, 44), S(11, 57), S(16, 60), S(9, 75), S(21, 69), S(23, 65), S(32, 64), S(41, 55), S(44, 49), S(39, 54), S(23, 25), S(8, 16), S(-19, -23), S(-31, -33), S(-50, -60), S(-51, -61),
};

inline const pair pawn_threat_knight = S(80, 42);
inline const pair pawn_threat_bishop = S(92, 54);
inline const pair pawn_threat_rook = S(62, 48);
inline const pair pawn_threat_queen = S(51, 8);

inline const pair knight_threat_pawn = S(-14, 15);
inline const pair knight_threat_bishop = S(56, 45);
inline const pair knight_threat_rook = S(109, 8);
inline const pair knight_threat_queen = S(46, -12);

inline const pair bishop_threat_pawn = S(-6, 8);
inline const pair bishop_threat_knight = S(33, 26);
inline const pair bishop_threat_rook = S(82, 38);
inline const pair bishop_threat_queen = S(79, 25);

inline const std::array passed_pawn = {
  S(4, 7), S(-3, 10), S(-6, 86), S(27, 158), S(82, 219), S(166, 359),
};
inline const std::array defended_passed_pawn = {
  S(8, 2), S(13, 37), S(20, 45), S(7, 88), S(46, 121), S(67, 206),
};
inline const std::array blocked_passed_pawn = {
  S(-3, -13), S(9, -6), S(-4, -24), S(-9, -48), S(-16, -79), S(-44, -171),
};

inline const pair isolated_pawn = S(-4, -7);
inline const std::array defended_pawn = {
  S(17, 22), S(24, 14), S(26, 30), S(90, 73), S(68, 112),
};
inline const std::array phalanx = {
  S(10, -11), S(17, 8), S(30, 38), S(76, 89), S(51, 97), S(9, 32),
};

inline const std::array shelter_centre = {
  S(-18, -4), S(21, -6), S(9, 5), S(-9, 7), S(-5, -2), S(2, 4), S(0, -4), S(0, 0),
};
inline const std::array shelter_mid = {
  S(-37, -18), S(55, -18), S(2, -3), S(-31, 3), S(0, 11), S(5, 8), S(6, 16), S(0, 0),
};
inline const std::array shelter_edge = {
  S(-23, -12), S(44, -18), S(2, 4), S(-24, 7), S(-2, 9), S(2, 10), S(1, -1), S(0, 0),
};

inline const std::array pawn_psqt = {
  S( -56,  -13), S( -22,  -11), S( -43,  -18), S( -42,  -20), S( -39,    6), S(  12,  -23), S(  54,  -57), S( -48,  -60),
  S( -56,  -32), S( -40,  -30), S( -28,  -55), S( -44,  -38), S( -37,  -36), S( -63,  -40), S(  17,  -80), S( -41,  -72),
  S( -67,  -13), S( -51,  -26), S( -22,  -49), S(  -7,  -68), S( -19,  -70), S( -32,  -58), S( -27,  -56), S( -62,  -60),
  S( -51,   11), S(   3,   -7), S( -16,  -29), S(   8,  -61), S(  11,  -65), S(  -8,  -61), S(  10,  -37), S( -45,  -41),
  S( -18,   85), S(  18,   75), S(  59,   31), S(  82,   -4), S(  83,  -16), S(  69,  -11), S(  44,   44), S(   4,   34),
  S( 110,  184), S( 111,  177), S(  99,  149), S(  97,  122), S(  78,   85), S(  19,   72), S(   3,  122), S(  -4,  128),
};
inline const std::array knight_psqt = {
  S( -43,  -27), S( -58,  -41), S( -44,  -26), S( -34,  -23), S( -37,  -17), S(  -7,  -28), S( -41,  -28), S( -32,  -38),
  S( -53,  -33), S( -43,  -27), S( -39,   -9), S( -17,   12), S(   6,    5), S(   2,  -18), S( -18,  -18), S( -18,  -29),
  S( -73,  -18), S( -29,    4), S( -15,   17), S(  10,   39), S(  22,   25), S(  31,   12), S(  39,   -7), S( -36,  -22),
  S( -40,   -1), S(  -7,   11), S(  14,   39), S(  28,   43), S(  45,   49), S(  48,   20), S(  40,   13), S(   6,  -15),
  S( -10,   14), S(  12,   23), S(  24,   48), S(  81,   53), S(  61,   47), S( 128,   22), S(  62,   15), S(  68,   -3),
  S( -28,  -13), S(  -6,   18), S(  38,   38), S(  78,   30), S(  92,   26), S(  84,   44), S(  54,   10), S(  16,    0),
  S( -73,  -20), S( -44,   -3), S(   0,   -1), S(  34,   18), S(  23,    3), S(  34,    1), S( -33,  -21), S(  -1,  -27),
  S(-147,  -68), S( -25,  -19), S( -43,  -16), S(  -6,    2), S(   1,  -11), S( -51,  -26), S(  -8,   -9), S( -22,  -39),
};
inline const std::array bishop_psqt = {
  S( -15,  -37), S( -12,  -34), S( -12,  -20), S( -19,  -17), S( -20,  -32), S( -39,    0), S( -12,  -25), S(  -6,   -9),
  S(   8,  -25), S(   0,  -10), S(   9,  -10), S( -25,    8), S(   9,   -6), S(  15,  -21), S(  56,  -19), S(  -6,  -21),
  S( -11,  -11), S(  20,    9), S(   9,   19), S(   4,   11), S(   0,   45), S(  22,    6), S(  18,  -10), S(   7,   -6),
  S( -19,  -13), S( -16,   22), S(  17,   23), S(  25,   51), S(  38,   19), S(   5,   20), S(   2,   -1), S(  -6,  -19),
  S( -23,    3), S( -15,   16), S(   3,   27), S(  66,   29), S(  31,   40), S(  22,   14), S(   3,   10), S(   3,  -11),
  S( -26,  -13), S(  -3,   21), S(  -3,   17), S(  39,    3), S(  61,   19), S(  68,   42), S(  58,   22), S(  36,   -9),
  S( -41,   -6), S( -40,    4), S( -13,   -2), S( -28,  -10), S( -24,    0), S(   5,    2), S( -13,   -5), S( -32,  -24),
  S( -17,   -9), S( -20,   -4), S( -35,  -16), S( -20,  -11), S( -16,    0), S( -53,  -11), S( -10,  -14), S(  -3,   -7),
};
inline const std::array rook_psqt = {
  S( -36,  -31), S( -27,  -31), S( -10,  -20), S(   5,  -33), S(  23,  -55), S(  14,  -47), S( -25,  -17), S( -17,  -75),
  S( -78,  -21), S( -53,  -25), S( -42,  -12), S( -28,  -32), S( -27,  -39), S(   4,  -48), S(   4,  -48), S( -92,  -50),
  S( -64,    0), S( -52,   -5), S( -40,    5), S( -33,  -19), S( -24,  -25), S(  -4,  -28), S(  23,  -32), S( -16,  -41),
  S( -57,   11), S( -53,   12), S( -30,    9), S( -10,   -9), S( -20,  -16), S(  -4,  -13), S(  -4,  -11), S( -28,  -33),
  S( -50,   38), S( -39,   30), S(  -9,   27), S(   5,   18), S(   6,   -6), S(  34,    6), S(  18,   -5), S(   3,    2),
  S( -27,   48), S(   7,   37), S(   3,   37), S(  30,   23), S(  57,    9), S(  71,   19), S(  43,   25), S(  21,    5),
  S(  -7,   52), S(   2,   59), S(  46,   47), S(  68,   43), S(  61,   33), S(  92,   21), S(  45,   38), S(  74,   22),
  S(  21,   13), S(  23,   18), S(  25,   22), S(  39,   21), S(  42,    9), S(  16,   23), S(  30,   24), S(  51,   14),
};
inline const std::array queen_psqt = {
  S( -43,  -40), S( -38,  -49), S( -24,  -64), S(   5,  -88), S( -34,  -70), S( -77,  -77), S( -47,  -48), S( -50,  -44),
  S( -53,  -45), S( -36,  -27), S( -16,  -44), S( -12,  -55), S(   0,  -63), S(  -5,  -51), S( -11,  -51), S( -39,  -36),
  S( -42,  -40), S( -24,  -31), S( -27,   -9), S( -20,  -16), S( -17,    6), S(   3,   -6), S(  13,   -2), S( -15,  -21),
  S( -37,  -30), S( -43,  -18), S( -19,   -1), S( -16,   50), S(   0,   25), S(  -8,   40), S(  11,   19), S(  -9,   15),
  S( -39,  -27), S( -37,    9), S(  -7,   11), S(   0,   58), S(  26,   80), S(  39,   58), S(  19,   74), S(  29,   29),
  S( -36,  -26), S( -21,   -3), S(  -5,    8), S(  13,   41), S(  57,   59), S( 112,   84), S(  97,   67), S(  68,   43),
  S( -30,  -20), S( -36,   18), S(   3,   29), S(   7,   40), S(  36,   49), S(  84,   54), S(  66,   34), S(  92,   23),
  S( -24,  -33), S(   1,   -6), S(  22,    3), S(  22,   18), S(  45,   33), S(  54,   38), S(  36,    8), S(  42,   13),
};
inline const std::array king_psqt = {
  S( -15,  -49), S(  50,  -77), S(  78,  -57), S( -38,  -72), S(  67, -110), S(  22,  -85), S( 169, -115), S( 130, -139),
  S(   7,  -45), S(   3,  -41), S(  -2,  -17), S( -46,   -5), S( -42,    0), S(  28,  -24), S(  83,  -49), S( 112,  -84),
  S( -24,  -54), S(  -9,  -17), S( -46,    4), S( -69,   26), S( -84,   32), S( -64,   21), S( -18,  -14), S( -40,  -37),
  S( -19,  -22), S( -23,   -2), S( -37,   32), S( -29,   38), S( -33,   42), S( -57,   43), S( -53,    9), S( -54,  -28),
  S( -10,   -6), S(  -2,   40), S(   0,   49), S(  -1,   49), S(  -4,   66), S(  -2,   78), S(  -7,   56), S( -23,   -9),
  S(   0,   12), S(   2,   36), S(   9,   60), S(  10,   55), S(  11,   64), S(  13,   92), S(  12,   68), S(   1,   25),
  S(   0,   -9), S(   4,   14), S(   8,   34), S(   6,   23), S(   8,   28), S(   9,   41), S(   3,   32), S(   0,   -2),
  S(   0,   -8), S(   2,   -2), S(   2,    5), S(   0,    0), S(   1,    0), S(   2,    5), S(   0,    3), S(   0,   -4),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
