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
inline const pair pawn_material = S(136, 260);
inline const pair knight_material = S(560, 678);
inline const pair bishop_material = S(586, 749);
inline const pair rook_material = S(769, 1221);
inline const pair queen_material = S(1672, 1911);

inline const pair bishop_pair = S(112, 139);

inline const std::array knight_mobility = {
  S(-50, -72), S(-15, -41), S(-4, -21), S(4, -1), S(9, 17), S(12, 25), S(14, 28), S(13, 33), S(16, 32),
};
inline const std::array bishop_mobility = {
  S(-64, -88), S(-33, -54), S(-17, -24), S(-5, -17), S(0, 1), S(9, 11), S(4, 22), S(6, 22), S(17, 26), S(21, 32), S(25, 22), S(27, 25), S(1, -1), S(7, 22),
};
inline const std::array rook_mobility = {
  S(-72, -77), S(-49, -38), S(-41, -21), S(-25, -13), S(-27, -5), S(-10, -7), S(-3, 1), S(7, 3), S(16, 8), S(20, 14), S(28, 20), S(33, 29), S(34, 30), S(53, 14), S(35, 41),
};
inline const std::array queen_mobility = {
  S(-29, -63), S(-21, -62), S(-11, -79), S(-11, -66), S(-1, -51), S(1, -31), S(7, -25), S(6, 0), S(7, 17), S(6, 32), S(8, 42), S(9, 55), S(12, 51), S(16, 59), S(13, 59), S(14, 67), S(16, 58), S(20, 48), S(27, 46), S(29, 28), S(33, 20), S(23, 22), S(7, -5), S(-5, -11), S(-33, -38), S(-43, -50), S(-52, -60), S(-54, -62),
};

inline const pair pawn_threat_knight = S(79, 23);
inline const pair pawn_threat_bishop = S(86, 36);
inline const pair pawn_threat_rook = S(55, 27);
inline const pair pawn_threat_queen = S(40, -8);

inline const pair pp_threat_knight = S(28, 19);
inline const pair pp_threat_bishop = S(19, -1);
inline const pair pp_threat_rook = S(10, 11);
inline const pair pp_threat_queen = S(27, -44);

inline const pair knight_threat_pawn = S(9, 33);
inline const pair knight_threat_bishop = S(57, 31);
inline const pair knight_threat_rook = S(94, -10);
inline const pair knight_threat_queen = S(38, -14);

inline const pair bishop_threat_pawn = S(6, 11);
inline const pair bishop_threat_knight = S(34, 23);
inline const pair bishop_threat_rook = S(79, 17);
inline const pair bishop_threat_queen = S(72, 25);

inline const pair rook_threat_pawn = S(3, 37);
inline const pair rook_threat_knight = S(49, 26);
inline const pair rook_threat_bishop = S(51, 28);
inline const pair rook_threat_queen = S(77, -1);

inline const pair king_threat_pawn = S(26, 78);
inline const pair king_threat_knight = S(-10, 9);
inline const pair king_threat_bishop = S(12, 0);
inline const pair king_threat_rook = S(-43, -6);

inline const pair knight_check_threat = S(-31, -5);
inline const pair bishop_check_threat = S(-24, -24);
inline const pair rook_check_threat = S(-54, -14);
inline const pair queen_check_threat = S(-20, -77);

inline const pair hanging = S(31, 38);

inline const std::array passed_pawn = {
  S(-34, -99), S(-46, -91), S(-50, 3), S(-12, 90), S(65, 157), S(162, 250),
};
inline const std::array defended_passed_pawn = {
  S(10, -6), S(15, 26), S(26, 37), S(14, 79), S(49, 108), S(50, 150),
};
inline const std::array blocked_passed_pawn = {
  S(2, -5), S(8, -7), S(-12, -16), S(-23, -31), S(-17, -64), S(-26, -96),
};
inline const std::array friendly_passer_tropism = {
  S(6, 76), S(4, 70), S(14, 44), S(9, 29), S(15, 33), S(25, 33), S(6, 23),
};
inline const std::array enemy_passer_tropism = {
  S(-24, 2), S(7, 17), S(18, 47), S(27, 56), S(24, 60), S(18, 61), S(12, 66),
};
inline const std::array candidate_passed_pawn = {
  S(9, -13), S(4, -15), S(0, 33), S(14, 87), S(39, 91), S(33, 65),
};

inline const pair isolated_pawn = S(-7, -7);
inline const pair doubled_pawn = S(-4, -35);
inline const std::array defended_pawn = {
  S(20, 7), S(22, 2), S(18, 15), S(82, 55), S(61, 103),
};
inline const std::array phalanx = {
  S(7, -12), S(19, 9), S(26, 27), S(71, 55), S(53, 89), S(7, 20),
};

inline const std::array shelter_centre = {
  S(-29, -13), S(15, -18), S(-4, -11), S(1, -14), S(-5, 1), S(1, 9), S(21, 47),
};
inline const std::array shelter_mid = {
  S(-51, -12), S(31, -26), S(16, -21), S(14, -19), S(0, -1), S(-14, 18), S(4, 63),
};
inline const std::array shelter_edge = {
  S(-37, -17), S(24, -35), S(18, -19), S(10, -19), S(-9, -3), S(-18, 29), S(13, 66),
};

inline const std::array king_ring = {
  S(-40, 10), S(-31, 9), S(-20, -1), S(-12, 13), S(5, 11),
};

inline const std::array pawn_psqt = {
  S( -59,   -2), S( -20,   -4), S( -44,  -14), S( -53,  -23), S( -45,    0), S(  -6,  -24), S(  46,  -58), S( -41,  -58),
  S( -50,  -23), S( -44,  -21), S( -29,  -45), S( -40,  -40), S( -40,  -32), S( -64,  -30), S(  12,  -73), S( -38,  -67),
  S( -58,   -4), S( -47,  -18), S( -17,  -44), S( -12,  -64), S( -15,  -62), S( -27,  -48), S( -23,  -40), S( -50,  -53),
  S( -47,   15), S(   5,   -1), S( -14,  -24), S(  24,  -58), S(  23,  -64), S(  13,  -58), S(  25,  -34), S( -29,  -41),
  S( -16,   83), S(  12,   72), S(  46,   34), S(  65,    3), S(  60,    1), S(  50,    0), S(  26,   50), S(  -3,   33),
  S( 102,  138), S( 112,  147), S(  95,  131), S(  99,  111), S(  82,   77), S(  19,   59), S(  10,   93), S(   8,   89),
};
inline const std::array knight_psqt = {
  S( -41,  -26), S( -43,  -40), S( -38,  -19), S( -26,  -21), S( -33,  -18), S(  -6,  -28), S( -30,  -30), S( -19,  -30),
  S( -38,  -31), S( -43,  -18), S( -28,   -6), S(  -5,   10), S(  16,    3), S(   5,  -19), S( -15,  -22), S(  -2,  -22),
  S( -57,  -19), S( -14,    4), S(   1,    9), S(  20,   30), S(  31,   23), S(  39,    1), S(  39,  -13), S( -22,  -20),
  S( -27,   -2), S(  -4,    8), S(  21,   37), S(  38,   36), S(  27,   46), S(  53,   15), S(  20,   11), S(  17,  -11),
  S(  -8,   13), S(   5,   22), S(  21,   41), S(  47,   49), S(  37,   50), S(  87,   25), S(  29,   19), S(  47,   -4),
  S( -21,   -9), S(   0,   12), S(  25,   24), S(  47,   22), S(  66,   17), S(  54,   39), S(  20,   14), S(   2,   -1),
  S( -54,  -13), S( -32,   -5), S(   4,   -1), S(  23,   20), S(  13,    9), S(  39,   13), S( -23,  -16), S(  -7,  -18),
  S(-139,  -60), S( -18,  -20), S( -30,  -16), S(  -5,    0), S(   5,   -2), S( -43,  -14), S(  -5,   -7), S( -20,  -39),
};
inline const std::array bishop_psqt = {
  S( -18,  -35), S( -19,  -28), S( -14,  -14), S( -20,   -7), S( -23,  -29), S( -37,    0), S( -12,  -23), S(  -8,   -5),
  S(   7,  -21), S(   4,   -6), S(   6,  -11), S( -16,    8), S(   4,   -3), S(   2,  -17), S(  44,  -24), S( -15,  -20),
  S( -18,   -9), S(  16,   10), S(  15,   19), S(  -9,    6), S(   2,   38), S(  23,    3), S(  13,  -12), S(   2,   -6),
  S( -10,  -10), S( -18,   16), S(   3,   18), S(  23,   44), S(  21,   12), S(  14,   10), S(   4,   -6), S(  -1,  -19),
  S( -11,    0), S(  -6,   17), S(   4,   29), S(  42,   29), S(  32,   32), S(  14,   10), S(  14,    6), S(  -3,  -12),
  S( -14,   -2), S(   3,   18), S(   2,   21), S(  34,    5), S(  51,   15), S(  53,   36), S(  40,    9), S(  26,   -6),
  S( -29,    0), S( -26,    2), S(  -4,    4), S( -12,   -6), S( -19,   -1), S(  14,   -1), S(  -3,   -8), S( -16,  -25),
  S( -21,    0), S( -11,   -3), S( -27,  -13), S( -13,   -6), S( -14,    0), S( -49,  -14), S( -10,   -7), S(  -2,   -7),
};
inline const std::array rook_psqt = {
  S( -23,   -4), S(  -7,  -12), S(   7,   -4), S(  13,  -20), S(  29,  -41), S(  20,  -37), S( -29,    3), S(  -8,  -51),
  S( -61,    1), S( -38,   -6), S( -27,    7), S( -15,  -13), S( -21,  -25), S(   0,  -31), S(  -7,  -37), S( -77,  -33),
  S( -45,   11), S( -35,    8), S( -32,   16), S( -18,   -6), S( -13,  -13), S(   5,  -21), S(   8,  -27), S( -12,  -31),
  S( -39,   19), S( -37,   12), S( -19,   10), S(   1,   -6), S( -14,  -16), S(  -1,  -15), S( -17,  -12), S( -18,  -29),
  S( -35,   32), S( -27,   21), S(  -3,   16), S(  12,    3), S(   9,  -17), S(  39,  -12), S(   0,   -5), S(  -2,   -9),
  S( -14,   31), S(  12,   15), S(   9,   20), S(  20,    2), S(  43,   -7), S(  44,   -3), S(   9,   14), S(  -7,    0),
  S(  -8,   34), S(  -8,   42), S(  35,   23), S(  51,   15), S(  34,    8), S(  56,   13), S(  18,   32), S(  49,   13),
  S(  13,   11), S(  13,   12), S(  24,   17), S(  36,   15), S(  37,   10), S(  15,   17), S(  21,   25), S(  37,   11),
};
inline const std::array queen_psqt = {
  S( -14,  -10), S( -19,  -23), S(  -6,  -20), S(  13,  -21), S( -17,  -41), S( -65,  -58), S( -41,  -42), S( -41,  -33),
  S( -27,  -19), S( -14,    0), S(  -3,    2), S(   3,    9), S(  13,    5), S(  10,  -29), S(  -9,  -31), S( -20,  -24),
  S( -32,  -10), S(  -9,    9), S(  -3,   28), S(  -1,   21), S(   0,   36), S(  19,   11), S(  25,    0), S(  -7,  -14),
  S( -19,   -5), S( -24,    2), S(  -9,   29), S(   1,   49), S(  12,   14), S(  16,    9), S(  16,    3), S(   2,    1),
  S( -24,   -6), S( -17,   19), S(  -7,   18), S(   0,   42), S(  18,   27), S(  30,   -1), S(  23,   18), S(  32,  -36),
  S( -25,  -12), S( -16,   -3), S(  -3,    1), S(  -4,   12), S(  26,   18), S(  34,    9), S(  44,    9), S(  16,  -10),
  S( -17,   -7), S( -38,   10), S( -14,   20), S( -26,   13), S( -11,    4), S(  43,   11), S(  38,   13), S(  66,   -3),
  S( -17,  -26), S(  -6,   -9), S(   7,   -2), S(   5,    0), S(  21,    3), S(  20,    7), S(  18,   -3), S(  34,    9),
};
inline const std::array king_psqt = {
  S( -32,  -42), S(   8,  -50), S(  35,  -36), S( -64,  -44), S(  27,  -72), S( -11,  -47), S( 105,  -85), S(  61, -108),
  S( -13,  -37), S(   2,  -25), S(   1,   -5), S( -31,    4), S( -20,   10), S(  35,   -6), S(  78,  -35), S(  73,  -67),
  S( -23,  -47), S(   0,  -22), S(  -9,    3), S( -11,   23), S( -23,   25), S(  -7,   16), S(  17,  -16), S( -47,  -26),
  S( -17,  -20), S( -22,   -4), S( -14,   15), S( -11,   25), S(  -7,   30), S( -28,   27), S( -30,   -1), S( -52,  -38),
  S( -12,   -5), S(   0,   21), S(   0,   35), S(   0,   39), S(  -2,   48), S(   4,   54), S(  -9,   28), S( -25,  -14),
  S(  -1,   12), S(   2,   23), S(   7,   47), S(   8,   47), S(   9,   51), S(  12,   68), S(   8,   45), S(  -2,   19),
  S(   0,   -6), S(   2,   15), S(   4,   22), S(   7,   20), S(   8,   25), S(  10,   38), S(   0,   21), S(  -1,    2),
  S(  -1,  -10), S(   0,   -8), S(   0,    5), S(   1,    2), S(   1,    5), S(   1,    1), S(   0,    0), S(   0,   -1),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
