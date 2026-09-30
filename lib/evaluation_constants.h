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
inline const pair pawn_material = S(133, 255);
inline const pair knight_material = S(559, 666);
inline const pair bishop_material = S(573, 742);
inline const pair rook_material = S(778, 1228);
inline const pair queen_material = S(1671, 1963);

inline const pair bishop_pair = S(116, 145);

inline const std::array knight_mobility = {
  S(-51, -76), S(-14, -38), S(0, -18), S(5, 0), S(10, 14), S(10, 25), S(10, 32), S(11, 36), S(16, 24),
};
inline const std::array bishop_mobility = {
  S(-64, -88), S(-33, -50), S(-16, -24), S(0, -14), S(2, 0), S(6, 16), S(13, 24), S(11, 22), S(17, 28), S(18, 33), S(28, 17), S(25, 20), S(-8, -6), S(0, 21),
};
inline const std::array rook_mobility = {
  S(-74, -76), S(-55, -44), S(-44, -25), S(-30, -9), S(-31, -3), S(-11, 1), S(-6, 7), S(3, 8), S(16, 14), S(27, 19), S(34, 24), S(33, 28), S(44, 29), S(54, 6), S(40, 18),
};
inline const std::array queen_mobility = {
  S(-34, -65), S(-28, -65), S(-21, -80), S(-12, -74), S(-5, -60), S(0, -50), S(3, -35), S(5, -13), S(8, 7), S(7, 22), S(9, 33), S(11, 48), S(14, 49), S(12, 58), S(17, 60), S(7, 71), S(18, 62), S(22, 59), S(27, 54), S(35, 42), S(35, 33), S(28, 34), S(11, 9), S(-4, -2), S(-28, -34), S(-37, -41), S(-52, -61), S(-53, -62),
};

inline const pair pawn_threat_knight = S(80, 39);
inline const pair pawn_threat_bishop = S(90, 54);
inline const pair pawn_threat_rook = S(62, 46);
inline const pair pawn_threat_queen = S(48, 5);

inline const pair knight_threat_pawn = S(-19, 16);
inline const pair knight_threat_bishop = S(54, 47);
inline const pair knight_threat_rook = S(107, 11);
inline const pair knight_threat_queen = S(46, -9);

inline const pair bishop_threat_pawn = S(-8, 8);
inline const pair bishop_threat_knight = S(30, 26);
inline const pair bishop_threat_rook = S(83, 40);
inline const pair bishop_threat_queen = S(78, 26);

inline const std::array passed_pawn = {
  S(-26, -108), S(-43, -92), S(-47, -3), S(-10, 78), S(55, 144), S(145, 283),
};
inline const std::array defended_passed_pawn = {
  S(8, -6), S(15, 28), S(29, 35), S(15, 74), S(51, 100), S(68, 190),
};
inline const std::array blocked_passed_pawn = {
  S(-3, -17), S(8, -5), S(-8, -15), S(-18, -32), S(-20, -62), S(-42, -165),
};
inline const std::array friendly_passer_tropism = {
  S(6, 69), S(6, 68), S(9, 42), S(4, 30), S(15, 32), S(24, 33), S(5, 24),
};
inline const std::array enemy_passer_tropism = {
  S(-43, -37), S(6, 32), S(21, 49), S(30, 57), S(30, 64), S(22, 64), S(5, 69),
};

inline const pair isolated_pawn = S(-8, -6);
inline const std::array defended_pawn = {
  S(20, 16), S(31, 18), S(30, 34), S(88, 84), S(69, 122),
};
inline const std::array phalanx = {
  S(8, -11), S(21, 7), S(31, 37), S(81, 90), S(52, 96), S(9, 30),
};

inline const std::array shelter_centre = {
  S(-33, -18), S(26, -20), S(-1, -12), S(0, -18), S(-11, 0), S(2, 11), S(17, 57),
};
inline const std::array shelter_mid = {
  S(-66, -21), S(36, -23), S(22, -21), S(17, -19), S(0, -7), S(-19, 20), S(9, 74),
};
inline const std::array shelter_edge = {
  S(-43, -21), S(26, -34), S(27, -24), S(11, -19), S(-12, -2), S(-19, 30), S(9, 71),
};

inline const std::array storm_centre = {
  S(11, -17), S(-3, 45), S(-35, 44), S(-7, -4), S(5, -16), S(16, -24), S(12, -26),
};
inline const std::array storm_mid = {
  S(-27, -16), S(48, 43), S(-16, 23), S(0, -1), S(-1, -10), S(1, -18), S(-4, -20),
};
inline const std::array storm_edge = {
  S(-15, -21), S(50, 71), S(-22, 29), S(-14, 1), S(-5, -18), S(8, -30), S(0, -31),
};

inline const std::array king_ring = {
  S(-38, 10), S(-31, 13), S(-25, 0), S(-30, 6), S(-9, -86),
};

inline const std::array pawn_psqt = {
  S( -58,   -8), S( -22,   -6), S( -40,  -16), S( -48,  -18), S( -43,   -2), S(   9,  -30), S(  63,  -59), S( -37,  -61),
  S( -56,  -29), S( -42,  -24), S( -26,  -49), S( -41,  -42), S( -33,  -36), S( -62,  -43), S(  26,  -85), S( -39,  -77),
  S( -66,  -13), S( -51,  -24), S( -26,  -50), S(  -9,  -65), S( -16,  -70), S( -29,  -55), S( -15,  -53), S( -50,  -61),
  S( -49,    9), S(   2,   -9), S( -13,  -29), S(   7,  -60), S(  19,  -68), S(  -3,  -55), S(  27,  -37), S( -32,  -43),
  S( -17,   73), S(  18,   65), S(  52,   31), S(  72,    3), S(  59,    0), S(  42,   11), S(  28,   54), S(  -9,   38),
  S( 105,  165), S( 108,  163), S(  94,  141), S(  92,  122), S(  76,   94), S(  22,   80), S(   7,  118), S(   8,  118),
};
inline const std::array knight_psqt = {
  S( -40,  -26), S( -52,  -43), S( -41,  -26), S( -30,  -21), S( -33,  -17), S(  -2,  -29), S( -38,  -28), S( -29,  -37),
  S( -48,  -31), S( -40,  -25), S( -33,  -10), S(  -8,   11), S(  11,    2), S(   8,  -21), S( -14,  -17), S( -14,  -26),
  S( -65,  -18), S( -22,    5), S(  -9,   12), S(  15,   36), S(  27,   22), S(  35,    8), S(  39,   -9), S( -29,  -23),
  S( -32,    0), S(   0,   11), S(  21,   37), S(  35,   39), S(  49,   45), S(  54,   18), S(  42,   13), S(  10,  -15),
  S(  -4,   13), S(  17,   19), S(  28,   44), S(  82,   52), S(  39,   57), S( 115,   27), S(  29,   27), S(  55,   -1),
  S( -23,  -15), S(  -3,   15), S(  42,   35), S(  66,   31), S(  69,   27), S(  65,   46), S(  26,   16), S(   6,   -1),
  S( -68,  -20), S( -41,   -5), S(   3,   -1), S(  30,   20), S(  16,    4), S(  26,    3), S( -32,  -20), S(  -8,  -28),
  S(-144,  -68), S( -24,  -19), S( -42,  -15), S(  -6,    2), S(   0,  -10), S( -51,  -25), S(  -8,   -9), S( -24,  -39),
};
inline const std::array bishop_psqt = {
  S( -12,  -38), S( -13,  -33), S(  -9,  -20), S( -16,  -15), S( -17,  -31), S( -29,    0), S( -13,  -23), S(  -5,  -10),
  S(   8,  -23), S(   7,   -9), S(   9,  -10), S( -19,    7), S(  13,   -2), S(  18,  -19), S(  59,  -21), S(  -3,  -18),
  S( -18,  -10), S(  21,   11), S(  16,   21), S(   3,   11), S(   4,   45), S(  26,    9), S(  21,   -9), S(   5,   -6),
  S( -15,  -11), S( -20,   22), S(  15,   24), S(  23,   50), S(  37,   18), S(  13,   19), S(   7,    0), S(  -6,  -20),
  S( -20,    2), S( -11,   19), S(  -2,   28), S(  58,   32), S(  23,   36), S(  16,   13), S(   3,   10), S(  -6,  -12),
  S( -20,  -14), S(   1,   19), S(   0,   17), S(  29,    5), S(  53,   17), S(  53,   38), S(  44,   21), S(  13,  -12),
  S( -36,   -4), S( -30,    6), S(  -7,   -1), S( -20,  -10), S( -28,   -1), S(   2,    0), S( -20,   -6), S( -37,  -27),
  S( -13,   -9), S( -17,   -3), S( -33,  -17), S( -18,  -13), S( -19,   -2), S( -54,  -13), S( -11,  -15), S(   0,   -7),
};
inline const std::array rook_psqt = {
  S( -29,  -28), S( -20,  -31), S(  -5,  -18), S(   9,  -32), S(  27,  -51), S(  16,  -46), S( -25,  -17), S( -10,  -72),
  S( -73,  -17), S( -47,  -23), S( -36,  -10), S( -24,  -31), S( -22,  -36), S(   6,  -48), S(   0,  -47), S( -88,  -47),
  S( -58,    0), S( -44,   -3), S( -35,    6), S( -30,  -16), S( -21,  -23), S(  -9,  -27), S(  17,  -32), S( -16,  -38),
  S( -48,   11), S( -45,   11), S( -25,    9), S(  -2,   -6), S( -16,  -18), S(  -9,  -12), S( -10,  -13), S( -28,  -32),
  S( -39,   38), S( -29,   29), S(  -2,   25), S(  11,   16), S(  12,   -6), S(  27,    3), S(   9,   -7), S(  -4,    0),
  S( -19,   45), S(  15,   34), S(  10,   35), S(  35,   22), S(  59,    8), S(  62,   17), S(  33,   22), S(   8,    4),
  S(  -7,   53), S(  -4,   58), S(  37,   47), S(  59,   41), S(  49,   33), S(  81,   19), S(  33,   38), S(  61,   22),
  S(  18,   11), S(  20,   16), S(  19,   21), S(  34,   22), S(  35,    9), S(  13,   23), S(  23,   23), S(  40,   15),
};
inline const std::array queen_psqt = {
  S( -31,  -29), S( -25,  -34), S(  -9,  -37), S(  10,  -41), S( -19,  -43), S( -65,  -63), S( -42,  -42), S( -41,  -36),
  S( -40,  -31), S( -24,  -12), S(  -5,  -14), S(  -2,  -12), S(  10,  -14), S(   4,  -36), S(  -2,  -41), S( -31,  -31),
  S( -36,  -26), S( -14,   -5), S( -11,   12), S(  -8,    8), S(   0,   42), S(  13,    9), S(  19,    0), S(  -9,  -16),
  S( -27,    2), S( -34,    0), S( -10,   18), S(  -8,   53), S(  11,   35), S(   2,   30), S(  20,   12), S(  -5,    0),
  S( -23,    2), S( -21,   40), S(  -4,   26), S(  -1,   61), S(  25,   55), S(  32,   25), S(  20,   43), S(  22,  -19),
  S( -19,   -7), S(  -5,   16), S(   9,   25), S(  10,   35), S(  42,   29), S(  65,   31), S(  65,   22), S(  31,   -9),
  S( -25,  -19), S( -31,   19), S(   0,   27), S(   3,   30), S(   6,   16), S(  55,   14), S(  48,   17), S(  79,    1),
  S( -25,  -46), S(  -8,  -21), S(   3,  -16), S(  -2,  -17), S(   6,  -12), S(  21,    3), S(  12,  -15), S(  22,  -16),
};
inline const std::array king_psqt = {
  S( -31,  -51), S(  13,  -67), S(  40,  -46), S( -51,  -61), S(  44,  -95), S(  -6,  -65), S( 121,  -93), S(  82, -120),
  S(  -5,  -44), S(   0,  -34), S(   1,   -8), S( -34,   -1), S( -23,    3), S(  33,   -9), S(  88,  -40), S(  85,  -69),
  S( -24,  -51), S(  -1,  -16), S( -22,    2), S( -32,   21), S( -46,   24), S( -23,   14), S(  12,  -17), S( -43,  -29),
  S( -19,  -21), S( -18,   -8), S( -26,   22), S( -19,   26), S( -18,   31), S( -36,   32), S( -36,    0), S( -55,  -29),
  S( -11,   -3), S(   0,   33), S(   2,   40), S(   0,   42), S(  -2,   54), S(   0,   66), S(  -4,   46), S( -26,  -10),
  S(   0,   11), S(   1,   31), S(   8,   56), S(   8,   48), S(  11,   60), S(  12,   83), S(  10,   60), S(   0,   22),
  S(  -1,   -8), S(   4,   15), S(   7,   33), S(   6,   24), S(   7,   25), S(   9,   41), S(   3,   29), S(   0,    0),
  S(  -1,   -8), S(   1,   -2), S(   1,    5), S(   0,    0), S(   0,    1), S(   2,    5), S(   0,    2), S(   0,   -5),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
