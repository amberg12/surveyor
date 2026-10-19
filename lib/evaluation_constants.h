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
inline const pair pawn_material = S(137, 261);
inline const pair knight_material = S(559, 678);
inline const pair bishop_material = S(587, 750);
inline const pair rook_material = S(772, 1220);
inline const pair queen_material = S(1672, 1911);

inline const pair bishop_pair = S(113, 139);

inline const std::array knight_mobility = {
  S(-50, -72), S(-17, -41), S(-3, -22), S(4, 0), S(8, 16), S(10, 26), S(15, 28), S(14, 30), S(17, 34),
};
inline const std::array bishop_mobility = {
  S(-64, -88), S(-35, -55), S(-16, -24), S(-6, -17), S(-2, 1), S(8, 12), S(7, 23), S(12, 24), S(17, 26), S(19, 31), S(24, 22), S(25, 24), S(1, -1), S(7, 22),
};
inline const std::array rook_mobility = {
  S(-70, -76), S(-49, -41), S(-39, -24), S(-27, -9), S(-27, -5), S(-6, -3), S(-7, -1), S(4, 5), S(12, 7), S(23, 16), S(29, 21), S(33, 28), S(37, 30), S(54, 14), S(34, 37),
};
inline const std::array queen_mobility = {
  S(-28, -63), S(-21, -61), S(-13, -79), S(-8, -66), S(0, -51), S(2, -31), S(6, -25), S(5, 0), S(6, 17), S(5, 31), S(9, 42), S(9, 54), S(14, 51), S(13, 57), S(14, 60), S(12, 66), S(18, 58), S(20, 48), S(28, 48), S(29, 28), S(33, 21), S(23, 21), S(7, -6), S(-4, -11), S(-33, -39), S(-43, -50), S(-52, -60), S(-54, -62),
};

inline const pair pawn_threat_knight = S(79, 24);
inline const pair pawn_threat_bishop = S(85, 38);
inline const pair pawn_threat_rook = S(56, 29);
inline const pair pawn_threat_queen = S(39, -8);

inline const pair pp_threat_knight = S(29, 19);
inline const pair pp_threat_bishop = S(19, 0);
inline const pair pp_threat_rook = S(8, 14);
inline const pair pp_threat_queen = S(24, -44);

inline const pair knight_threat_pawn = S(10, 31);
inline const pair knight_threat_bishop = S(57, 30);
inline const pair knight_threat_rook = S(95, -10);
inline const pair knight_threat_queen = S(39, -14);

inline const pair bishop_threat_pawn = S(5, 15);
inline const pair bishop_threat_knight = S(35, 25);
inline const pair bishop_threat_rook = S(80, 17);
inline const pair bishop_threat_queen = S(73, 25);

inline const pair rook_threat_pawn = S(3, 36);
inline const pair rook_threat_knight = S(49, 27);
inline const pair rook_threat_bishop = S(49, 26);
inline const pair rook_threat_queen = S(78, 0);

inline const pair king_threat_pawn = S(19, 77);
inline const pair king_threat_knight = S(-11, 9);
inline const pair king_threat_bishop = S(12, 0);
inline const pair king_threat_rook = S(-42, -5);

inline const pair knight_check_threat = S(-30, -3);
inline const pair bishop_check_threat = S(-18, -27);
inline const pair rook_check_threat = S(-54, -14);
inline const pair queen_check_threat = S(-18, -79);

inline const pair hanging = S(27, 41);

inline const std::array passed_pawn = {
  S(-30, -100), S(-42, -86), S(-50, 5), S(-8, 88), S(62, 154), S(158, 244),
};
inline const std::array defended_passed_pawn = {
  S(10, -7), S(16, 27), S(26, 37), S(15, 74), S(50, 109), S(49, 149),
};
inline const std::array blocked_passed_pawn = {
  S(0, -12), S(10, -4), S(-12, -18), S(-22, -31), S(-17, -66), S(-27, -97),
};
inline const std::array friendly_passer_tropism = {
  S(3, 72), S(6, 67), S(20, 42), S(12, 29), S(14, 36), S(26, 33), S(7, 24),
};
inline const std::array enemy_passer_tropism = {
  S(-26, 0), S(7, 15), S(20, 47), S(29, 55), S(22, 58), S(23, 61), S(12, 67),
};

inline const pair isolated_pawn = S(-9, -2);
inline const std::array defended_pawn = {
  S(20, 15), S(23, 14), S(19, 20), S(85, 62), S(63, 106),
};
inline const std::array phalanx = {
  S(4, -12), S(21, 10), S(24, 38), S(77, 88), S(53, 90), S(7, 20),
};

inline const std::array shelter_centre = {
  S(-32, -13), S(16, -21), S(-1, -5), S(0, -14), S(-6, -1), S(1, 9), S(21, 46),
};
inline const std::array shelter_mid = {
  S(-49, -13), S(32, -25), S(12, -18), S(16, -23), S(-1, -1), S(-15, 18), S(5, 64),
};
inline const std::array shelter_edge = {
  S(-39, -13), S(22, -37), S(20, -21), S(11, -20), S(-8, -2), S(-19, 30), S(13, 65),
};

inline const std::array king_ring = {
  S(-37, 9), S(-35, 10), S(-18, -2), S(-10, 11), S(10, 11),
};

inline const std::array pawn_psqt = {
  S( -56,   -3), S( -27,   -5), S( -41,  -15), S( -55,  -21), S( -50,   -1), S(  -5,  -30), S(  45,  -58), S( -46,  -58),
  S( -58,  -25), S( -45,  -25), S( -31,  -54), S( -41,  -42), S( -45,  -38), S( -71,  -40), S(  11,  -82), S( -43,  -75),
  S( -62,   -3), S( -46,  -18), S( -18,  -45), S(  -9,  -62), S( -19,  -69), S( -32,  -53), S( -23,  -43), S( -50,  -55),
  S( -45,   15), S(   6,    0), S( -15,  -25), S(  25,  -55), S(  20,  -65), S(  12,  -59), S(  22,  -37), S( -31,  -40),
  S( -17,   84), S(  17,   78), S(  51,   41), S(  72,   11), S(  65,    9), S(  50,    3), S(  30,   56), S(  -4,   36),
  S( 105,  143), S( 118,  149), S(  99,  134), S( 102,  115), S(  87,   83), S(  24,   63), S(  16,   98), S(  10,   91),
};
inline const std::array knight_psqt = {
  S( -41,  -26), S( -45,  -41), S( -38,  -19), S( -26,  -20), S( -33,  -17), S(  -5,  -28), S( -33,  -30), S( -19,  -30),
  S( -39,  -32), S( -42,  -18), S( -31,   -7), S(  -3,   11), S(  18,    3), S(   6,  -19), S( -15,  -22), S(  -2,  -23),
  S( -54,  -18), S( -14,    3), S(  -2,    9), S(  21,   30), S(  30,   22), S(  39,    1), S(  39,  -12), S( -23,  -19),
  S( -29,   -3), S(  -3,    9), S(  20,   36), S(  38,   36), S(  29,   48), S(  53,   16), S(  19,   11), S(  17,  -12),
  S(  -8,   13), S(   8,   24), S(  21,   41), S(  50,   51), S(  37,   49), S(  87,   25), S(  32,   20), S(  47,   -4),
  S( -21,   -8), S(   0,   12), S(  25,   24), S(  46,   21), S(  66,   18), S(  55,   38), S(  20,   14), S(   2,   -1),
  S( -54,  -13), S( -31,   -5), S(   4,    0), S(  23,   20), S(  13,    8), S(  38,   14), S( -23,  -17), S(  -6,  -19),
  S(-141,  -61), S( -19,  -21), S( -30,  -16), S(  -5,    0), S(   5,   -3), S( -44,  -15), S(  -5,   -7), S( -21,  -39),
};
inline const std::array bishop_psqt = {
  S( -19,  -36), S( -20,  -29), S( -13,  -17), S( -21,   -9), S( -23,  -29), S( -36,    1), S( -13,  -24), S(  -8,   -5),
  S(   8,  -21), S(   3,   -5), S(   6,  -12), S( -20,    7), S(  11,   -3), S(   2,  -17), S(  43,  -20), S( -16,  -20),
  S( -16,   -9), S(  16,   12), S(  15,   18), S(  -6,    6), S(   1,   38), S(  22,    3), S(  11,  -12), S(   2,   -5),
  S(  -9,  -10), S( -15,   19), S(   4,   18), S(  23,   43), S(  20,   13), S(  15,   11), S(   3,   -6), S(  -1,  -20),
  S( -12,    0), S(  -6,   18), S(   4,   29), S(  42,   30), S(  33,   33), S(  14,   10), S(  14,    6), S(  -4,  -11),
  S( -15,   -3), S(   3,   18), S(   2,   22), S(  33,    6), S(  51,   15), S(  53,   34), S(  40,    8), S(  26,   -7),
  S( -30,   -1), S( -26,    3), S(  -4,    4), S( -12,   -6), S( -20,   -1), S(  15,    0), S(  -3,   -8), S( -16,  -26),
  S( -21,    0), S( -11,   -4), S( -27,  -13), S( -14,   -7), S( -14,    0), S( -50,  -14), S( -10,   -7), S(  -2,   -7),
};
inline const std::array rook_psqt = {
  S( -20,   -3), S( -10,  -11), S(   2,   -8), S(  13,  -19), S(  28,  -42), S(  21,  -35), S( -28,    3), S(  -8,  -54),
  S( -60,    1), S( -38,   -7), S( -25,    8), S( -16,  -14), S( -20,  -23), S(   0,  -31), S(  -8,  -39), S( -77,  -33),
  S( -45,   11), S( -35,    8), S( -33,   14), S( -19,   -7), S( -13,  -14), S(   5,  -21), S(   7,  -27), S( -12,  -31),
  S( -38,   19), S( -38,   11), S( -19,    9), S(   1,   -7), S( -15,  -17), S(  -2,  -15), S( -17,  -11), S( -20,  -31),
  S( -37,   32), S( -25,   22), S(  -3,   17), S(  14,    3), S(  10,  -16), S(  40,  -11), S(   0,   -4), S(  -1,   -8),
  S( -15,   31), S(  12,   16), S(   8,   20), S(  20,    2), S(  43,   -7), S(  44,   -3), S(   9,   15), S(  -9,    0),
  S(  -6,   37), S(  -8,   41), S(  35,   23), S(  52,   15), S(  35,    9), S(  56,   12), S(  19,   32), S(  49,   13),
  S(  12,   12), S(  13,   12), S(  23,   17), S(  36,   15), S(  36,   10), S(  15,   17), S(  20,   25), S(  37,   13),
};
inline const std::array queen_psqt = {
  S( -14,  -10), S( -19,  -23), S(  -6,  -20), S(  18,  -20), S( -17,  -41), S( -66,  -59), S( -41,  -42), S( -41,  -33),
  S( -28,  -19), S( -13,    0), S(  -3,    2), S(   2,    9), S(  10,    4), S(  10,  -29), S( -10,  -31), S( -19,  -24),
  S( -32,  -10), S( -11,    9), S(  -4,   28), S(  -2,   20), S(   0,   36), S(  16,   11), S(  25,    0), S(  -6,  -13),
  S( -21,   -6), S( -23,    3), S(  -9,   29), S(   1,   48), S(  11,   13), S(  18,   10), S(  17,    4), S(   2,    2),
  S( -23,   -5), S( -16,   19), S(  -7,   17), S(   1,   42), S(  19,   28), S(  30,   -1), S(  24,   18), S(  34,  -35),
  S( -24,  -12), S( -15,   -2), S(  -3,    2), S(  -4,   13), S(  25,   18), S(  35,    9), S(  44,    9), S(  17,   -9),
  S( -17,   -8), S( -40,    8), S( -15,   20), S( -25,   13), S( -11,    4), S(  42,   11), S(  38,   13), S(  66,   -3),
  S( -17,  -27), S(  -6,  -10), S(   6,   -2), S(   5,   -1), S(  21,    3), S(  20,    7), S(  19,   -3), S(  35,    9),
};
inline const std::array king_psqt = {
  S( -33,  -42), S(   7,  -51), S(  34,  -37), S( -64,  -44), S(  29,  -75), S( -11,  -47), S( 103,  -85), S(  60, -109),
  S( -14,  -39), S(   1,  -25), S(   1,   -5), S( -32,    4), S( -21,    9), S(  34,   -8), S(  82,  -35), S(  75,  -63),
  S( -23,  -47), S(   0,  -22), S(  -9,    3), S( -11,   21), S( -23,   24), S(  -6,   16), S(  19,  -13), S( -48,  -28),
  S( -17,  -21), S( -21,   -4), S( -14,   15), S( -11,   26), S(  -7,   31), S( -27,   28), S( -31,   -1), S( -52,  -39),
  S( -11,   -5), S(  -1,   21), S(   1,   36), S(   0,   40), S(  -2,   49), S(   4,   55), S(  -9,   29), S( -25,  -14),
  S(  -2,   11), S(   2,   24), S(   7,   47), S(   8,   47), S(   9,   51), S(  12,   69), S(   8,   46), S(  -2,   19),
  S(   0,   -5), S(   2,   15), S(   4,   22), S(   7,   20), S(   8,   25), S(  10,   39), S(   1,   22), S(  -1,    2),
  S(  -1,  -10), S(   0,   -8), S(   0,    5), S(   1,    2), S(   1,    5), S(   1,    1), S(   0,    0), S(   0,   -1),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
