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
inline const pair pawn_material = S(137, 253);
inline const pair knight_material = S(574, 653);
inline const pair bishop_material = S(591, 726);
inline const pair rook_material = S(790, 1208);
inline const pair queen_material = S(1675, 2038);

inline const pair bishop_pair = S(124, 151);

inline const std::array knight_mobility = {
  S(-49, -74), S(-13, -32), S(-2, -12), S(5, 9), S(10, 19), S(8, 29), S(9, 27), S(12, 24), S(18, 8),
};
inline const std::array bishop_mobility = {
  S(-64, -91), S(-37, -49), S(-20, -21), S(-4, -13), S(3, 2), S(7, 19), S(15, 28), S(15, 23), S(20, 27), S(18, 33), S(30, 14), S(26, 15), S(-8, -5), S(-2, 18),
};
inline const std::array rook_mobility = {
  S(-83, -76), S(-59, -46), S(-49, -25), S(-35, -9), S(-37, -1), S(-19, 2), S(-6, 7), S(5, 10), S(14, 15), S(26, 17), S(38, 22), S(41, 24), S(53, 29), S(63, 7), S(48, 23),
};
inline const std::array queen_mobility = {
  S(-23, -68), S(-33, -69), S(-33, -85), S(-22, -84), S(-14, -72), S(-6, -61), S(-1, -49), S(-4, -30), S(1, -8), S(0, 8), S(6, 21), S(9, 42), S(12, 45), S(11, 57), S(13, 60), S(8, 75), S(21, 71), S(23, 66), S(30, 64), S(40, 56), S(43, 48), S(39, 54), S(21, 25), S(7, 15), S(-20, -23), S(-31, -34), S(-50, -60), S(-51, -61),
};

inline const pair pawn_threat_knight = S(72, 46);
inline const pair pawn_threat_bishop = S(100, 51);
inline const pair pawn_threat_rook = S(61, 52);
inline const pair pawn_threat_queen = S(49, 9);

inline const pair isolated_pawn = S(-10, -8);
inline const std::array passed_pawn = {
  S(0, 3), S(0, 9), S(-9, 77), S(17, 148), S(69, 199), S(122, 316),
};
inline const std::array defended_passed_pawn = {
  S(6, 1), S(12, 36), S(28, 59), S(14, 107), S(51, 139), S(71, 224),
};
inline const std::array defended_pawn = {
  S(12, 22), S(20, 13), S(23, 26), S(91, 70), S(68, 112),
};

inline const std::array shelter_centre = {
  S(-25, -6), S(25, -4), S(9, 1), S(-7, 7), S(-5, -1), S(2, 5), S(1, 0), S(0, 0),
};
inline const std::array shelter_mid = {
  S(-38, -15), S(53, -20), S(2, -5), S(-29, 3), S(0, 12), S(4, 9), S(6, 15), S(0, 0),
};
inline const std::array shelter_edge = {
  S(-28, -11), S(45, -19), S(5, 1), S(-23, 5), S(-2, 9), S(1, 12), S(2, 2), S(0, 0),
};

inline const std::array pawn_psqt = {
  S( -57,  -16), S( -18,  -21), S( -35,  -24), S( -47,  -25), S( -40,    0), S(  11,  -28), S(  60,  -67), S( -49,  -65),
  S( -56,  -31), S( -34,  -28), S( -23,  -51), S( -34,  -38), S( -30,  -33), S( -57,  -39), S(  19,  -82), S( -44,  -66),
  S( -67,   -8), S( -44,  -18), S( -17,  -45), S(  -6,  -66), S( -14,  -66), S( -32,  -53), S( -21,  -49), S( -66,  -55),
  S( -54,   18), S(  -1,   -3), S( -15,  -27), S(  13,  -59), S(  13,  -61), S(  -6,  -55), S(   7,  -32), S( -49,  -39),
  S( -20,   85), S(  16,   75), S(  56,   30), S(  83,   -3), S(  80,  -19), S(  66,  -11), S(  42,   44), S(   0,   32),
  S( 107,  178), S( 109,  175), S(  97,  144), S(  91,  113), S(  72,   82), S(  14,   71), S(  -2,  118), S( -13,  124),
};
inline const std::array knight_psqt = {
  S( -44,  -22), S( -58,  -47), S( -45,  -29), S( -36,  -28), S( -38,  -21), S(  -9,  -37), S( -41,  -33), S( -35,  -37),
  S( -53,  -33), S( -46,  -28), S( -42,  -13), S( -19,   10), S(   4,    0), S(   0,  -22), S( -23,  -23), S( -19,  -30),
  S( -81,  -24), S( -31,    2), S( -27,   19), S(   8,   44), S(  17,   30), S(  22,   13), S(  32,   -9), S( -43,  -29),
  S( -43,   -5), S( -12,   13), S(   8,   47), S(  18,   53), S(  42,   55), S(  34,   35), S(  37,   12), S(   5,  -20),
  S( -10,    9), S(   2,   24), S(  21,   58), S(  76,   59), S(  46,   66), S( 133,   29), S(  47,   23), S(  74,   -7),
  S( -25,  -18), S(  16,   17), S(  45,   45), S(  89,   38), S( 115,   30), S(  85,   52), S(  78,    5), S(  13,   -3),
  S( -66,  -24), S( -41,   -7), S(  24,   -3), S(  53,   18), S(  27,    5), S(  51,    0), S( -33,  -23), S(   4,  -30),
  S(-151,  -71), S( -26,  -21), S( -41,  -17), S(  -6,    1), S(   2,  -13), S( -52,  -27), S(  -9,  -10), S( -23,  -41),
};
inline const std::array bishop_psqt = {
  S( -18,  -34), S( -15,  -31), S( -17,  -22), S( -24,  -18), S( -25,  -33), S( -43,   -1), S( -14,  -24), S( -11,   -5),
  S(   5,  -22), S(   1,   -9), S(   4,   -9), S( -35,    9), S(  -2,   -4), S(   6,  -20), S(  47,  -19), S( -11,  -20),
  S( -12,  -12), S(  15,   11), S(   8,   24), S(   0,   18), S(  -9,   47), S(  20,   11), S(  12,  -10), S(   4,   -6),
  S( -18,  -15), S( -14,   20), S(  12,   26), S(  32,   55), S(  39,   23), S(   0,   22), S(   0,   -2), S(  -4,  -21),
  S( -22,   -2), S(  -6,   13), S(   4,   26), S(  71,   33), S(  37,   41), S(  25,   14), S(  16,    6), S(   0,  -12),
  S( -26,  -17), S(  -3,   19), S(  10,   16), S(  46,    2), S(  67,   20), S(  73,   42), S(  59,   21), S(  40,  -12),
  S( -41,   -9), S( -22,    1), S(  -9,   -3), S( -23,  -10), S( -11,   -1), S(   8,    3), S(  -2,   -5), S( -34,  -25),
  S( -20,  -11), S( -21,   -6), S( -35,  -18), S( -20,  -12), S( -17,    0), S( -55,  -12), S( -12,  -16), S(  -4,   -8),
};
inline const std::array rook_psqt = {
  S( -30,  -30), S( -23,  -28), S( -10,  -21), S(   4,  -32), S(  24,  -50), S(  18,  -49), S( -25,  -18), S( -11,  -72),
  S( -74,  -18), S( -48,  -22), S( -40,  -11), S( -28,  -29), S( -25,  -38), S(   5,  -48), S(   6,  -48), S( -88,  -49),
  S( -65,    1), S( -53,   -2), S( -44,    6), S( -34,  -18), S( -27,  -26), S(  -6,  -27), S(  20,  -32), S( -16,  -41),
  S( -57,   10), S( -54,   11), S( -32,    9), S( -10,   -8), S( -24,  -16), S(  -7,  -13), S(  -8,  -11), S( -25,  -34),
  S( -51,   36), S( -38,   31), S( -12,   26), S(   0,   17), S(   2,   -6), S(  32,    4), S(  17,   -6), S(   2,    0),
  S( -26,   48), S(   7,   39), S(   1,   37), S(  30,   22), S(  55,    8), S(  69,   19), S(  44,   25), S(  19,    4),
  S(  -4,   51), S(   0,   59), S(  47,   49), S(  66,   43), S(  60,   35), S(  93,   22), S(  44,   40), S(  75,   22),
  S(  25,    4), S(  25,   15), S(  26,   20), S(  40,   20), S(  43,   10), S(  16,   23), S(  30,   23), S(  52,   12),
};
inline const std::array queen_psqt = {
  S( -41,  -39), S( -36,  -48), S( -24,  -64), S(   8,  -89), S( -36,  -69), S( -77,  -76), S( -47,  -47), S( -50,  -44),
  S( -51,  -45), S( -35,  -27), S( -14,  -46), S( -16,  -53), S(   0,  -62), S(  -5,  -51), S( -11,  -51), S( -39,  -35),
  S( -42,  -41), S( -23,  -32), S( -28,   -8), S( -19,  -16), S( -17,    8), S(   4,   -4), S(  11,   -2), S( -14,  -22),
  S( -39,  -30), S( -40,  -17), S( -20,   -1), S( -16,   52), S(  -2,   26), S(  -7,   42), S(  12,   22), S( -11,   15),
  S( -39,  -29), S( -37,    8), S(  -9,   10), S(  -3,   56), S(  20,   79), S(  38,   58), S(  17,   73), S(  28,   27),
  S( -35,  -27), S( -21,   -4), S(  -6,    9), S(  12,   39), S(  57,   59), S( 113,   85), S(  96,   66), S(  68,   42),
  S( -28,  -22), S( -35,   19), S(   4,   30), S(   7,   41), S(  36,   49), S(  86,   55), S(  66,   34), S(  94,   22),
  S( -24,  -34), S(   2,   -5), S(  21,    3), S(  23,   19), S(  46,   33), S(  54,   38), S(  37,    8), S(  43,   12),
};
inline const std::array king_psqt = {
  S( -15,  -47), S(  51,  -75), S(  74,  -57), S( -37,  -71), S(  69, -109), S(  25,  -81), S( 171, -115), S( 135, -132),
  S(   6,  -44), S(   4,  -41), S(  -2,  -16), S( -48,   -5), S( -43,   -1), S(  31,  -21), S(  86,  -47), S( 111,  -79),
  S( -24,  -53), S( -10,  -16), S( -47,    4), S( -69,   26), S( -84,   34), S( -66,   20), S( -17,  -14), S( -40,  -36),
  S( -19,  -21), S( -23,   -3), S( -38,   34), S( -29,   39), S( -33,   41), S( -58,   43), S( -53,    8), S( -53,  -25),
  S( -10,   -7), S(  -2,   39), S(   0,   47), S(  -1,   48), S(  -4,   65), S(  -3,   76), S(  -8,   54), S( -24,  -11),
  S(   0,   11), S(   2,   35), S(   8,   59), S(  10,   55), S(  11,   63), S(  13,   92), S(  12,   68), S(   1,   23),
  S(   0,  -10), S(   4,   13), S(   8,   33), S(   6,   24), S(   8,   27), S(   9,   41), S(   3,   32), S(  -1,   -3),
  S(  -1,  -12), S(   2,   -3), S(   2,    3), S(   0,   -1), S(   0,    0), S(   2,    4), S(   0,    2), S(   0,   -7),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
