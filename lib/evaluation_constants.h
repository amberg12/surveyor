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
inline const pair pawn_material = S(138, 263);
inline const pair knight_material = S(569, 680);
inline const pair bishop_material = S(583, 749);
inline const pair rook_material = S(775, 1230);
inline const pair queen_material = S(1672, 1989);

inline const pair bishop_pair = S(112, 146);

inline const std::array knight_mobility = {
  S(-52, -73), S(-21, -43), S(-3, -23), S(0, -3), S(12, 17), S(11, 25), S(15, 31), S(16, 35), S(20, 34),
};
inline const std::array bishop_mobility = {
  S(-67, -94), S(-36, -57), S(-19, -26), S(-3, -17), S(1, -1), S(4, 13), S(6, 21), S(11, 22), S(15, 24), S(21, 35), S(26, 22), S(29, 30), S(2, 0), S(7, 25),
};
inline const std::array rook_mobility = {
  S(-76, -82), S(-57, -45), S(-42, -28), S(-30, -16), S(-28, -9), S(-14, -5), S(-7, -1), S(5, 3), S(15, 9), S(21, 17), S(29, 22), S(35, 32), S(46, 37), S(62, 19), S(41, 46),
};
inline const std::array queen_mobility = {
  S(-38, -67), S(-30, -66), S(-24, -86), S(-19, -75), S(-10, -62), S(-5, -43), S(1, -36), S(1, -13), S(5, 3), S(5, 18), S(6, 30), S(6, 42), S(11, 42), S(16, 54), S(16, 57), S(15, 66), S(19, 63), S(20, 56), S(33, 60), S(34, 46), S(40, 40), S(32, 43), S(19, 12), S(8, 7), S(-25, -28), S(-35, -40), S(-51, -61), S(-53, -63),
};

inline const pair pawn_threat_knight = S(77, 25);
inline const pair pawn_threat_bishop = S(85, 38);
inline const pair pawn_threat_rook = S(58, 30);
inline const pair pawn_threat_queen = S(38, -11);

inline const pair pp_threat_knight = S(30, 18);
inline const pair pp_threat_bishop = S(18, 0);
inline const pair pp_threat_rook = S(7, 16);
inline const pair pp_threat_queen = S(29, -33);

inline const pair knight_threat_pawn = S(11, 30);
inline const pair knight_threat_bishop = S(55, 32);
inline const pair knight_threat_rook = S(92, -12);
inline const pair knight_threat_queen = S(35, -15);

inline const pair bishop_threat_pawn = S(7, 15);
inline const pair bishop_threat_knight = S(35, 26);
inline const pair bishop_threat_rook = S(80, 19);
inline const pair bishop_threat_queen = S(71, 23);

inline const pair rook_threat_pawn = S(0, 41);
inline const pair rook_threat_knight = S(46, 27);
inline const pair rook_threat_bishop = S(51, 30);
inline const pair rook_threat_queen = S(73, -7);

inline const pair king_threat_pawn = S(38, 75);
inline const pair king_threat_knight = S(-2, 8);
inline const pair king_threat_bishop = S(38, 12);
inline const pair king_threat_rook = S(-45, -7);

inline const pair hanging = S(25, 41);

inline const std::array passed_pawn = {
  S(-28, -103), S(-41, -89), S(-50, 5), S(-13, 85), S(56, 155), S(153, 246),
};
inline const std::array defended_passed_pawn = {
  S(9, -10), S(16, 27), S(26, 41), S(13, 77), S(47, 109), S(48, 148),
};
inline const std::array blocked_passed_pawn = {
  S(-1, -13), S(8, -4), S(-12, -16), S(-23, -32), S(-16, -64), S(-29, -97),
};
inline const std::array friendly_passer_tropism = {
  S(3, 69), S(5, 67), S(14, 40), S(7, 32), S(14, 34), S(22, 29), S(9, 25),
};
inline const std::array enemy_passer_tropism = {
  S(-38, -2), S(12, 17), S(20, 44), S(28, 52), S(24, 60), S(20, 61), S(7, 65),
};

inline const pair isolated_pawn = S(-6, -2);
inline const std::array defended_pawn = {
  S(17, 13), S(23, 9), S(21, 20), S(84, 60), S(61, 106),
};
inline const std::array phalanx = {
  S(7, -7), S(19, 9), S(25, 37), S(79, 89), S(54, 92), S(7, 21),
};

inline const std::array shelter_centre = {
  S(-32, -13), S(23, -15), S(-3, -7), S(4, -16), S(-8, -1), S(-1, 9), S(18, 45),
};
inline const std::array shelter_mid = {
  S(-58, -19), S(37, -23), S(21, -16), S(20, -19), S(-1, 0), S(-20, 17), S(0, 61),
};
inline const std::array shelter_edge = {
  S(-43, -19), S(26, -36), S(18, -16), S(15, -19), S(-9, -1), S(-18, 29), S(10, 64),
};

inline const std::array king_ring = {
  S(-41, 7), S(-28, 12), S(-25, -1), S(-29, 7), S(-8, -87),
};

inline const std::array pawn_psqt = {
  S( -53,   -4), S( -19,   -2), S( -43,  -14), S( -48,  -20), S( -48,    0), S(   5,  -31), S(  52,  -58), S( -41,  -57),
  S( -53,  -23), S( -43,  -24), S( -27,  -53), S( -41,  -40), S( -36,  -36), S( -66,  -37), S(  14,  -83), S( -42,  -74),
  S( -62,   -5), S( -47,  -14), S( -23,  -47), S( -10,  -62), S( -22,  -65), S( -28,  -52), S( -28,  -45), S( -53,  -56),
  S( -49,   14), S(   5,    0), S( -15,  -25), S(  18,  -58), S(  19,  -63), S(   4,  -60), S(  21,  -33), S( -31,  -42),
  S( -15,   84), S(  17,   78), S(  49,   41), S(  71,   10), S(  56,    7), S(  52,    3), S(  26,   54), S(  -3,   35),
  S( 105,  141), S( 116,  149), S(  98,  133), S(  98,  113), S(  86,   81), S(  19,   60), S(  10,   96), S(   7,   92),
};
inline const std::array knight_psqt = {
  S( -44,  -28), S( -53,  -41), S( -41,  -21), S( -29,  -21), S( -33,  -17), S(  -3,  -25), S( -40,  -31), S( -23,  -31),
  S( -43,  -33), S( -46,  -20), S( -37,   -9), S(  -7,   10), S(  13,    3), S(  11,  -18), S( -11,  -22), S(  -7,  -25),
  S( -62,  -21), S( -21,    1), S(  -8,    7), S(  13,   30), S(  27,   25), S(  34,    3), S(  36,   -9), S( -30,  -21),
  S( -33,   -3), S(  -8,    6), S(  19,   36), S(  35,   41), S(  46,   47), S(  50,   21), S(  41,   12), S(  10,  -10),
  S( -11,   10), S(   8,   19), S(  15,   42), S(  75,   50), S(  39,   55), S( 112,   26), S(  33,   22), S(  64,   -3),
  S( -24,  -10), S(  -3,   11), S(  31,   26), S(  45,   25), S(  65,   20), S(  61,   42), S(  26,   16), S(   6,    0),
  S( -56,  -15), S( -34,   -7), S(   2,   -1), S(  30,   23), S(  17,   10), S(  37,   13), S( -26,  -19), S(  -2,  -19),
  S(-142,  -61), S( -20,  -22), S( -30,  -17), S(  -7,   -1), S(   5,   -3), S( -47,  -16), S(  -4,   -7), S( -23,  -41),
};
inline const std::array bishop_psqt = {
  S( -17,  -37), S( -17,  -28), S( -11,  -15), S( -20,   -8), S( -19,  -28), S( -31,    4), S( -11,  -21), S(  -4,   -4),
  S(   9,  -21), S(   4,   -6), S(  10,  -11), S( -13,    7), S(   7,   -4), S(  12,  -14), S(  52,  -22), S( -14,  -21),
  S( -19,   -9), S(  19,   11), S(  14,   17), S(  -1,    9), S(   3,   39), S(  25,    4), S(  14,  -12), S(   8,   -4),
  S( -10,  -11), S( -21,   16), S(  11,   19), S(  21,   41), S(  27,   15), S(  13,   12), S(   6,   -3), S(  -3,  -21),
  S( -14,   -1), S(  -4,   15), S(  -2,   30), S(  49,   32), S(  27,   31), S(  22,   12), S(  11,    8), S(   0,   -9),
  S( -15,   -4), S(   0,   17), S(  -2,   20), S(  24,    6), S(  50,   16), S(  42,   34), S(  45,   13), S(  14,   -7),
  S( -34,   -2), S( -26,    2), S(  -9,    0), S( -13,   -5), S( -26,   -1), S(  11,    0), S( -11,   -9), S( -22,  -25),
  S( -18,    0), S( -13,   -6), S( -27,  -13), S( -16,   -8), S( -15,    0), S( -51,  -16), S( -11,   -9), S(  -7,  -10),
};
inline const std::array rook_psqt = {
  S( -25,  -14), S( -14,  -18), S(   3,  -12), S(  15,  -23), S(  32,  -42), S(  23,  -35), S( -22,   -3), S(  -7,  -62),
  S( -68,   -6), S( -42,  -12), S( -30,    2), S( -19,  -17), S( -22,  -26), S(   6,  -36), S(   4,  -39), S( -79,  -39),
  S( -51,    5), S( -42,    2), S( -35,   13), S( -24,   -8), S( -11,  -15), S(   1,  -21), S(  19,  -26), S( -13,  -33),
  S( -47,   14), S( -42,   10), S( -25,   11), S(   0,   -6), S( -15,  -14), S(  -2,  -13), S(  -9,   -9), S( -19,  -26),
  S( -41,   30), S( -29,   22), S(  -4,   19), S(  11,    7), S(  14,  -13), S(  37,   -6), S(  13,   -1), S(   3,   -4),
  S( -17,   33), S(   9,   17), S(   6,   22), S(  26,    7), S(  46,   -1), S(  57,    1), S(  22,   17), S(   7,    2),
  S( -18,   40), S( -16,   45), S(  26,   27), S(  47,   20), S(  35,   14), S(  58,   15), S(  27,   32), S(  53,   15),
  S(  10,   14), S(  11,   13), S(  22,   19), S(  34,   19), S(  34,   13), S(  16,   20), S(  19,   26), S(  40,   13),
};
inline const std::array queen_psqt = {
  S( -28,  -27), S( -28,  -32), S( -13,  -29), S(  10,  -31), S( -18,  -38), S( -70,  -63), S( -45,  -46), S( -47,  -37),
  S( -38,  -29), S( -26,  -15), S(  -8,  -11), S(  -2,  -10), S(   8,   -4), S(   9,  -38), S(  -6,  -34), S( -25,  -28),
  S( -43,  -23), S( -15,   -5), S(  -9,    7), S( -10,    6), S(  -2,   39), S(  12,    4), S(  22,    1), S( -10,  -16),
  S( -27,   -2), S( -33,   -4), S(  -9,   19), S(   0,   41), S(  14,   27), S(  11,   20), S(  16,    9), S(  -1,    5),
  S( -25,    1), S( -13,   33), S(  -9,   20), S(   2,   54), S(  27,   49), S(  36,   14), S(  30,   37), S(  30,  -24),
  S( -21,   -8), S(  -9,    5), S(  10,   24), S(   8,   28), S(  42,   35), S(  57,   26), S(  57,   23), S(  30,   -4),
  S( -26,  -17), S( -38,   11), S(  -5,   28), S(  -3,   32), S(   8,   16), S(  58,   15), S(  46,   17), S(  74,   -2),
  S( -24,  -39), S( -13,  -15), S(   3,   -5), S(   0,   -9), S(  15,   -3), S(  22,    7), S(  17,   -3), S(  24,    0),
};
inline const std::array king_psqt = {
  S( -28,  -39), S(  20,  -51), S(  43,  -38), S( -54,  -50), S(  42,  -81), S(   2,  -52), S( 125,  -87), S(  84, -107),
  S(  -4,  -32), S(   7,  -25), S(   3,   -7), S( -32,    4), S( -22,    8), S(  35,   -3), S(  89,  -33), S(  86,  -57),
  S( -20,  -45), S(   0,  -22), S( -18,    1), S( -26,   20), S( -41,   25), S( -22,   17), S(  12,  -13), S( -45,  -22),
  S( -19,  -21), S( -28,   -7), S( -23,   13), S( -21,   22), S( -19,   28), S( -38,   24), S( -37,   -1), S( -56,  -37),
  S( -14,   -6), S(  -3,   19), S(  -2,   34), S(  -4,   37), S(  -8,   46), S(   1,   54), S( -10,   28), S( -26,  -12),
  S(  -1,   12), S(   1,   23), S(   6,   46), S(   6,   46), S(   8,   51), S(  11,   68), S(  10,   47), S(  -2,   20),
  S(   0,   -3), S(   3,   17), S(   4,   23), S(   6,   20), S(   7,   25), S(  10,   39), S(   2,   25), S(   0,    4),
  S(  -1,   -9), S(   0,   -7), S(   1,    6), S(   0,    2), S(   1,    5), S(   1,    3), S(   0,    1), S(   0,    0),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
