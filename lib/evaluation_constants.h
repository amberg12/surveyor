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
inline const pair pawn_material = S(142, 255);
inline const pair knight_material = S(570, 655);
inline const pair bishop_material = S(582, 730);
inline const pair rook_material = S(787, 1208);
inline const pair queen_material = S(1667, 2036);
inline const pair bishop_pair = S(123, 152);

inline const std::array knight_mobility = {
  S(-48, -74), S(-10, -31), S(-3, -15), S(2, 9), S(8, 21), S(11, 28), S(10, 29), S(13, 23), S(16, 9),
};
inline const std::array bishop_mobility = {
  S(-66, -93), S(-39, -49), S(-21, -22), S(-8, -12), S(2, 4), S(8, 17), S(13, 27), S(16, 24), S(19, 26), S(20, 34), S(34, 15), S(27, 14), S(-7, -5), S(0, 18),
};
inline const std::array rook_mobility = {
  S(-83, -75), S(-60, -45), S(-50, -25), S(-32, -10), S(-34, -3), S(-17, 4), S(-11, 6), S(5, 8), S(16, 16), S(29, 18), S(35, 20), S(38, 26), S(52, 29), S(63, 8), S(48, 21),
};
inline const std::array queen_mobility = {
  S(-24, -67), S(-32, -69), S(-32, -85), S(-20, -84), S(-15, -73), S(-10, -62), S(-5, -50), S(-2, -30), S(2, -6), S(1, 8), S(6, 22), S(10, 41), S(12, 45), S(7, 56), S(14, 60), S(8, 74), S(20, 69), S(24, 66), S(31, 63), S(40, 55), S(43, 48), S(39, 53), S(22, 25), S(8, 15), S(-19, -23), S(-31, -34), S(-50, -60), S(-51, -61),
};

inline const pair isolated_pawn = S(-9, -10);
inline const std::array passed_pawn = {
  S(4, 7), S(-1, 8), S(-11, 80), S(19, 145), S(69, 198), S(123, 316),
};
inline const std::array defended_passed_pawn = {
  S(9, 3), S(13, 39), S(26, 58), S(15, 108), S(50, 138), S(71, 223),
};
inline const std::array defended_pawn = {
  S(11, 21), S(19, 15), S(21, 26), S(89, 70), S(68, 112),
};

inline const std::array shelter_centre = {
  S(-24, -6), S(24, -5), S(9, 1), S(-7, 7), S(-5, -1), S(2, 5), S(1, 0), S(0, 0),
};
inline const std::array shelter_mid = {
  S(-39, -15), S(55, -20), S(1, -5), S(-29, 4), S(0, 12), S(4, 9), S(6, 15), S(0, 0),
};
inline const std::array shelter_edge = {
  S(-31, -13), S(48, -20), S(5, 3), S(-23, 5), S(-2, 9), S(2, 12), S(2, 2), S(0, 0),
};

inline const std::array pawn_psqt = {
  S( -59,  -15), S( -21,  -21), S( -44,  -22), S( -46,  -24), S( -45,    0), S(   9,  -31), S(  55,  -68), S( -52,  -66),
  S( -56,  -28), S( -35,  -29), S( -22,  -53), S( -37,  -39), S( -34,  -33), S( -58,  -41), S(  22,  -80), S( -42,  -66),
  S( -70,   -5), S( -47,  -16), S( -18,  -46), S(  -4,  -65), S( -11,  -66), S( -34,  -52), S( -20,  -47), S( -67,  -55),
  S( -54,   17), S(   4,   -3), S( -15,  -28), S(  15,  -59), S(  19,  -63), S(  -6,  -55), S(   8,  -31), S( -49,  -39),
  S( -21,   84), S(  15,   75), S(  60,   30), S(  82,   -6), S(  81,  -21), S(  68,  -12), S(  42,   45), S(   2,   34),
  S( 107,  178), S( 112,  175), S(  98,  145), S(  94,  116), S(  76,   83), S(  15,   70), S(   0,  118), S( -13,  125),
};
inline const std::array knight_psqt = {
  S( -43,  -22), S( -58,  -48), S( -46,  -29), S( -35,  -29), S( -36,  -21), S(  -9,  -36), S( -42,  -33), S( -34,  -37),
  S( -53,  -33), S( -46,  -28), S( -39,  -12), S( -14,   11), S(   5,    0), S(  -1,  -22), S( -23,  -23), S( -18,  -31),
  S( -76,  -23), S( -30,    3), S( -23,   22), S(   7,   44), S(  17,   30), S(  27,   14), S(  34,   -8), S( -43,  -29),
  S( -42,   -6), S( -15,   12), S(   4,   47), S(  15,   54), S(  39,   55), S(  33,   33), S(  33,   11), S(   2,  -21),
  S(  -9,    8), S(   0,   24), S(  21,   57), S(  74,   59), S(  46,   66), S( 129,   28), S(  46,   22), S(  69,   -9),
  S( -27,  -18), S(  18,   17), S(  45,   44), S(  90,   39), S( 114,   31), S(  84,   53), S(  77,    4), S(  11,   -4),
  S( -65,  -24), S( -40,   -7), S(  26,   -3), S(  55,   17), S(  29,    6), S(  51,    0), S( -32,  -23), S(   5,  -30),
  S(-150,  -71), S( -25,  -21), S( -41,  -17), S(  -5,    1), S(   2,  -14), S( -51,  -27), S(  -8,  -10), S( -22,  -41),
};
inline const std::array bishop_psqt = {
  S( -16,  -33), S( -13,  -30), S( -14,  -23), S( -22,  -18), S( -23,  -32), S( -37,    0), S( -13,  -24), S( -10,   -5),
  S(   6,  -21), S(   1,   -9), S(   6,   -8), S( -30,   10), S(   2,   -8), S(   8,  -20), S(  50,  -20), S(  -9,  -20),
  S( -13,  -11), S(  17,   12), S(   8,   25), S(   0,   16), S(  -8,   46), S(  18,    9), S(  12,  -10), S(   4,   -6),
  S( -15,  -14), S( -15,   20), S(   8,   27), S(  30,   53), S(  36,   24), S(  -1,   21), S(  -3,   -3), S(  -3,  -21),
  S( -23,   -2), S( -10,   14), S(   3,   27), S(  68,   32), S(  35,   39), S(  19,   14), S(  11,    6), S(  -2,  -12),
  S( -29,  -15), S(  -3,   19), S(   8,   17), S(  45,    1), S(  65,   19), S(  66,   43), S(  57,   21), S(  32,  -10),
  S( -40,   -9), S( -21,    1), S(  -7,   -3), S( -22,  -10), S( -11,   -1), S(   8,    2), S(  -1,   -5), S( -33,  -25),
  S( -16,  -11), S( -20,   -6), S( -34,  -17), S( -19,  -11), S( -16,    0), S( -54,  -12), S( -11,  -16), S(  -2,   -7),
};
inline const std::array rook_psqt = {
  S( -28,  -28), S( -23,  -28), S( -10,  -19), S(   8,  -30), S(  27,  -52), S(  18,  -48), S( -25,  -18), S( -10,  -72),
  S( -73,  -18), S( -48,  -22), S( -41,  -12), S( -27,  -30), S( -26,  -39), S(   4,  -49), S(   6,  -48), S( -88,  -49),
  S( -65,    0), S( -52,   -2), S( -45,    5), S( -36,  -19), S( -27,  -25), S(  -7,  -28), S(  20,  -32), S( -17,  -40),
  S( -56,   12), S( -54,   11), S( -33,    8), S( -10,   -8), S( -25,  -17), S(  -7,  -13), S( -10,  -12), S( -25,  -33),
  S( -50,   36), S( -41,   29), S( -11,   25), S(   0,   17), S(   2,   -6), S(  29,    4), S(  14,   -7), S(   1,    0),
  S( -26,   48), S(   6,   37), S(   2,   36), S(  32,   23), S(  55,    9), S(  68,   21), S(  42,   25), S(  19,    5),
  S(  -4,   52), S(   1,   60), S(  48,   50), S(  66,   42), S(  61,   34), S(  94,   23), S(  44,   39), S(  76,   21),
  S(  25,    3), S(  24,   14), S(  26,   21), S(  40,   19), S(  44,   10), S(  16,   23), S(  31,   24), S(  53,   11),
};
inline const std::array queen_psqt = {
  S( -41,  -39), S( -36,  -49), S( -21,  -63), S(   6,  -90), S( -35,  -70), S( -76,  -76), S( -47,  -48), S( -50,  -43),
  S( -51,  -44), S( -34,  -27), S( -13,  -46), S( -13,  -54), S(   1,  -62), S(  -5,  -51), S( -11,  -52), S( -38,  -35),
  S( -42,  -40), S( -27,  -33), S( -28,   -9), S( -21,  -17), S( -17,    8), S(   2,   -5), S(  11,   -2), S( -13,  -22),
  S( -36,  -29), S( -41,  -16), S( -20,    0), S( -17,   51), S(  -1,   26), S(  -9,   41), S(   8,   22), S( -10,   15),
  S( -40,  -29), S( -39,    8), S(  -9,   11), S(  -4,   57), S(  21,   79), S(  37,   58), S(  16,   73), S(  26,   28),
  S( -35,  -27), S( -21,   -4), S(  -6,    8), S(  13,   40), S(  56,   58), S( 112,   85), S(  96,   67), S(  69,   43),
  S( -29,  -23), S( -34,   19), S(   5,   30), S(   7,   41), S(  37,   49), S(  86,   55), S(  68,   35), S(  95,   22),
  S( -24,  -34), S(   2,   -5), S(  22,    3), S(  23,   19), S(  46,   33), S(  54,   38), S(  38,    8), S(  44,   12),
};
inline const std::array king_psqt = {
  S( -15,  -47), S(  50,  -75), S(  78,  -56), S( -36,  -71), S(  72, -109), S(  23,  -82), S( 167, -118), S( 133, -135),
  S(   6,  -44), S(   5,  -39), S(  -2,  -15), S( -47,   -4), S( -43,    0), S(  31,  -21), S(  85,  -47), S( 112,  -79),
  S( -24,  -53), S( -11,  -16), S( -47,    5), S( -68,   27), S( -84,   32), S( -65,   21), S( -17,  -13), S( -40,  -35),
  S( -19,  -21), S( -23,   -2), S( -37,   34), S( -29,   38), S( -33,   42), S( -59,   42), S( -53,    8), S( -54,  -26),
  S( -10,   -7), S(  -2,   39), S(   0,   47), S(  -1,   48), S(  -4,   64), S(  -3,   76), S(  -7,   54), S( -24,  -11),
  S(   0,   11), S(   2,   35), S(   8,   59), S(  10,   55), S(  11,   63), S(  13,   92), S(  12,   68), S(   1,   23),
  S(  -1,  -10), S(   4,   14), S(   8,   34), S(   6,   24), S(   7,   27), S(   9,   41), S(   3,   32), S(  -1,   -3),
  S(  -1,  -12), S(   2,   -3), S(   1,    3), S(   0,   -1), S(   0,    0), S(   2,    4), S(   0,    2), S(   0,   -7),
};

}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
