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
inline const pair pawn_material = S(131, 251);
inline const pair knight_material = S(558, 664);
inline const pair bishop_material = S(577, 740);
inline const pair rook_material = S(782, 1230);
inline const pair queen_material = S(1674, 1963);

inline const pair bishop_pair = S(116, 145);

inline const std::array knight_mobility = {
  S(-48, -76), S(-13, -39), S(0, -20), S(5, 0), S(7, 17), S(10, 29), S(11, 31), S(12, 33), S(14, 24),
};
inline const std::array bishop_mobility = {
  S(-63, -87), S(-36, -49), S(-15, -24), S(-1, -14), S(3, 0), S(8, 14), S(11, 23), S(12, 23), S(21, 28), S(19, 34), S(26, 16), S(23, 19), S(-8, -6), S(0, 21),
};
inline const std::array rook_mobility = {
  S(-77, -76), S(-54, -45), S(-42, -23), S(-29, -9), S(-30, -2), S(-12, 2), S(-8, 6), S(5, 8), S(17, 13), S(27, 21), S(31, 21), S(34, 26), S(45, 30), S(54, 7), S(39, 19),
};
inline const std::array queen_mobility = {
  S(-25, -65), S(-27, -65), S(-20, -80), S(-12, -75), S(-8, -62), S(0, -50), S(0, -35), S(6, -14), S(7, 7), S(7, 22), S(8, 33), S(9, 49), S(14, 50), S(12, 59), S(14, 59), S(8, 73), S(19, 62), S(22, 59), S(27, 55), S(35, 42), S(35, 33), S(29, 33), S(11, 8), S(-4, -2), S(-28, -34), S(-37, -42), S(-52, -61), S(-53, -62),
};

inline const pair pawn_threat_knight = S(82, 41);
inline const pair pawn_threat_bishop = S(88, 53);
inline const pair pawn_threat_rook = S(62, 46);
inline const pair pawn_threat_queen = S(49, 5);

inline const pair knight_threat_pawn = S(-15, 17);
inline const pair knight_threat_bishop = S(54, 48);
inline const pair knight_threat_rook = S(105, 10);
inline const pair knight_threat_queen = S(45, -9);

inline const pair bishop_threat_pawn = S(-4, 10);
inline const pair bishop_threat_knight = S(32, 26);
inline const pair bishop_threat_rook = S(82, 39);
inline const pair bishop_threat_queen = S(78, 26);

inline const std::array passed_pawn = {
  S(-33, -108), S(-40, -98), S(-47, -6), S(-9, 75), S(52, 147), S(143, 295),
};
inline const std::array defended_passed_pawn = {
  S(12, -8), S(15, 26), S(28, 33), S(15, 73), S(49, 106), S(69, 200),
};
inline const std::array blocked_passed_pawn = {
  S(-1, -11), S(10, -2), S(-11, -15), S(-18, -32), S(-20, -63), S(-45, -169),
};
inline const std::array friendly_passer_tropism = {
  S(9, 70), S(0, 68), S(8, 46), S(5, 29), S(11, 30), S(23, 30), S(6, 27),
};
inline const std::array enemy_passer_tropism = {
  S(-52, -50), S(8, 32), S(21, 52), S(30, 62), S(26, 67), S(23, 64), S(6, 76),
};

inline const pair isolated_pawn = S(-6, -10);
inline const std::array defended_pawn = {
  S(20, 20), S(27, 16), S(26, 34), S(90, 82), S(70, 120),
};
inline const std::array phalanx = {
  S(11, -15), S(18, 10), S(28, 36), S(78, 90), S(52, 94), S(9, 31),
};

inline const std::array shelter_centre = {
  S(-19, -9), S(23, -4), S(6, 6), S(-7, 10), S(-6, -2), S(2, 5), S(0, -4), S(0, 0),
};
inline const std::array shelter_mid = {
  S(-31, -24), S(50, -17), S(-1, -2), S(-29, 5), S(0, 10), S(5, 10), S(6, 17), S(0, 0),
};
inline const std::array shelter_edge = {
  S(-19, -15), S(39, -15), S(0, 6), S(-22, 7), S(-1, 8), S(2, 8), S(1, -1), S(0, 0),
};

inline const std::array king_ring = {
  S(-37, 11), S(-31, 16), S(-31, 0), S(-28, 9), S(-6, -85),
};

inline const std::array pawn_psqt = {
  S( -59,   -4), S( -22,   -2), S( -41,  -12), S( -40,  -18), S( -38,    1), S(  12,  -28), S(  60,  -63), S( -42,  -64),
  S( -56,  -29), S( -39,  -24), S( -25,  -51), S( -38,  -39), S( -36,  -35), S( -64,  -40), S(  19,  -84), S( -40,  -74),
  S( -64,  -13), S( -49,  -25), S( -18,  -50), S(  -7,  -68), S( -20,  -67), S( -30,  -56), S( -22,  -54), S( -54,  -62),
  S( -49,    6), S(   9,  -10), S( -11,  -29), S(  13,  -58), S(  15,  -63), S(   0,  -56), S(  13,  -35), S( -41,  -41),
  S( -13,   73), S(  20,   65), S(  54,   30), S(  79,   -3), S(  64,   -3), S(  59,   -3), S(  21,   53), S(  -8,   39),
  S( 105,  161), S( 108,  162), S(  95,  141), S(  94,  122), S(  76,   96), S(  20,   79), S(  -6,  122), S(   0,  123),
};
inline const std::array knight_psqt = {
  S( -40,  -26), S( -53,  -42), S( -42,  -27), S( -30,  -22), S( -33,  -18), S(   0,  -29), S( -37,  -29), S( -28,  -36),
  S( -48,  -31), S( -40,  -25), S( -35,  -11), S(  -8,    9), S(  13,    4), S(   7,  -20), S( -15,  -17), S( -15,  -27),
  S( -62,  -18), S( -22,    4), S(  -6,   14), S(  17,   37), S(  27,   22), S(  34,    7), S(  41,  -10), S( -31,  -24),
  S( -32,   -1), S(   0,   11), S(  22,   37), S(  36,   40), S(  50,   45), S(  55,   19), S(  40,   13), S(  10,  -17),
  S(  -2,   13), S(  19,   19), S(  29,   44), S(  79,   51), S(  38,   57), S( 112,   27), S(  30,   29), S(  57,    0),
  S( -24,  -15), S(  -2,   15), S(  41,   34), S(  67,   32), S(  68,   28), S(  65,   47), S(  24,   17), S(   5,   -1),
  S( -68,  -20), S( -40,   -4), S(   3,   -2), S(  29,   20), S(  15,    5), S(  24,    3), S( -33,  -20), S(  -8,  -27),
  S(-144,  -68), S( -24,  -19), S( -42,  -16), S(  -6,    2), S(   0,  -10), S( -51,  -25), S(  -8,   -9), S( -24,  -39),
};
inline const std::array bishop_psqt = {
  S( -13,  -38), S( -12,  -34), S( -10,  -22), S( -17,  -15), S( -17,  -32), S( -31,    3), S( -12,  -24), S(  -1,   -9),
  S(   9,  -23), S(   8,   -8), S(  11,  -11), S( -16,    7), S(  12,   -2), S(  18,  -19), S(  53,  -21), S(  -4,  -19),
  S( -15,   -9), S(  22,   11), S(  16,   21), S(   4,   11), S(   5,   46), S(  29,   10), S(  20,   -9), S(   8,   -4),
  S( -15,  -11), S( -19,   22), S(  13,   24), S(  26,   50), S(  37,   20), S(  10,   19), S(   7,    0), S(  -7,  -20),
  S( -19,    1), S( -13,   17), S(  -1,   27), S(  58,   31), S(  24,   36), S(  15,   12), S(   2,   10), S(  -6,  -13),
  S( -20,  -15), S(   0,   20), S(   0,   18), S(  29,    5), S(  53,   18), S(  53,   38), S(  44,   22), S(  15,  -13),
  S( -37,   -4), S( -30,    6), S(  -8,   -1), S( -21,  -10), S( -26,    0), S(   0,    0), S( -20,   -6), S( -37,  -26),
  S( -14,   -8), S( -17,   -3), S( -33,  -17), S( -19,  -13), S( -18,   -2), S( -54,  -12), S( -12,  -15), S(   0,   -7),
};
inline const std::array rook_psqt = {
  S( -29,  -31), S( -21,  -30), S(  -2,  -22), S(   7,  -33), S(  29,  -52), S(  19,  -48), S( -26,  -15), S( -17,  -70),
  S( -72,  -18), S( -45,  -22), S( -35,  -11), S( -23,  -30), S( -21,  -37), S(   4,  -47), S(   1,  -46), S( -89,  -48),
  S( -56,    1), S( -44,   -4), S( -34,    7), S( -29,  -17), S( -21,  -23), S(  -8,  -28), S(  18,  -32), S( -18,  -38),
  S( -48,   11), S( -45,   11), S( -24,    8), S(  -2,   -7), S( -15,  -17), S( -12,  -12), S( -11,  -12), S( -25,  -32),
  S( -40,   36), S( -28,   30), S(  -1,   24), S(  11,   16), S(  13,   -6), S(  29,    5), S(   9,   -8), S(   0,    1),
  S( -19,   47), S(  14,   33), S(  10,   33), S(  34,   20), S(  59,    7), S(  61,   18), S(  33,   23), S(   9,    2),
  S(  -6,   54), S(  -5,   59), S(  38,   48), S(  58,   40), S(  48,   32), S(  78,   21), S(  31,   38), S(  61,   23),
  S(  18,   11), S(  20,   16), S(  18,   21), S(  33,   21), S(  35,    8), S(  12,   23), S(  23,   24), S(  40,   16),
};
inline const std::array queen_psqt = {
  S( -30,  -29), S( -25,  -34), S( -10,  -37), S(  13,  -41), S( -21,  -43), S( -65,  -63), S( -40,  -41), S( -41,  -36),
  S( -40,  -31), S( -22,  -11), S(  -8,  -15), S(  -1,  -12), S(  10,  -14), S(   3,  -36), S(  -2,  -41), S( -31,  -31),
  S( -34,  -27), S( -11,   -5), S( -13,   12), S( -10,    8), S(  -4,   41), S(  13,    9), S(  21,    0), S(  -8,  -16),
  S( -27,    1), S( -34,    0), S( -11,   18), S(  -5,   55), S(  10,   35), S(   2,   31), S(  18,   11), S(  -7,   -1),
  S( -22,    2), S( -21,   40), S(  -5,   25), S(   0,   62), S(  25,   56), S(  31,   25), S(  21,   44), S(  20,  -20),
  S( -17,   -6), S(  -5,   14), S(  10,   26), S(  10,   35), S(  42,   29), S(  65,   31), S(  66,   22), S(  32,   -9),
  S( -24,  -19), S( -29,   19), S(   0,   27), S(   2,   30), S(   5,   16), S(  54,   15), S(  47,   16), S(  81,    1),
  S( -26,  -46), S(  -8,  -21), S(   3,  -16), S(  -2,  -16), S(   6,  -12), S(  20,    3), S(  11,  -15), S(  22,  -16),
};
inline const std::array king_psqt = {
  S( -29,  -48), S(  23,  -66), S(  41,  -44), S( -62,  -59), S(  35,  -91), S(  -3,  -61), S( 130,  -94), S(  86, -118),
  S(  -2,  -40), S(   1,  -31), S(  -2,   -8), S( -40,    2), S( -29,    4), S(  36,  -11), S(  90,  -40), S(  86,  -67),
  S( -25,  -52), S(   1,  -15), S( -24,    0), S( -36,   20), S( -49,   23), S( -19,   11), S(  17,  -14), S( -41,  -31),
  S( -19,  -23), S( -18,   -6), S( -27,   21), S( -21,   25), S( -20,   29), S( -36,   27), S( -34,   -1), S( -54,  -33),
  S( -11,   -5), S(   0,   34), S(   1,   39), S(  -1,   41), S(  -3,   51), S(   0,   62), S(  -4,   43), S( -26,  -12),
  S(   0,   12), S(   1,   32), S(   7,   56), S(   8,   48), S(  10,   58), S(  11,   81), S(  10,   61), S(   0,   21),
  S(  -1,   -7), S(   4,   16), S(   7,   34), S(   6,   24), S(   7,   24), S(   9,   40), S(   3,   31), S(   0,    0),
  S(   0,   -6), S(   1,   -1), S(   1,    6), S(   0,    0), S(   0,    1), S(   2,    6), S(   0,    3), S(   0,   -3),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
