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
inline const pair pawn_material = S(137, 256);
inline const pair knight_material = S(565, 678);
inline const pair bishop_material = S(588, 747);
inline const pair rook_material = S(780, 1228);
inline const pair queen_material = S(1669, 1983);

inline const pair bishop_pair = S(113, 147);

inline const std::array knight_mobility = {
  S(-51, -73), S(-19, -45), S(-5, -24), S(3, -1), S(8, 18), S(14, 26), S(13, 31), S(16, 33), S(19, 34),
};
inline const std::array bishop_mobility = {
  S(-65, -92), S(-35, -56), S(-17, -26), S(-2, -20), S(4, 2), S(6, 13), S(11, 20), S(12, 26), S(18, 26), S(20, 35), S(23, 22), S(21, 27), S(-1, -2), S(2, 21),
};
inline const std::array rook_mobility = {
  S(-78, -82), S(-55, -44), S(-46, -30), S(-28, -16), S(-29, -9), S(-14, -5), S(-8, 0), S(5, 2), S(13, 11), S(24, 15), S(32, 24), S(36, 33), S(45, 37), S(63, 20), S(40, 45),
};
inline const std::array queen_mobility = {
  S(-39, -66), S(-32, -66), S(-22, -85), S(-20, -75), S(-9, -62), S(-7, -44), S(0, -37), S(1, -13), S(0, 1), S(6, 18), S(9, 29), S(7, 40), S(13, 42), S(19, 54), S(17, 56), S(14, 67), S(16, 61), S(22, 57), S(31, 60), S(33, 47), S(40, 41), S(31, 44), S(19, 13), S(8, 7), S(-25, -28), S(-35, -40), S(-51, -61), S(-53, -63),
};

inline const pair pawn_threat_knight = S(78, 21);
inline const pair pawn_threat_bishop = S(77, 30);
inline const pair pawn_threat_rook = S(58, 27);
inline const pair pawn_threat_queen = S(36, -12);

inline const pair pp_threat_knight = S(25, 24);
inline const pair pp_threat_bishop = S(17, -1);
inline const pair pp_threat_rook = S(11, 20);
inline const pair pp_threat_queen = S(28, -32);

inline const pair knight_threat_pawn = S(-4, 20);
inline const pair knight_threat_bishop = S(51, 27);
inline const pair knight_threat_rook = S(93, -17);
inline const pair knight_threat_queen = S(36, -17);

inline const pair bishop_threat_pawn = S(-8, 1);
inline const pair bishop_threat_knight = S(32, 21);
inline const pair bishop_threat_rook = S(76, 11);
inline const pair bishop_threat_queen = S(67, 21);

inline const pair rook_threat_pawn = S(-9, 28);
inline const pair rook_threat_knight = S(22, 20);
inline const pair rook_threat_bishop = S(38, 13);
inline const pair rook_threat_queen = S(82, -8);

inline const pair hanging = S(26, 53);

inline const std::array passed_pawn = {
  S(-30, -104), S(-41, -90), S(-54, 1), S(-12, 85), S(55, 153), S(155, 245),
};
inline const std::array defended_passed_pawn = {
  S(8, -6), S(17, 28), S(27, 38), S(15, 72), S(48, 107), S(50, 149),
};
inline const std::array blocked_passed_pawn = {
  S(0, -14), S(9, -5), S(-11, -17), S(-21, -32), S(-17, -65), S(-34, -102),
};
inline const std::array friendly_passer_tropism = {
  S(4, 70), S(4, 67), S(15, 42), S(7, 27), S(11, 30), S(24, 32), S(5, 20),
};
inline const std::array enemy_passer_tropism = {
  S(-58, -41), S(12, 27), S(24, 47), S(29, 57), S(27, 64), S(26, 65), S(11, 70),
};

inline const pair isolated_pawn = S(-2, -8);
inline const std::array defended_pawn = {
  S(19, 18), S(27, 16), S(21, 27), S(84, 76), S(66, 119),
};
inline const std::array phalanx = {
  S(2, -10), S(18, 8), S(26, 41), S(78, 90), S(54, 93), S(7, 21),
};

inline const std::array shelter_centre = {
  S(-34, -12), S(25, -13), S(-3, -5), S(5, -18), S(-8, 0), S(-1, 7), S(16, 43),
};
inline const std::array shelter_mid = {
  S(-56, -19), S(35, -20), S(22, -14), S(20, -20), S(-1, 0), S(-19, 15), S(0, 60),
};
inline const std::array shelter_edge = {
  S(-42, -15), S(22, -34), S(21, -16), S(13, -19), S(-6, -3), S(-17, 27), S(9, 62),
};

inline const std::array king_ring = {
  S(-34, 12), S(-26, 11), S(-26, 2), S(-32, 8), S(-11, -85),
};

inline const std::array pawn_psqt = {
  S( -54,    0), S( -19,   -2), S( -38,  -12), S( -44,  -18), S( -43,    1), S(   7,  -27), S(  53,  -56), S( -41,  -55),
  S( -55,  -20), S( -40,  -23), S( -24,  -48), S( -36,  -36), S( -34,  -32), S( -65,  -36), S(  20,  -78), S( -39,  -70),
  S( -62,   -3), S( -49,  -16), S( -22,  -44), S( -10,  -61), S( -26,  -67), S( -26,  -49), S( -27,  -41), S( -51,  -49),
  S( -47,   17), S(   7,    1), S( -17,  -24), S(  14,  -57), S(  19,  -64), S(   6,  -57), S(  24,  -36), S( -31,  -41),
  S( -17,   82), S(  18,   76), S(  49,   38), S(  72,    7), S(  55,    5), S(  53,    0), S(  27,   50), S(  -3,   33),
  S( 103,  137), S( 115,  146), S(  97,  129), S(  96,  108), S(  81,   73), S(  13,   53), S(  -4,   87), S(   1,   86),
};
inline const std::array knight_psqt = {
  S( -44,  -28), S( -52,  -41), S( -41,  -22), S( -29,  -22), S( -33,  -17), S(  -1,  -24), S( -41,  -30), S( -24,  -32),
  S( -45,  -34), S( -47,  -20), S( -38,  -10), S(  -7,   11), S(  11,    2), S(  10,  -18), S( -12,  -21), S(  -7,  -25),
  S( -65,  -22), S( -21,    2), S(  -2,    6), S(  14,   30), S(  25,   23), S(  33,    3), S(  37,   -8), S( -31,  -20),
  S( -35,   -3), S(  -7,    7), S(  20,   35), S(  36,   40), S(  43,   46), S(  50,   17), S(  41,   14), S(  11,   -9),
  S( -10,   10), S(  13,   22), S(  21,   41), S(  77,   50), S(  43,   57), S( 115,   25), S(  35,   28), S(  64,   -1),
  S( -26,  -10), S(  -4,   11), S(  34,   25), S(  50,   25), S(  66,   21), S(  63,   41), S(  26,   17), S(   8,    1),
  S( -59,  -16), S( -36,   -7), S(   0,   -3), S(  28,   22), S(  15,    8), S(  35,   10), S( -27,  -19), S(  -6,  -19),
  S(-144,  -62), S( -21,  -22), S( -32,  -17), S(  -7,    0), S(   5,   -2), S( -47,  -16), S(  -4,   -6), S( -23,  -41),
};
inline const std::array bishop_psqt = {
  S( -19,  -38), S( -17,  -30), S( -14,  -20), S( -21,  -11), S( -18,  -29), S( -35,    4), S( -10,  -22), S(  -4,   -5),
  S(  10,  -21), S(   3,   -8), S(   9,  -12), S( -14,    5), S(  11,   -4), S(  13,  -16), S(  53,  -22), S( -13,  -22),
  S( -20,  -10), S(  21,   11), S(  18,   20), S(   2,    8), S(   9,   43), S(  27,    6), S(  16,  -10), S(   7,   -4),
  S( -10,  -13), S( -20,   18), S(  16,   24), S(  29,   46), S(  35,   18), S(  15,   12), S(   7,   -2), S(  -2,  -22),
  S( -16,   -2), S(  -7,   14), S(   1,   31), S(  58,   36), S(  33,   34), S(  24,   13), S(  12,    7), S(   0,   -8),
  S( -19,   -6), S(   0,   18), S(   0,   21), S(  28,    8), S(  52,   17), S(  41,   35), S(  44,   12), S(  10,   -8),
  S( -37,   -3), S( -30,    1), S(  -9,    0), S( -15,   -6), S( -28,   -1), S(   7,   -2), S( -19,  -12), S( -38,  -26),
  S( -20,   -1), S( -13,   -5), S( -28,  -13), S( -18,   -8), S( -15,    1), S( -56,  -18), S( -12,   -9), S( -10,  -11),
};
inline const std::array rook_psqt = {
  S( -25,  -15), S( -15,  -22), S(   0,  -13), S(  11,  -23), S(  30,  -43), S(  24,  -32), S( -20,   -3), S( -12,  -63),
  S( -70,   -7), S( -44,  -14), S( -31,    3), S( -22,  -19), S( -24,  -26), S(   7,  -36), S(   4,  -40), S( -79,  -38),
  S( -53,    2), S( -40,    2), S( -36,   12), S( -26,   -8), S( -13,  -16), S(   0,  -19), S(  19,  -26), S( -14,  -34),
  S( -45,   14), S( -42,    8), S( -26,    9), S(  -2,   -7), S( -17,  -16), S(  -5,  -12), S( -10,  -10), S( -20,  -30),
  S( -38,   28), S( -24,   19), S(  -5,   17), S(   9,    3), S(  12,  -17), S(  36,   -6), S(  15,   -3), S(   7,   -5),
  S( -16,   33), S(  10,   13), S(   5,   20), S(  22,    4), S(  43,   -3), S(  55,    2), S(  23,   19), S(   6,    2),
  S( -15,   45), S( -12,   50), S(  30,   32), S(  51,   26), S(  40,   21), S(  67,   20), S(  33,   34), S(  58,   19),
  S(   9,   14), S(  10,   15), S(  21,   19), S(  33,   18), S(  34,   14), S(  16,   22), S(  19,   27), S(  40,   14),
};
inline const std::array queen_psqt = {
  S( -28,  -27), S( -29,  -33), S( -11,  -29), S(  10,  -31), S( -17,  -38), S( -69,  -63), S( -45,  -46), S( -46,  -37),
  S( -38,  -29), S( -25,  -15), S( -10,  -11), S(  -2,   -9), S(   5,   -4), S(  11,  -37), S(  -5,  -34), S( -25,  -28),
  S( -43,  -23), S( -17,   -6), S(  -7,    7), S( -12,    5), S(  -1,   40), S(  15,    6), S(  22,    3), S( -11,  -15),
  S( -28,   -3), S( -32,   -3), S( -10,   18), S(  -3,   40), S(  11,   26), S(  10,   20), S(  18,   11), S(  -2,    5),
  S( -25,    0), S( -13,   32), S(  -8,   19), S(   1,   53), S(  27,   49), S(  37,   14), S(  31,   38), S(  30,  -24),
  S( -20,   -8), S(  -9,    4), S(  10,   23), S(   8,   28), S(  41,   35), S(  58,   27), S(  59,   24), S(  28,   -4),
  S( -24,  -17), S( -38,    9), S(  -4,   28), S(  -2,   32), S(   8,   15), S(  57,   14), S(  46,   17), S(  74,   -2),
  S( -23,  -39), S( -13,  -15), S(   3,   -5), S(   0,   -9), S(  15,   -3), S(  22,    7), S(  18,   -2), S(  24,    0),
};
inline const std::array king_psqt = {
  S( -30,  -42), S(  17,  -56), S(  44,  -41), S( -57,  -56), S(  39,  -84), S(   0,  -59), S( 123,  -92), S(  81, -111),
  S(  -6,  -36), S(   4,  -29), S(   2,   -9), S( -33,    0), S( -22,    5), S(  33,   -9), S(  87,  -39), S(  84,  -64),
  S( -21,  -46), S(   0,  -25), S( -21,   -3), S( -27,   18), S( -40,   21), S( -21,   13), S(  13,  -18), S( -47,  -29),
  S( -19,  -22), S( -27,   -5), S( -22,   12), S( -20,   20), S( -18,   26), S( -36,   25), S( -36,    0), S( -55,  -37),
  S( -13,   -4), S(  -1,   27), S(  -1,   36), S(  -3,   39), S(  -6,   49), S(   2,   59), S(  -9,   37), S( -24,   -8),
  S(   0,   15), S(   3,   31), S(   6,   51), S(   7,   50), S(   8,   55), S(  13,   79), S(  11,   58), S(  -1,   23),
  S(   0,   -2), S(   4,   20), S(   5,   25), S(   7,   21), S(   8,   28), S(  10,   43), S(   3,   28), S(   0,    4),
  S(  -1,   -8), S(   0,   -7), S(   1,    7), S(   0,    2), S(   1,    5), S(   2,    3), S(   0,    2), S(   0,    0),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
