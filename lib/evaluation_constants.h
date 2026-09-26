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
inline const pair pawn_material = S(136, 251);
inline const pair knight_material = S(577, 654);
inline const pair bishop_material = S(596, 731);
inline const pair rook_material = S(798, 1210);
inline const pair queen_material = S(1683, 2044);

inline const pair bishop_pair = S(124, 150);
inline const pair tempo = S(26, 13);

inline const std::array knight_mobility = {
  S(-47, -73), S(-10, -29), S(-6, -14), S(2, 9), S(8, 22), S(10, 29), S(14, 27), S(11, 23), S(16, 6),
};
inline const std::array bishop_mobility = {
  S(-70, -88), S(-36, -48), S(-16, -20), S(-6, -12), S(4, 1), S(7, 19), S(16, 27), S(17, 23), S(24, 27), S(19, 31), S(32, 13), S(24, 15), S(-10, -7), S(-5, 17),
};
inline const std::array rook_mobility = {
  S(-86, -76), S(-61, -45), S(-50, -25), S(-33, -10), S(-34, -1), S(-16, 7), S(-11, 5), S(7, 13), S(18, 13), S(28, 18), S(37, 19), S(39, 25), S(51, 28), S(62, 4), S(48, 20),
};
inline const std::array queen_mobility = {
  S(-35, -67), S(-35, -69), S(-30, -86), S(-18, -83), S(-11, -71), S(-8, -62), S(-3, -49), S(-2, -30), S(3, -5), S(3, 8), S(7, 21), S(11, 42), S(14, 46), S(11, 58), S(12, 61), S(10, 75), S(20, 70), S(26, 67), S(31, 65), S(39, 54), S(42, 47), S(38, 52), S(21, 24), S(6, 13), S(-20, -24), S(-32, -35), S(-50, -61), S(-51, -61),
};

inline const pair pawn_threat_knight = S(93, 52);
inline const pair pawn_threat_bishop = S(116, 57);
inline const pair pawn_threat_rook = S(73, 58);
inline const pair pawn_threat_queen = S(72, 13);

inline const std::array passed_pawn = {
  S(6, 7), S(-2, 8), S(-9, 87), S(22, 161), S(84, 220), S(166, 359),
};
inline const std::array defended_passed_pawn = {
  S(11, 2), S(11, 36), S(23, 47), S(8, 89), S(47, 122), S(69, 208),
};
inline const std::array blocked_passed_pawn = {
  S(-1, -10), S(12, -5), S(-4, -27), S(-12, -52), S(-16, -81), S(-45, -173),
};

inline const pair isolated_pawn = S(-3, -6);
inline const std::array defended_pawn = {
  S(18, 20), S(27, 15), S(31, 33), S(91, 75), S(68, 112),
};
inline const std::array phalanx = {
  S(12, -11), S(19, 7), S(30, 38), S(74, 89), S(51, 96), S(9, 32),
};

inline const std::array shelter_centre = {
  S(-21, -6), S(25, -2), S(7, 1), S(-8, 9), S(-6, -2), S(2, 3), S(0, -4), S(0, 0),
};
inline const std::array shelter_mid = {
  S(-37, -15), S(56, -21), S(1, -6), S(-32, 4), S(0, 11), S(5, 9), S(6, 17), S(0, 0),
};
inline const std::array shelter_edge = {
  S(-25, -11), S(47, -18), S(2, 2), S(-25, 8), S(-2, 10), S(2, 10), S(1, -1), S(0, 0),
};

inline const std::array pawn_psqt = {
  S( -61,  -12), S( -23,  -13), S( -45,  -17), S( -47,  -17), S( -43,    5), S(   7,  -22), S(  55,  -55), S( -48,  -57),
  S( -59,  -31), S( -43,  -32), S( -26,  -53), S( -39,  -40), S( -33,  -32), S( -66,  -40), S(  19,  -83), S( -45,  -70),
  S( -68,  -12), S( -50,  -25), S( -23,  -50), S( -12,  -69), S( -18,  -72), S( -33,  -59), S( -23,  -54), S( -61,  -59),
  S( -48,   11), S(   0,   -8), S( -17,  -32), S(  11,  -63), S(  16,  -68), S(  -9,  -60), S(   8,  -39), S( -44,  -41),
  S( -16,   82), S(  18,   74), S(  60,   31), S(  85,   -4), S(  85,  -17), S(  71,  -11), S(  47,   45), S(   5,   35),
  S( 110,  185), S( 111,  178), S(  99,  148), S(  97,  121), S(  79,   85), S(  19,   73), S(   3,  122), S(  -3,  129),
};
inline const std::array knight_psqt = {
  S( -45,  -31), S( -68,  -51), S( -46,  -31), S( -37,  -30), S( -37,  -22), S(  -9,  -35), S( -53,  -35), S( -35,  -41),
  S( -54,  -36), S( -45,  -30), S( -41,  -12), S( -23,    8), S(   3,    0), S(   0,  -21), S( -23,  -24), S( -20,  -34),
  S( -81,  -21), S( -30,    3), S( -22,   25), S(   8,   43), S(  18,   32), S(  24,   13), S(  33,   -9), S( -49,  -29),
  S( -44,   -6), S( -12,   14), S(   9,   49), S(  19,   56), S(  41,   56), S(  36,   35), S(  39,   12), S(   2,  -21),
  S(  -8,   11), S(   2,   26), S(  23,   60), S(  80,   62), S(  47,   66), S( 137,   30), S(  48,   25), S(  74,   -8),
  S( -25,  -17), S(  18,   17), S(  48,   46), S(  92,   40), S( 120,   30), S(  84,   52), S(  80,    5), S(  12,   -4),
  S( -65,  -25), S( -42,   -8), S(  26,   -3), S(  55,   19), S(  26,    4), S(  50,    0), S( -34,  -23), S(   4,  -31),
  S(-151,  -72), S( -26,  -21), S( -42,  -17), S(  -7,    1), S(   2,  -13), S( -53,  -28), S(  -9,  -11), S( -25,  -41),
};
inline const std::array bishop_psqt = {
  S( -18,  -39), S( -15,  -34), S( -22,  -24), S( -22,  -20), S( -24,  -34), S( -46,    0), S( -14,  -27), S( -12,  -11),
  S(   6,  -26), S(  -2,  -12), S(   5,  -10), S( -32,    9), S(  -3,   -8), S(   8,  -21), S(  43,  -23), S( -10,  -23),
  S( -12,  -13), S(  14,   12), S(   7,   25), S(  -4,   15), S( -11,   47), S(  19,   10), S(  13,  -10), S(   5,   -7),
  S( -18,  -14), S( -12,   21), S(  13,   28), S(  33,   54), S(  42,   24), S(   0,   23), S(   1,   -1), S(  -3,  -22),
  S( -22,    0), S(  -8,   15), S(   7,   29), S(  71,   34), S(  39,   43), S(  28,   16), S(  13,    7), S(   0,  -11),
  S( -26,  -15), S(  -2,   18), S(  12,   17), S(  46,    3), S(  66,   21), S(  75,   44), S(  59,   22), S(  40,  -13),
  S( -43,   -7), S( -21,    2), S(  -7,   -1), S( -23,   -8), S(  -9,    1), S(   6,    3), S(  -2,   -4), S( -37,  -24),
  S( -22,  -12), S( -22,   -6), S( -35,  -17), S( -20,  -10), S( -18,    0), S( -55,  -12), S( -12,  -14), S(  -4,   -7),
};
inline const std::array rook_psqt = {
  S( -38,  -30), S( -26,  -30), S( -11,  -22), S(   4,  -37), S(  24,  -55), S(  10,  -50), S( -23,  -19), S( -17,  -74),
  S( -77,  -20), S( -50,  -25), S( -40,  -13), S( -28,  -33), S( -26,  -39), S(   2,  -49), S(   4,  -51), S( -90,  -50),
  S( -66,    0), S( -51,   -3), S( -44,    5), S( -34,  -19), S( -25,  -26), S(  -6,  -27), S(  23,  -32), S( -16,  -42),
  S( -58,   12), S( -52,   12), S( -33,    9), S( -11,   -8), S( -24,  -15), S(  -6,  -12), S(  -6,  -12), S( -26,  -33),
  S( -48,   40), S( -38,   32), S( -10,   28), S(   2,   20), S(   3,   -6), S(  33,    5), S(  18,   -5), S(   5,    1),
  S( -26,   49), S(   8,   37), S(   4,   39), S(  32,   23), S(  56,    9), S(  71,   20), S(  44,   24), S(  19,    4),
  S(  -3,   55), S(   3,   58), S(  50,   48), S(  69,   43), S(  62,   33), S(  94,   21), S(  44,   37), S(  75,   23),
  S(  22,   13), S(  24,   18), S(  25,   22), S(  40,   21), S(  43,    9), S(  16,   23), S(  29,   23), S(  51,   16),
};
inline const std::array queen_psqt = {
  S( -44,  -40), S( -37,  -49), S( -24,  -64), S(   2,  -92), S( -37,  -70), S( -77,  -77), S( -48,  -48), S( -51,  -44),
  S( -52,  -45), S( -35,  -27), S( -15,  -46), S( -15,  -53), S(   1,  -63), S(  -3,  -50), S( -12,  -51), S( -38,  -35),
  S( -42,  -40), S( -23,  -31), S( -26,   -9), S( -21,  -16), S( -16,    6), S(   2,   -3), S(  13,   -3), S( -13,  -22),
  S( -41,  -29), S( -39,  -17), S( -20,    0), S( -17,   52), S(   0,   27), S(  -6,   42), S(  11,   19), S( -11,   13),
  S( -37,  -26), S( -36,   11), S(  -6,   13), S(  -2,   61), S(  22,   80), S(  39,   57), S(  19,   74), S(  30,   29),
  S( -35,  -25), S( -21,   -3), S(  -5,   11), S(  15,   42), S(  55,   59), S( 114,   85), S(  97,   66), S(  69,   42),
  S( -30,  -21), S( -32,   20), S(   6,   29), S(   9,   40), S(  38,   50), S(  85,   55), S(  67,   34), S(  93,   21),
  S( -26,  -34), S(   0,   -7), S(  19,    2), S(  21,   17), S(  43,   31), S(  53,   37), S(  35,    7), S(  39,   10),
};
inline const std::array king_psqt = {
  S( -15,  -49), S(  50,  -77), S(  72,  -59), S( -40,  -74), S(  63, -110), S(  20,  -85), S( 166, -118), S( 132, -140),
  S(   6,  -45), S(   3,  -43), S(  -2,  -17), S( -49,   -6), S( -45,    0), S(  29,  -23), S(  84,  -48), S( 114,  -84),
  S( -23,  -54), S(  -8,  -17), S( -46,    3), S( -68,   27), S( -83,   32), S( -65,   21), S( -16,  -14), S( -38,  -37),
  S( -19,  -22), S( -22,   -2), S( -37,   33), S( -29,   38), S( -33,   41), S( -56,   44), S( -51,   10), S( -53,  -28),
  S( -10,   -5), S(  -1,   41), S(   0,   50), S(   0,   50), S(  -4,   66), S(  -2,   79), S(  -7,   56), S( -23,  -10),
  S(   0,   13), S(   2,   37), S(   9,   61), S(  10,   55), S(  11,   65), S(  14,   92), S(  12,   69), S(   1,   24),
  S(   0,   -9), S(   4,   15), S(   8,   34), S(   6,   24), S(   7,   27), S(   9,   41), S(   4,   32), S(   0,   -2),
  S(   0,   -9), S(   2,   -2), S(   2,    5), S(   0,    0), S(   1,    0), S(   2,    5), S(   0,    3), S(   0,   -4),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
