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
inline const pair pawn_material = S(130, 252);
inline const pair knight_material = S(561, 679);
inline const pair bishop_material = S(582, 754);
inline const pair rook_material = S(777, 1230);
inline const pair queen_material = S(1670, 1996);

inline const pair bishop_pair = S(113, 148);

inline const std::array knight_mobility = {
  S(-50, -72), S(-17, -41), S(-4, -18), S(6, 0), S(8, 15), S(11, 26), S(14, 30), S(15, 31), S(16, 28),
};
inline const std::array bishop_mobility = {
  S(-65, -88), S(-35, -50), S(-16, -21), S(-3, -16), S(4, 3), S(13, 16), S(9, 25), S(11, 23), S(21, 26), S(18, 31), S(22, 18), S(22, 22), S(-3, -6), S(0, 14),
};
inline const std::array rook_mobility = {
  S(-78, -83), S(-54, -45), S(-45, -26), S(-28, -15), S(-27, -4), S(-12, -4), S(-6, 1), S(5, 3), S(13, 10), S(21, 17), S(29, 22), S(36, 30), S(44, 33), S(61, 17), S(40, 41),
};
inline const std::array queen_mobility = {
  S(-39, -67), S(-28, -67), S(-20, -86), S(-12, -74), S(-4, -61), S(-4, -42), S(2, -34), S(2, -10), S(7, 6), S(9, 22), S(10, 34), S(11, 46), S(15, 46), S(15, 56), S(15, 58), S(15, 68), S(18, 63), S(20, 56), S(29, 59), S(29, 43), S(34, 36), S(26, 37), S(14, 8), S(3, 2), S(-28, -32), S(-37, -43), S(-52, -62), S(-53, -64),
};

inline const pair pawn_threat_knight = S(82, 39);
inline const pair pawn_threat_bishop = S(89, 52);
inline const pair pawn_threat_rook = S(65, 50);
inline const pair pawn_threat_queen = S(51, -2);

inline const pair pp_threat_knight = S(27, 29);
inline const pair pp_threat_bishop = S(18, -1);
inline const pair pp_threat_rook = S(11, 23);
inline const pair pp_threat_queen = S(24, -33);

inline const pair knight_threat_pawn = S(2, 29);
inline const pair knight_threat_bishop = S(57, 46);
inline const pair knight_threat_rook = S(99, 16);
inline const pair knight_threat_queen = S(50, -5);

inline const pair bishop_threat_pawn = S(-6, 6);
inline const pair bishop_threat_knight = S(33, 29);
inline const pair bishop_threat_rook = S(79, 40);
inline const pair bishop_threat_queen = S(79, 29);

inline const pair rook_threat_pawn = S(-9, 32);
inline const pair rook_threat_knight = S(26, 28);
inline const pair rook_threat_bishop = S(39, 20);
inline const pair rook_threat_queen = S(98, 9);

inline const std::array passed_pawn = {
  S(-27, -105), S(-45, -93), S(-50, 5), S(-13, 86), S(55, 153), S(155, 245),
};
inline const std::array defended_passed_pawn = {
  S(10, -8), S(16, 29), S(27, 37), S(15, 74), S(48, 106), S(53, 152),
};
inline const std::array blocked_passed_pawn = {
  S(0, -14), S(7, -5), S(-8, -14), S(-20, -30), S(-16, -63), S(-31, -96),
};
inline const std::array friendly_passer_tropism = {
  S(6, 72), S(3, 64), S(16, 40), S(7, 27), S(11, 31), S(21, 32), S(7, 23),
};
inline const std::array enemy_passer_tropism = {
  S(-56, -50), S(11, 30), S(22, 50), S(32, 57), S(25, 63), S(23, 66), S(13, 72),
};

inline const pair isolated_pawn = S(-7, -4);
inline const std::array defended_pawn = {
  S(20, 18), S(28, 21), S(28, 37), S(87, 80), S(67, 122),
};
inline const std::array phalanx = {
  S(7, -7), S(20, 9), S(25, 39), S(77, 90), S(54, 93), S(7, 21),
};

inline const std::array shelter_centre = {
  S(-33, -15), S(24, -13), S(0, -4), S(3, -14), S(-7, 0), S(-2, 6), S(16, 42),
};
inline const std::array shelter_mid = {
  S(-54, -17), S(37, -18), S(18, -17), S(20, -20), S(-2, 0), S(-19, 15), S(-1, 59),
};
inline const std::array shelter_edge = {
  S(-42, -14), S(23, -34), S(19, -17), S(13, -19), S(-6, -1), S(-18, 26), S(9, 61),
};

inline const std::array king_ring = {
  S(-37, 12), S(-28, 17), S(-30, 0), S(-33, 9), S(-9, -82),
};

inline const std::array pawn_psqt = {
  S( -57,    0), S( -16,   -2), S( -35,   -9), S( -43,  -18), S( -42,    6), S(   6,  -26), S(  55,  -55), S( -43,  -57),
  S( -57,  -22), S( -39,  -22), S( -21,  -47), S( -39,  -37), S( -32,  -31), S( -60,  -35), S(  18,  -77), S( -40,  -73),
  S( -62,   -4), S( -50,  -13), S( -22,  -42), S( -10,  -61), S( -22,  -64), S( -28,  -50), S( -27,  -45), S( -51,  -52),
  S( -50,   17), S(   4,    0), S( -16,  -22), S(  16,  -55), S(  20,  -60), S(   8,  -58), S(  25,  -35), S( -32,  -42),
  S( -17,   82), S(  17,   76), S(  47,   37), S(  73,    6), S(  53,    2), S(  50,   -3), S(  26,   49), S(  -1,   30),
  S( 103,  138), S( 115,  147), S(  96,  128), S(  97,  108), S(  80,   74), S(  12,   52), S(  -9,   86), S(   2,   87),
};
inline const std::array knight_psqt = {
  S( -45,  -30), S( -55,  -44), S( -40,  -22), S( -29,  -23), S( -33,  -17), S(  -3,  -26), S( -36,  -33), S( -24,  -33),
  S( -45,  -35), S( -47,  -22), S( -36,   -9), S(  -7,    8), S(  10,    2), S(  10,  -17), S( -12,  -23), S(  -8,  -27),
  S( -63,  -23), S( -17,    4), S(  -4,   11), S(  18,   35), S(  27,   28), S(  34,    6), S(  39,   -7), S( -32,  -21),
  S( -33,   -4), S(  -5,    8), S(  21,   41), S(  38,   45), S(  44,   50), S(  51,   20), S(  42,   16), S(  10,  -13),
  S(  -9,   10), S(  18,   27), S(  26,   49), S(  80,   56), S(  44,   58), S( 116,   29), S(  39,   28), S(  63,   -4),
  S( -26,  -12), S(  -4,   11), S(  35,   30), S(  52,   27), S(  65,   21), S(  63,   43), S(  27,   16), S(   4,   -1),
  S( -62,  -19), S( -39,   -7), S(  -1,   -5), S(  24,   20), S(  12,    4), S(  31,    7), S( -31,  -22), S(  -8,  -23),
  S(-147,  -67), S( -21,  -23), S( -33,  -18), S(  -8,   -1), S(   2,   -6), S( -51,  -20), S(  -5,   -8), S( -25,  -43),
};
inline const std::array bishop_psqt = {
  S( -20,  -40), S( -17,  -31), S( -10,  -22), S( -19,  -10), S( -18,  -30), S( -36,    1), S( -10,  -23), S(  -6,   -7),
  S(   7,  -24), S(   2,  -10), S(   9,  -12), S( -17,    4), S(   9,   -4), S(  13,  -15), S(  55,  -22), S( -15,  -23),
  S( -23,  -13), S(  23,   13), S(  19,   22), S(   2,   13), S(   9,   47), S(  27,    9), S(  20,   -8), S(   7,   -8),
  S( -10,  -15), S( -18,   19), S(  15,   24), S(  34,   52), S(  37,   21), S(  20,   16), S(   7,   -3), S(  -2,  -24),
  S( -16,   -4), S(  -6,   18), S(   3,   34), S(  60,   38), S(  34,   37), S(  26,   16), S(  11,    7), S(   0,  -11),
  S( -21,   -9), S(   1,   19), S(   1,   23), S(  28,   10), S(  53,   18), S(  43,   36), S(  45,   14), S(   8,  -13),
  S( -40,   -8), S( -32,    1), S(  -9,    2), S( -16,   -5), S( -31,    0), S(   6,   -2), S( -20,  -12), S( -39,  -29),
  S( -22,   -4), S( -13,   -4), S( -29,  -13), S( -18,   -8), S( -17,    0), S( -60,  -20), S( -13,   -9), S( -12,  -12),
};
inline const std::array rook_psqt = {
  S( -29,  -19), S( -13,  -25), S(   0,  -16), S(   9,  -27), S(  28,  -46), S(  19,  -39), S( -26,   -8), S(  -9,  -64),
  S( -67,   -8), S( -43,  -14), S( -31,    2), S( -21,  -18), S( -23,  -26), S(   6,  -36), S(   3,  -42), S( -79,  -39),
  S( -51,    3), S( -38,    4), S( -35,   12), S( -27,   -7), S( -13,  -14), S(  -3,  -21), S(  20,  -27), S( -12,  -33),
  S( -43,   16), S( -41,   11), S( -26,   11), S(   0,   -3), S( -18,  -15), S(  -4,  -10), S(  -9,   -9), S( -20,  -29),
  S( -38,   30), S( -24,   21), S(  -6,   18), S(  11,    7), S(  13,  -15), S(  34,   -5), S(  14,   -2), S(   6,   -5),
  S( -16,   33), S(   9,   14), S(   6,   21), S(  22,    5), S(  44,   -4), S(  54,    2), S(  21,   18), S(   5,    2),
  S( -15,   45), S( -12,   49), S(  34,   35), S(  55,   27), S(  43,   23), S(  68,   20), S(  32,   36), S(  56,   18),
  S(   9,   16), S(   9,   15), S(  21,   20), S(  33,   17), S(  33,   12), S(  15,   20), S(  19,   25), S(  39,   14),
};
inline const std::array queen_psqt = {
  S( -30,  -29), S( -30,  -35), S( -14,  -32), S(   6,  -36), S( -21,  -41), S( -72,  -65), S( -47,  -47), S( -50,  -39),
  S( -40,  -31), S( -28,  -17), S( -11,  -11), S(  -3,   -9), S(   5,   -5), S(   8,  -37), S(  -7,  -35), S( -27,  -29),
  S( -41,  -23), S( -13,   -4), S(  -7,   10), S( -12,    7), S(   0,   43), S(   9,    6), S(  20,    0), S( -14,  -18),
  S( -27,   -2), S( -29,   -1), S( -10,   22), S(   2,   47), S(  14,   29), S(  14,   24), S(  20,    7), S(  -5,    1),
  S( -23,    1), S( -10,   35), S(  -4,   26), S(   6,   59), S(  30,   52), S(  37,   15), S(  29,   35), S(  30,  -29),
  S( -22,   -9), S(  -6,    8), S(  13,   27), S(  11,   32), S(  43,   37), S(  60,   29), S(  58,   23), S(  25,   -8),
  S( -24,  -18), S( -33,   13), S(   0,   30), S(   1,   34), S(  11,   18), S(  60,   17), S(  49,   17), S(  71,   -5),
  S( -24,  -41), S( -13,  -17), S(   1,   -8), S(  -3,  -11), S(  12,   -6), S(  20,    4), S(  14,   -5), S(  22,   -3),
};
inline const std::array king_psqt = {
  S( -28,  -43), S(  19,  -58), S(  41,  -44), S( -56,  -57), S(  43,  -85), S(   0,  -61), S( 120,  -94), S(  81, -116),
  S(  -6,  -39), S(   5,  -30), S(   3,  -11), S( -33,    2), S( -23,    3), S(  32,  -10), S(  87,  -41), S(  84,  -65),
  S( -21,  -46), S(   0,  -26), S( -20,   -1), S( -28,   18), S( -40,   21), S( -19,   15), S(  15,  -16), S( -46,  -30),
  S( -19,  -21), S( -28,   -5), S( -23,   11), S( -20,   21), S( -19,   24), S( -38,   25), S( -38,    2), S( -55,  -35),
  S( -13,   -5), S(  -1,   30), S(  -2,   38), S(  -3,   40), S(  -7,   50), S(   1,   59), S(  -9,   39), S( -24,   -7),
  S(   0,   16), S(   3,   34), S(   6,   52), S(   6,   51), S(   8,   55), S(  13,   81), S(  11,   61), S(  -1,   24),
  S(   0,   -3), S(   4,   21), S(   5,   26), S(   6,   21), S(   8,   28), S(  10,   44), S(   3,   29), S(   0,    4),
  S(  -1,   -9), S(   0,   -6), S(   1,    6), S(   0,    1), S(   1,    5), S(   2,    3), S(   0,    1), S(   0,    0),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
