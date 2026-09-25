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
inline const pair pawn_material = S(136, 250);
inline const pair knight_material = S(574, 656);
inline const pair bishop_material = S(592, 728);
inline const pair rook_material = S(789, 1207);
inline const pair queen_material = S(1674, 2038);

inline const pair bishop_pair = S(124, 149);

inline const std::array knight_mobility = {
  S(-49, -74), S(-14, -32), S(-1, -12), S(2, 8), S(9, 22), S(10, 26), S(10, 28), S(12, 25), S(19, 8),
};
inline const std::array bishop_mobility = {
  S(-65, -89), S(-39, -48), S(-20, -22), S(-8, -12), S(2, 5), S(7, 15), S(16, 26), S(18, 25), S(19, 26), S(19, 31), S(33, 14), S(26, 17), S(-8, -6), S(-2, 18),
};
inline const std::array rook_mobility = {
  S(-87, -76), S(-63, -46), S(-47, -25), S(-35, -12), S(-33, 1), S(-16, 3), S(-8, 7), S(6, 10), S(17, 16), S(27, 19), S(36, 19), S(39, 25), S(51, 27), S(64, 9), S(48, 22),
};
inline const std::array queen_mobility = {
  S(-32, -67), S(-35, -69), S(-30, -86), S(-19, -84), S(-15, -73), S(-8, -62), S(-5, -49), S(0, -30), S(0, -8), S(2, 7), S(5, 20), S(7, 40), S(12, 45), S(13, 58), S(17, 62), S(8, 75), S(20, 70), S(24, 67), S(31, 64), S(41, 55), S(43, 48), S(39, 54), S(22, 25), S(8, 16), S(-19, -23), S(-31, -33), S(-50, -60), S(-51, -61),
};

inline const pair pawn_threat_knight = S(75, 45);
inline const pair pawn_threat_bishop = S(98, 50);
inline const pair pawn_threat_rook = S(59, 50);
inline const pair pawn_threat_queen = S(47, 7);

inline const pair isolated_pawn = S(-8, -7);
inline const std::array passed_pawn = {
  S(3, 6), S(-1, 10), S(-9, 82), S(20, 146), S(72, 195), S(125, 314),
};
inline const std::array defended_passed_pawn = {
  S(3, 2), S(7, 36), S(23, 53), S(11, 97), S(51, 133), S(71, 222),
};
inline const std::array defended_pawn = {
  S(20, 22), S(28, 17), S(27, 32), S(92, 75), S(69, 114),
};
inline const std::array phalanx = {
  S(11, -10), S(19, 11), S(29, 36), S(75, 89), S(53, 99), S(11, 36),
};

inline const std::array shelter_centre = {
  S(-22, -6), S(26, -5), S(8, 3), S(-9, 7), S(-6, -2), S(2, 4), S(0, -1), S(0, 0),
};
inline const std::array shelter_mid = {
  S(-37, -16), S(55, -18), S(3, -2), S(-31, 4), S(0, 10), S(4, 7), S(6, 14), S(0, 0),
};
inline const std::array shelter_edge = {
  S(-24, -11), S(44, -21), S(5, 5), S(-25, 7), S(-3, 8), S(1, 11), S(1, 1), S(0, 0),
};

inline const std::array pawn_psqt = {
  S( -57,  -10), S( -20,  -11), S( -41,  -16), S( -46,  -20), S( -41,    9), S(   8,  -23), S(  55,  -55), S( -48,  -60),
  S( -57,  -31), S( -40,  -28), S( -28,  -54), S( -40,  -37), S( -35,  -33), S( -64,  -40), S(  18,  -82), S( -41,  -70),
  S( -65,  -13), S( -48,  -23), S( -22,  -51), S(  -9,  -70), S( -19,  -71), S( -35,  -60), S( -23,  -54), S( -61,  -60),
  S( -52,   16), S(   5,   -7), S( -15,  -30), S(  14,  -63), S(  14,  -67), S(  -7,  -61), S(  10,  -37), S( -48,  -41),
  S( -17,   87), S(  19,   77), S(  59,   33), S(  84,   -4), S(  82,  -18), S(  71,   -8), S(  45,   45), S(   5,   36),
  S( 108,  177), S( 110,  175), S(  99,  145), S(  93,  116), S(  74,   83), S(  16,   72), S(   0,  120), S( -11,  125),
};
inline const std::array knight_psqt = {
  S( -43,  -22), S( -61,  -49), S( -45,  -29), S( -36,  -28), S( -37,  -21), S(  -8,  -36), S( -40,  -33), S( -34,  -38),
  S( -52,  -32), S( -46,  -28), S( -42,  -12), S( -21,    9), S(   2,   -1), S(   0,  -22), S( -21,  -23), S( -18,  -31),
  S( -77,  -22), S( -30,    3), S( -22,   21), S(  10,   44), S(  18,   31), S(  25,   15), S(  31,  -10), S( -46,  -30),
  S( -42,   -5), S( -13,   13), S(   7,   47), S(  16,   54), S(  38,   53), S(  34,   33), S(  37,   11), S(   4,  -20),
  S(  -9,    9), S(   3,   24), S(  19,   57), S(  76,   60), S(  43,   65), S( 132,   30), S(  48,   23), S(  74,   -8),
  S( -26,  -18), S(  17,   16), S(  45,   45), S(  89,   38), S( 115,   29), S(  85,   51), S(  77,    5), S(  14,   -3),
  S( -66,  -25), S( -43,   -7), S(  25,   -3), S(  53,   18), S(  27,    5), S(  50,    0), S( -33,  -23), S(   5,  -30),
  S(-150,  -71), S( -26,  -21), S( -42,  -17), S(  -6,    2), S(   2,  -13), S( -53,  -27), S(  -9,  -11), S( -23,  -41),
};
inline const std::array bishop_psqt = {
  S( -19,  -35), S( -15,  -31), S( -17,  -24), S( -23,  -18), S( -23,  -33), S( -42,   -1), S( -14,  -24), S( -12,   -6),
  S(   6,  -22), S(   0,  -10), S(   6,   -7), S( -32,    9), S(  -2,   -6), S(   9,  -20), S(  47,  -21), S( -10,  -20),
  S( -12,  -12), S(  14,   11), S(   5,   23), S(  -4,   15), S(  -8,   46), S(  19,    9), S(  12,  -10), S(   6,   -5),
  S( -18,  -15), S( -14,   21), S(  12,   27), S(  30,   53), S(  41,   25), S(   3,   23), S(   0,   -2), S(  -3,  -21),
  S( -23,   -1), S(  -3,   15), S(   6,   28), S(  70,   33), S(  36,   42), S(  26,   14), S(  16,    7), S(   0,  -12),
  S( -26,  -16), S(  -2,   19), S(   9,   15), S(  45,    1), S(  67,   20), S(  72,   42), S(  58,   21), S(  37,  -12),
  S( -42,   -9), S( -22,    1), S( -10,   -3), S( -23,  -10), S( -12,    0), S(   7,    2), S(  -3,   -5), S( -34,  -25),
  S( -20,  -11), S( -21,   -6), S( -36,  -18), S( -20,  -11), S( -18,    0), S( -56,  -12), S( -12,  -16), S(  -3,   -7),
};
inline const std::array rook_psqt = {
  S( -34,  -28), S( -24,  -31), S(  -8,  -17), S(   6,  -31), S(  22,  -53), S(  15,  -48), S( -24,  -17), S( -10,  -72),
  S( -75,  -19), S( -51,  -24), S( -41,  -12), S( -29,  -31), S( -25,  -38), S(   3,  -49), S(   5,  -49), S( -88,  -49),
  S( -63,    0), S( -52,   -3), S( -44,    6), S( -34,  -16), S( -27,  -25), S(  -6,  -28), S(  22,  -33), S( -17,  -42),
  S( -57,   12), S( -54,   12), S( -32,    9), S( -11,   -9), S( -25,  -16), S(  -6,  -12), S(  -7,  -10), S( -25,  -33),
  S( -49,   37), S( -39,   31), S( -12,   26), S(   1,   18), S(   2,   -6), S(  32,    5), S(  16,   -6), S(   3,    1),
  S( -26,   48), S(   7,   37), S(   3,   37), S(  30,   22), S(  55,   10), S(  71,   21), S(  43,   25), S(  20,    4),
  S(  -3,   54), S(   1,   59), S(  46,   49), S(  66,   42), S(  60,   35), S(  93,   22), S(  44,   40), S(  76,   22),
  S(  25,    4), S(  24,   14), S(  25,   20), S(  40,   20), S(  43,    9), S(  16,   23), S(  30,   23), S(  52,   11),
};
inline const std::array queen_psqt = {
  S( -41,  -39), S( -37,  -49), S( -24,  -64), S(  10,  -90), S( -34,  -69), S( -77,  -76), S( -47,  -47), S( -50,  -43),
  S( -51,  -44), S( -35,  -27), S( -13,  -45), S( -12,  -53), S(   0,  -64), S(  -4,  -51), S( -12,  -51), S( -38,  -35),
  S( -41,  -41), S( -27,  -34), S( -26,   -8), S( -20,  -17), S( -17,    6), S(   4,   -5), S(  13,   -2), S( -12,  -21),
  S( -36,  -29), S( -41,  -17), S( -18,    0), S( -16,   52), S(   0,   26), S(  -9,   41), S(   8,   21), S( -10,   15),
  S( -39,  -29), S( -37,   10), S(  -9,   11), S(  -5,   56), S(  22,   80), S(  38,   59), S(  17,   74), S(  29,   28),
  S( -36,  -27), S( -22,   -4), S(  -7,    9), S(  11,   40), S(  57,   59), S( 112,   85), S(  96,   67), S(  68,   43),
  S( -30,  -23), S( -35,   19), S(   3,   29), S(   6,   40), S(  36,   49), S(  86,   56), S(  66,   34), S(  94,   22),
  S( -24,  -34), S(   2,   -6), S(  21,    3), S(  23,   19), S(  45,   33), S(  54,   38), S(  37,    8), S(  42,   12),
};
inline const std::array king_psqt = {
  S( -15,  -47), S(  51,  -75), S(  74,  -58), S( -36,  -71), S(  68, -110), S(  22,  -81), S( 169, -115), S( 132, -134),
  S(   6,  -43), S(   4,  -40), S(  -2,  -15), S( -48,   -5), S( -43,   -2), S(  32,  -20), S(  84,  -48), S( 112,  -82),
  S( -24,  -54), S( -10,  -17), S( -46,    3), S( -69,   27), S( -84,   33), S( -66,   19), S( -17,  -12), S( -40,  -35),
  S( -19,  -21), S( -22,   -3), S( -38,   32), S( -29,   36), S( -33,   43), S( -57,   42), S( -53,    8), S( -53,  -26),
  S( -10,   -7), S(  -2,   40), S(   0,   48), S(   0,   48), S(  -4,   65), S(  -3,   77), S(  -7,   55), S( -24,  -10),
  S(   0,   11), S(   2,   35), S(   8,   60), S(  10,   55), S(  11,   64), S(  13,   92), S(  12,   69), S(   1,   24),
  S(   0,   -9), S(   4,   15), S(   8,   33), S(   6,   24), S(   8,   27), S(   9,   42), S(   4,   33), S(   0,   -2),
  S(  -1,  -12), S(   1,   -3), S(   1,    3), S(   0,   -1), S(   0,    0), S(   2,    4), S(   0,    2), S(   0,   -6),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
