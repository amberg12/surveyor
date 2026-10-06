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
inline const pair pawn_material = S(136, 258);
inline const pair knight_material = S(564, 680);
inline const pair bishop_material = S(586, 752);
inline const pair rook_material = S(778, 1227);
inline const pair queen_material = S(1670, 1986);

inline const pair bishop_pair = S(113, 147);

inline const std::array knight_mobility = {
  S(-51, -73), S(-18, -44), S(-3, -23), S(3, 0), S(8, 18), S(10, 25), S(12, 34), S(17, 31), S(20, 32),
};
inline const std::array bishop_mobility = {
  S(-63, -94), S(-35, -57), S(-22, -28), S(-7, -20), S(0, -1), S(6, 8), S(7, 23), S(10, 26), S(17, 25), S(22, 36), S(26, 23), S(28, 31), S(1, 0), S(6, 26),
};
inline const std::array rook_mobility = {
  S(-75, -82), S(-53, -44), S(-43, -27), S(-29, -16), S(-31, -10), S(-9, -7), S(-4, 0), S(0, 3), S(13, 8), S(23, 18), S(29, 23), S(35, 31), S(46, 38), S(61, 17), S(39, 47),
};
inline const std::array queen_mobility = {
  S(-38, -67), S(-31, -66), S(-24, -86), S(-17, -75), S(-10, -62), S(-5, -44), S(0, -37), S(2, -13), S(4, 2), S(4, 17), S(9, 30), S(9, 42), S(14, 42), S(15, 53), S(13, 56), S(14, 67), S(18, 62), S(22, 56), S(30, 60), S(33, 46), S(40, 40), S(32, 43), S(20, 13), S(8, 7), S(-25, -28), S(-35, -40), S(-51, -61), S(-53, -63),
};

inline const pair pawn_threat_knight = S(79, 25);
inline const pair pawn_threat_bishop = S(83, 36);
inline const pair pawn_threat_rook = S(58, 30);
inline const pair pawn_threat_queen = S(39, -11);

inline const pair pp_threat_knight = S(30, 17);
inline const pair pp_threat_bishop = S(16, -1);
inline const pair pp_threat_rook = S(7, 16);
inline const pair pp_threat_queen = S(31, -32);

inline const pair knight_threat_pawn = S(8, 30);
inline const pair knight_threat_bishop = S(52, 30);
inline const pair knight_threat_rook = S(94, -13);
inline const pair knight_threat_queen = S(36, -15);

inline const pair bishop_threat_pawn = S(7, 16);
inline const pair bishop_threat_knight = S(37, 26);
inline const pair bishop_threat_rook = S(80, 17);
inline const pair bishop_threat_queen = S(72, 23);

inline const pair rook_threat_pawn = S(0, 36);
inline const pair rook_threat_knight = S(46, 25);
inline const pair rook_threat_bishop = S(53, 29);
inline const pair rook_threat_queen = S(73, -9);

inline const pair hanging = S(20, 43);

inline const std::array passed_pawn = {
  S(-27, -104), S(-44, -91), S(-49, 2), S(-12, 86), S(55, 153), S(154, 244),
};
inline const std::array defended_passed_pawn = {
  S(11, -7), S(16, 27), S(27, 39), S(13, 74), S(47, 108), S(48, 149),
};
inline const std::array blocked_passed_pawn = {
  S(1, -11), S(7, -3), S(-12, -16), S(-22, -30), S(-17, -64), S(-29, -99),
};
inline const std::array friendly_passer_tropism = {
  S(6, 69), S(4, 66), S(12, 38), S(6, 27), S(12, 34), S(24, 32), S(8, 23),
};
inline const std::array enemy_passer_tropism = {
  S(-59, -44), S(12, 26), S(24, 49), S(35, 57), S(27, 60), S(21, 69), S(12, 71),
};

inline const pair isolated_pawn = S(-6, -6);
inline const std::array defended_pawn = {
  S(18, 14), S(24, 11), S(20, 27), S(81, 69), S(63, 114),
};
inline const std::array phalanx = {
  S(5, -6), S(20, 7), S(26, 41), S(78, 91), S(54, 93), S(7, 21),
};

inline const std::array shelter_centre = {
  S(-34, -12), S(21, -15), S(-1, -7), S(3, -13), S(-6, -1), S(0, 7), S(17, 43),
};
inline const std::array shelter_mid = {
  S(-58, -17), S(39, -19), S(21, -15), S(18, -20), S(-1, 0), S(-18, 15), S(-1, 58),
};
inline const std::array shelter_edge = {
  S(-39, -15), S(24, -34), S(19, -16), S(12, -20), S(-10, -1), S(-17, 27), S(9, 62),
};

inline const std::array king_ring = {
  S(-37, 12), S(-30, 15), S(-27, 1), S(-33, 7), S(-9, -83),
};

inline const std::array pawn_psqt = {
  S( -53,    0), S( -19,    0), S( -42,  -11), S( -45,  -18), S( -46,    6), S(   1,  -27), S(  53,  -58), S( -41,  -55),
  S( -51,  -20), S( -42,  -22), S( -28,  -48), S( -42,  -39), S( -37,  -34), S( -65,  -36), S(  18,  -79), S( -44,  -71),
  S( -60,   -4), S( -48,  -15), S( -20,  -46), S( -11,  -63), S( -24,  -67), S( -29,  -48), S( -29,  -44), S( -50,  -52),
  S( -45,   18), S(   5,    0), S( -13,  -22), S(  15,  -58), S(  22,  -64), S(   9,  -60), S(  23,  -37), S( -33,  -39),
  S( -14,   83), S(  18,   77), S(  49,   38), S(  72,    7), S(  57,    4), S(  54,    0), S(  27,   51), S(   0,   33),
  S( 104,  139), S( 116,  147), S(  97,  129), S(  97,  108), S(  84,   76), S(  13,   53), S(  -3,   88), S(   1,   87),
};
inline const std::array knight_psqt = {
  S( -43,  -28), S( -51,  -41), S( -41,  -21), S( -29,  -21), S( -33,  -17), S(  -4,  -25), S( -38,  -30), S( -23,  -31),
  S( -43,  -33), S( -46,  -20), S( -36,   -9), S(  -6,   10), S(  12,    1), S(  10,  -18), S( -12,  -21), S(  -6,  -25),
  S( -61,  -21), S( -21,    1), S(  -4,    9), S(  12,   28), S(  24,   23), S(  30,    3), S(  35,  -10), S( -30,  -20),
  S( -35,   -4), S(  -8,    7), S(  16,   36), S(  34,   42), S(  48,   49), S(  51,   20), S(  41,   13), S(  12,  -10),
  S( -11,   11), S(  10,   19), S(  16,   42), S(  75,   50), S(  37,   54), S( 111,   25), S(  32,   22), S(  65,   -3),
  S( -24,  -11), S(  -3,   10), S(  32,   25), S(  45,   24), S(  65,   20), S(  62,   43), S(  27,   16), S(   7,    0),
  S( -56,  -15), S( -33,   -7), S(   2,   -1), S(  30,   23), S(  18,   10), S(  39,   13), S( -27,  -20), S(  -2,  -18),
  S(-142,  -61), S( -20,  -22), S( -30,  -17), S(  -7,   -1), S(   6,   -3), S( -46,  -17), S(  -4,   -6), S( -22,  -40),
};
inline const std::array bishop_psqt = {
  S( -17,  -36), S( -16,  -28), S( -12,  -16), S( -18,   -8), S( -18,  -27), S( -35,    5), S( -11,  -22), S(  -4,   -5),
  S(   9,  -21), S(   5,   -6), S(   9,  -12), S( -14,    7), S(  11,   -3), S(  13,  -15), S(  52,  -20), S( -14,  -21),
  S( -20,  -10), S(  20,   12), S(  13,   16), S(   0,    9), S(   3,   39), S(  25,    5), S(  16,  -11), S(  10,   -3),
  S(  -9,  -10), S( -19,   17), S(  13,   21), S(  21,   40), S(  30,   16), S(  16,   12), S(   6,   -3), S(  -3,  -21),
  S( -14,   -1), S(  -5,   15), S(  -2,   29), S(  49,   31), S(  26,   31), S(  24,   12), S(  11,    8), S(   1,   -8),
  S( -14,   -4), S(   0,   17), S(  -1,   19), S(  26,    6), S(  51,   17), S(  42,   34), S(  45,   12), S(  15,   -7),
  S( -34,   -2), S( -27,    1), S(  -8,    0), S( -14,   -5), S( -25,   -1), S(   9,   -1), S( -16,  -12), S( -34,  -26),
  S( -18,    0), S( -13,   -5), S( -28,  -13), S( -16,   -8), S( -15,    0), S( -56,  -18), S( -12,   -9), S(  -8,  -10),
};
inline const std::array rook_psqt = {
  S( -27,  -13), S( -14,  -21), S(  -1,  -13), S(  15,  -24), S(  34,  -40), S(  23,  -35), S( -19,   -1), S(  -7,  -62),
  S( -67,   -6), S( -43,  -11), S( -31,    1), S( -19,  -17), S( -22,  -26), S(   6,  -37), S(   4,  -38), S( -80,  -39),
  S( -51,    4), S( -41,    4), S( -35,   12), S( -24,   -8), S( -11,  -15), S(   0,  -22), S(  19,  -25), S( -14,  -34),
  S( -47,   15), S( -43,    9), S( -26,    9), S(   0,   -7), S( -15,  -15), S(  -1,  -12), S(  -9,   -9), S( -21,  -29),
  S( -41,   31), S( -30,   21), S(  -4,   17), S(  10,    7), S(  14,  -13), S(  37,   -6), S(  11,   -1), S(   1,   -4),
  S( -17,   32), S(   9,   17), S(   7,   23), S(  26,    7), S(  47,   -1), S(  58,    2), S(  24,   19), S(   8,    3),
  S( -18,   40), S( -15,   45), S(  26,   29), S(  47,   20), S(  36,   17), S(  65,   16), S(  30,   33), S(  55,   13),
  S(   8,   13), S(  11,   15), S(  22,   19), S(  33,   18), S(  35,   13), S(  17,   21), S(  19,   26), S(  40,   14),
};
inline const std::array queen_psqt = {
  S( -28,  -27), S( -28,  -32), S( -13,  -29), S(  11,  -31), S( -18,  -38), S( -69,  -63), S( -45,  -46), S( -47,  -37),
  S( -38,  -29), S( -27,  -16), S(  -8,  -11), S(   0,   -9), S(   8,   -4), S(   8,  -38), S(  -6,  -34), S( -25,  -28),
  S( -42,  -23), S( -13,   -4), S(  -9,    6), S(  -9,    6), S(  -2,   39), S(  13,    5), S(  20,    1), S( -11,  -16),
  S( -25,   -2), S( -33,   -3), S( -12,   19), S(  -1,   41), S(  13,   26), S(  11,   20), S(  20,   11), S(  -1,    5),
  S( -26,    1), S( -13,   32), S(  -9,   20), S(   2,   54), S(  27,   49), S(  36,   14), S(  30,   37), S(  30,  -24),
  S( -21,   -8), S(  -8,    5), S(   8,   23), S(   8,   28), S(  42,   35), S(  58,   26), S(  58,   23), S(  30,   -4),
  S( -26,  -17), S( -37,   11), S(  -5,   28), S(  -3,   32), S(   8,   16), S(  58,   15), S(  47,   18), S(  74,   -2),
  S( -24,  -38), S( -13,  -16), S(   3,   -6), S(   0,   -9), S(  15,   -4), S(  22,    7), S(  17,   -2), S(  25,    0),
};
inline const std::array king_psqt = {
  S( -29,  -42), S(  18,  -57), S(  42,  -42), S( -58,  -56), S(  40,  -85), S(   0,  -59), S( 121,  -93), S(  82, -115),
  S(  -5,  -36), S(   5,  -29), S(   2,  -11), S( -33,    0), S( -22,    6), S(  34,   -9), S(  88,  -38), S(  86,  -62),
  S( -21,  -46), S(  -1,  -25), S( -20,   -1), S( -28,   17), S( -42,   19), S( -22,   13), S(  11,  -16), S( -46,  -28),
  S( -19,  -21), S( -27,   -5), S( -22,   13), S( -20,   21), S( -19,   25), S( -38,   24), S( -36,    0), S( -55,  -35),
  S( -13,   -4), S(  -1,   27), S(  -1,   38), S(  -3,   40), S(  -7,   49), S(   2,   58), S(  -9,   37), S( -24,   -7),
  S(   0,   15), S(   3,   31), S(   6,   51), S(   7,   49), S(   9,   55), S(  14,   79), S(  11,   58), S(  -1,   23),
  S(   0,   -3), S(   4,   20), S(   5,   25), S(   7,   21), S(   8,   28), S(  10,   44), S(   3,   28), S(   0,    4),
  S(  -1,   -9), S(   0,   -7), S(   1,    6), S(   0,    1), S(   1,    5), S(   2,    3), S(   0,    1), S(   0,    0),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
