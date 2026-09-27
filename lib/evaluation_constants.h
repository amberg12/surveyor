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
inline const pair pawn_material = S(134, 253);
inline const pair knight_material = S(573, 658);
inline const pair bishop_material = S(588, 735);
inline const pair rook_material = S(796, 1218);
inline const pair queen_material = S(1680, 2053);

inline const pair bishop_pair = S(120, 142);

inline const std::array knight_mobility = {
  S(-48, -75), S(-16, -38), S(-1, -19), S(3, 3), S(9, 16), S(14, 26), S(10, 32), S(10, 31), S(18, 22),
};
inline const std::array bishop_mobility = {
  S(-70, -92), S(-37, -51), S(-20, -26), S(-11, -12), S(0, 0), S(5, 13), S(12, 25), S(15, 23), S(21, 28), S(20, 32), S(35, 16), S(31, 21), S(-5, -3), S(2, 25),
};
inline const std::array rook_mobility = {
  S(-86, -76), S(-61, -45), S(-47, -24), S(-34, -10), S(-32, -3), S(-17, 2), S(-7, 7), S(5, 9), S(14, 18), S(28, 19), S(36, 22), S(37, 25), S(51, 30), S(64, 6), S(50, 19),
};
inline const std::array queen_mobility = {
  S(-33, -68), S(-37, -69), S(-31, -86), S(-18, -84), S(-13, -73), S(-7, -61), S(-3, -49), S(0, -31), S(4, -7), S(-2, 7), S(8, 22), S(8, 41), S(10, 44), S(11, 57), S(15, 61), S(11, 76), S(18, 68), S(23, 66), S(32, 65), S(41, 56), S(43, 48), S(39, 55), S(22, 25), S(8, 16), S(-19, -23), S(-31, -34), S(-50, -61), S(-51, -61),
};

inline const pair pawn_threat_knight = S(80, 41);
inline const pair pawn_threat_bishop = S(89, 53);
inline const pair pawn_threat_rook = S(62, 47);
inline const pair pawn_threat_queen = S(51, 8);

inline const pair knight_threat_pawn = S(-12, 15);
inline const pair knight_threat_bishop = S(55, 45);
inline const pair knight_threat_rook = S(109, 9);
inline const pair knight_threat_queen = S(46, -12);

inline const pair bishop_threat_pawn = S(-7, 7);
inline const pair bishop_threat_knight = S(30, 25);
inline const pair bishop_threat_rook = S(86, 39);
inline const pair bishop_threat_queen = S(79, 24);

inline const std::array passed_pawn = {
  S(-24, -108), S(-34, -102), S(-42, -8), S(-7, 76), S(44, 146), S(135, 293),
};
inline const std::array defended_passed_pawn = {
  S(10, -6), S(14, 28), S(27, 34), S(13, 77), S(46, 106), S(64, 196),
};
inline const std::array blocked_passed_pawn = {
  S(0, -13), S(10, -3), S(-7, -14), S(-17, -33), S(-17, -63), S(-45, -168),
};
inline const std::array friendly_passer_tropism = {
  S(9, 70), S(0, 65), S(10, 42), S(5, 29), S(13, 32), S(23, 31), S(9, 23),
};
inline const std::array enemy_passer_tropism = {
  S(-31, -62), S(37, 23), S(19, 53), S(26, 64), S(17, 68), S(12, 71), S(-10, 78),
};

inline const pair isolated_pawn = S(-9, -4);
inline const std::array defended_pawn = {
  S(18, 20), S(25, 16), S(28, 34), S(90, 82), S(69, 119),
};
inline const std::array phalanx = {
  S(10, -14), S(17, 8), S(28, 36), S(76, 90), S(51, 94), S(9, 31),
};

inline const std::array shelter_centre = {
  S(-19, -6), S(22, -3), S(7, 5), S(-7, 7), S(-5, -2), S(2, 5), S(0, -4), S(0, 0),
};
inline const std::array shelter_mid = {
  S(-35, -21), S(52, -16), S(2, -2), S(-29, 3), S(0, 10), S(4, 8), S(6, 16), S(0, 0),
};
inline const std::array shelter_edge = {
  S(-27, -10), S(45, -18), S(2, 7), S(-22, 5), S(-1, 7), S(2, 8), S(1, -1), S(0, 0),
};

inline const std::array pawn_psqt = {
  S( -61,   -2), S( -21,   -4), S( -42,  -12), S( -42,  -18), S( -38,    3), S(  10,  -24), S(  57,  -62), S( -51,  -61),
  S( -57,  -29), S( -40,  -27), S( -27,  -49), S( -39,  -36), S( -36,  -35), S( -65,  -42), S(  17,  -82), S( -42,  -71),
  S( -64,  -11), S( -50,  -23), S( -21,  -48), S(  -9,  -66), S( -22,  -68), S( -32,  -59), S( -24,  -53), S( -62,  -61),
  S( -49,    8), S(   1,   -7), S( -15,  -28), S(   9,  -59), S(  13,  -61), S(  -8,  -57), S(   9,  -38), S( -42,  -39),
  S( -14,   72), S(  19,   66), S(  59,   28), S(  83,   -2), S(  78,   -9), S(  69,   -8), S(  45,   48), S(   5,   33),
  S( 105,  163), S( 106,  162), S(  93,  141), S(  91,  122), S(  76,   93), S(  23,   79), S(   5,  121), S(   1,  123),
};
inline const std::array knight_psqt = {
  S( -43,  -27), S( -61,  -40), S( -44,  -25), S( -34,  -21), S( -38,  -17), S(  -6,  -29), S( -42,  -27), S( -32,  -37),
  S( -53,  -31), S( -43,  -25), S( -40,   -9), S( -17,   13), S(   7,    6), S(   2,  -18), S( -18,  -17), S( -19,  -27),
  S( -71,  -17), S( -31,    6), S( -10,   20), S(  10,   40), S(  23,   27), S(  31,   12), S(  38,   -7), S( -37,  -23),
  S( -40,    0), S(  -7,   12), S(  13,   40), S(  29,   44), S(  42,   50), S(  48,   21), S(  39,   12), S(   6,  -15),
  S( -10,   13), S(  11,   22), S(  22,   47), S(  80,   52), S(  63,   48), S( 127,   21), S(  65,   16), S(  70,   -3),
  S( -28,  -15), S(  -5,   17), S(  39,   37), S(  78,   29), S(  92,   23), S(  83,   44), S(  55,   10), S(  16,   -2),
  S( -72,  -20), S( -44,   -4), S(   1,   -2), S(  34,   17), S(  23,    3), S(  35,    1), S( -33,  -21), S(  -1,  -28),
  S(-147,  -68), S( -25,  -19), S( -43,  -17), S(  -6,    1), S(   1,  -12), S( -51,  -27), S(  -8,  -10), S( -21,  -39),
};
inline const std::array bishop_psqt = {
  S( -16,  -38), S( -12,  -33), S( -16,  -20), S( -19,  -16), S( -20,  -32), S( -35,    0), S( -13,  -24), S(  -7,  -10),
  S(   8,  -23), S(   0,  -10), S(   9,  -11), S( -23,    7), S(   7,   -5), S(  15,  -20), S(  54,  -20), S(  -6,  -20),
  S( -14,  -11), S(  19,   10), S(  13,   21), S(   1,   11), S(   1,   45), S(  23,    8), S(  17,  -10), S(   5,   -6),
  S( -19,  -12), S( -16,   22), S(  17,   24), S(  25,   51), S(  39,   20), S(   5,   21), S(   2,   -1), S(  -6,  -19),
  S( -23,    1), S( -15,   16), S(   4,   26), S(  68,   31), S(  31,   41), S(  21,   14), S(   2,    9), S(   5,  -13),
  S( -25,  -15), S(  -3,   20), S(  -3,   16), S(  38,    3), S(  62,   19), S(  66,   41), S(  59,   22), S(  35,  -12),
  S( -41,   -6), S( -39,    5), S( -14,   -3), S( -27,   -9), S( -24,    0), S(   5,    2), S( -14,   -5), S( -31,  -25),
  S( -17,  -10), S( -20,   -4), S( -35,  -17), S( -20,  -11), S( -16,    0), S( -53,  -11), S( -10,  -14), S(  -3,   -7),
};
inline const std::array rook_psqt = {
  S( -38,  -32), S( -29,  -34), S(  -8,  -21), S(   6,  -33), S(  25,  -51), S(  16,  -49), S( -29,  -18), S( -18,  -73),
  S( -77,  -18), S( -54,  -24), S( -42,  -12), S( -28,  -29), S( -27,  -38), S(   5,  -45), S(   3,  -47), S( -92,  -48),
  S( -63,    1), S( -52,   -3), S( -42,    5), S( -35,  -19), S( -24,  -24), S(  -3,  -26), S(  24,  -32), S( -18,  -40),
  S( -56,   13), S( -54,   11), S( -31,    9), S(  -9,   -8), S( -21,  -16), S(  -3,  -12), S(  -5,  -13), S( -25,  -32),
  S( -49,   38), S( -39,   29), S(  -9,   26), S(   6,   17), S(   5,   -6), S(  32,    4), S(  18,   -6), S(   4,    1),
  S( -27,   48), S(   7,   36), S(   4,   36), S(  30,   23), S(  56,    8), S(  71,   19), S(  44,   25), S(  21,    2),
  S(  -4,   56), S(   0,   56), S(  47,   47), S(  68,   40), S(  61,   33), S(  92,   20), S(  45,   37), S(  75,   22),
  S(  21,   12), S(  23,   17), S(  25,   22), S(  39,   21), S(  42,    9), S(  16,   23), S(  29,   24), S(  50,   15),
};
inline const std::array queen_psqt = {
  S( -42,  -40), S( -38,  -49), S( -23,  -64), S(   5,  -88), S( -34,  -69), S( -77,  -76), S( -47,  -48), S( -50,  -44),
  S( -53,  -45), S( -37,  -27), S( -19,  -45), S( -12,  -55), S(   0,  -61), S(  -4,  -50), S( -12,  -50), S( -38,  -36),
  S( -43,  -40), S( -24,  -30), S( -26,   -8), S( -18,  -16), S( -15,    7), S(   8,   -4), S(  15,   -2), S( -14,  -21),
  S( -39,  -29), S( -42,  -17), S( -21,   -1), S( -17,   50), S(   1,   26), S(  -9,   40), S(  11,   19), S( -10,   14),
  S( -39,  -26), S( -36,   10), S(  -6,   12), S(  -1,   57), S(  24,   80), S(  39,   58), S(  18,   73), S(  27,   28),
  S( -35,  -25), S( -23,   -3), S(  -5,    8), S(  13,   40), S(  57,   58), S( 112,   83), S(  97,   65), S(  70,   42),
  S( -31,  -20), S( -36,   19), S(   3,   29), S(   8,   40), S(  35,   49), S(  83,   54), S(  66,   34), S(  92,   22),
  S( -24,  -32), S(   2,   -6), S(  21,    3), S(  23,   19), S(  45,   32), S(  54,   38), S(  36,    7), S(  42,   13),
};
inline const std::array king_psqt = {
  S( -14,  -43), S(  51,  -66), S(  76,  -52), S( -37,  -61), S(  70,  -98), S(  21,  -71), S( 166, -104), S( 131, -118),
  S(   8,  -39), S(   4,  -33), S(   0,  -10), S( -44,   -1), S( -39,    4), S(  32,  -14), S(  84,  -37), S( 111,  -67),
  S( -23,  -52), S(  -7,  -16), S( -44,    1), S( -66,   23), S( -80,   29), S( -60,   19), S( -14,  -10), S( -39,  -32),
  S( -19,  -22), S( -24,   -7), S( -39,   22), S( -31,   26), S( -34,   32), S( -57,   31), S( -53,    1), S( -53,  -30),
  S( -10,   -5), S(  -2,   34), S(  -1,   39), S(  -3,   40), S(  -8,   52), S(  -6,   64), S( -10,   45), S( -25,  -12),
  S(   0,   12), S(   1,   32), S(   7,   56), S(   7,   48), S(   9,   57), S(  10,   80), S(  10,   62), S(   0,   21),
  S(   0,   -6), S(   4,   16), S(   8,   33), S(   5,   23), S(   6,   22), S(   8,   40), S(   2,   29), S(   0,    0),
  S(   0,   -6), S(   2,   -1), S(   2,    7), S(   0,    1), S(   1,    1), S(   2,    6), S(   0,    3), S(   0,   -3),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
