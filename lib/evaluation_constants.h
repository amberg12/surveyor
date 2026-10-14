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
inline const pair pawn_material = S(146, 291);
inline const pair knight_material = S(583, 746);
inline const pair bishop_material = S(611, 820);
inline const pair rook_material = S(817, 1342);
inline const pair queen_material = S(1767, 2124);

inline const pair bishop_pair = S(159, 187);

inline const std::array knight_mobility = {
  S(-47, -74), S(-20, -54), S(-11, -23), S(2, -1), S(6, 15), S(10, 27), S(15, 33), S(20, 39), S(23, 37),
};
inline const std::array bishop_mobility = {
  S(-61, -96), S(-36, -56), S(-11, -37), S(-7, -20), S(-2, -4), S(6, 9), S(9, 19), S(8, 28), S(12, 32), S(18, 37), S(27, 25), S(30, 35), S(1, 2), S(4, 25),
};
inline const std::array rook_mobility = {
  S(-79, -103), S(-55, -55), S(-44, -38), S(-28, -21), S(-28, -10), S(-14, -5), S(-6, 2), S(2, 4), S(12, 12), S(22, 22), S(28, 28), S(37, 39), S(44, 40), S(67, 26), S(43, 58),
};
inline const std::array queen_mobility = {
  S(-43, -73), S(-32, -80), S(-25, -83), S(-15, -80), S(-9, -69), S(-5, -53), S(1, -40), S(1, -19), S(6, -1), S(8, 10), S(9, 33), S(7, 46), S(13, 51), S(13, 60), S(16, 60), S(17, 64), S(20, 69), S(22, 71), S(25, 61), S(33, 57), S(33, 43), S(38, 47), S(16, 15), S(6, 4), S(-17, -25), S(-35, -41), S(-55, -66), S(-54, -64),
};

inline const pair pawn_threat_knight = S(86, 23);
inline const pair pawn_threat_bishop = S(84, 46);
inline const pair pawn_threat_rook = S(69, 36);
inline const pair pawn_threat_queen = S(32, -7);

inline const pair pp_threat_knight = S(39, 25);
inline const pair pp_threat_bishop = S(23, 5);
inline const pair pp_threat_rook = S(12, 26);
inline const pair pp_threat_queen = S(35, -41);

inline const pair knight_threat_pawn = S(12, 40);
inline const pair knight_threat_bishop = S(71, 27);
inline const pair knight_threat_rook = S(97, -13);
inline const pair knight_threat_queen = S(39, -5);

inline const pair bishop_threat_pawn = S(11, 19);
inline const pair bishop_threat_knight = S(39, 32);
inline const pair bishop_threat_rook = S(83, 22);
inline const pair bishop_threat_queen = S(69, 21);

inline const pair rook_threat_pawn = S(6, 49);
inline const pair rook_threat_knight = S(54, 29);
inline const pair rook_threat_bishop = S(61, 37);
inline const pair rook_threat_queen = S(78, -12);

inline const pair hanging = S(25, 45);

inline const std::array passed_pawn = {
  S(-41, -115), S(-48, -103), S(-54, 0), S(-8, 82), S(66, 154), S(170, 267),
};
inline const std::array defended_passed_pawn = {
  S(8, -5), S(11, 25), S(25, 38), S(25, 62), S(39, 119), S(42, 152),
};
inline const std::array blocked_passed_pawn = {
  S(-3, -11), S(7, 0), S(-17, -14), S(-24, -42), S(-15, -93), S(-36, -139),
};
inline const std::array friendly_passer_tropism = {
  S(6, 75), S(2, 69), S(7, 41), S(8, 26), S(13, 28), S(30, 25), S(13, 19),
};
inline const std::array enemy_passer_tropism = {
  S(-82, -67), S(8, 27), S(30, 44), S(41, 57), S(32, 69), S(33, 76), S(19, 78),
};

inline const pair isolated_pawn = S(-10, -5);
inline const std::array defended_pawn = {
  S(30, 13), S(25, 16), S(33, 33), S(85, 83), S(75, 115),
};
inline const std::array phalanx = {
  S(11, -10), S(30, 11), S(39, 47), S(88, 106), S(58, 93), S(10, 29),
};

inline const std::array shelter_centre = {
  S(-30, -16), S(25, -12), S(-2, -18), S(1, -20), S(-3, -4), S(-7, 18), S(16, 53),
};
inline const std::array shelter_mid = {
  S(-54, -24), S(44, -26), S(21, -23), S(13, -19), S(-5, -1), S(-23, 29), S(5, 64),
};
inline const std::array shelter_edge = {
  S(-35, -19), S(27, -44), S(24, -29), S(13, -17), S(-19, 0), S(-22, 38), S(12, 74),
};

inline const std::array king_ring = {
  S(-47, 20), S(-31, 9), S(-29, 2), S(-34, 5), S(-3, -110),
};

inline const std::array pawn_psqt = {
  S( -56,    8), S( -26,    5), S( -36,  -14), S( -46,  -24), S( -54,    0), S(   3,  -33), S(  53,  -53), S( -38,  -52),
  S( -54,  -22), S( -57,  -21), S( -27,  -53), S( -38,  -44), S( -41,  -42), S( -68,  -39), S(  17,  -80), S( -45,  -72),
  S( -59,   -8), S( -46,  -18), S( -21,  -56), S(  -3,  -73), S( -16,  -73), S( -24,  -59), S( -19,  -50), S( -51,  -61),
  S( -41,   22), S(   6,    4), S(  -5,  -30), S(  18,  -57), S(  28,  -69), S(  10,  -62), S(  23,  -32), S( -27,  -30),
  S(  -6,   87), S(  22,   74), S(  36,   45), S(  66,    9), S(  43,   15), S(  52,    7), S(  17,   49), S(   1,   36),
  S( 114,  167), S( 106,  161), S(  94,  130), S( 102,   98), S(  67,   87), S(  28,   58), S( -20,   73), S(  22,   94),
};
inline const std::array knight_psqt = {
  S( -53,  -41), S( -53,  -47), S( -39,  -30), S( -41,  -19), S( -23,  -18), S( -20,  -25), S( -43,  -32), S( -45,  -33),
  S( -56,  -36), S( -38,  -17), S( -33,  -14), S(  -5,    2), S(  10,   -3), S(   4,  -18), S(  -9,  -22), S( -16,  -25),
  S( -63,  -25), S( -21,   -4), S(   0,    9), S(  10,   34), S(  27,   28), S(  32,   -2), S(  35,  -15), S( -29,  -26),
  S( -32,   -2), S(  -8,   15), S(  24,   35), S(  36,   51), S(  51,   47), S(  51,   25), S(  38,   15), S(   8,  -14),
  S(  -5,    1), S(  18,   21), S(  28,   38), S(  83,   49), S(  36,   57), S( 107,   31), S(  28,   36), S(  63,    0),
  S( -33,  -14), S(  -2,   14), S(  25,   33), S(  39,   30), S(  66,   33), S(  87,   33), S(  20,   31), S(   2,   -5),
  S( -50,  -20), S( -26,   -7), S(   8,    0), S(  20,   25), S(  17,   15), S(  45,    4), S( -13,   -8), S(  -3,  -17),
  S(-122,  -69), S( -22,  -18), S( -26,   -8), S( -10,   -9), S(  10,    5), S( -40,  -21), S( -13,  -10), S( -38,  -43),
};
inline const std::array bishop_psqt = {
  S( -21,  -26), S( -19,  -26), S(  -1,  -18), S( -19,  -13), S( -11,  -26), S( -28,    1), S( -18,  -19), S(  -7,  -12),
  S(  11,  -27), S(  15,  -12), S(   9,  -11), S(  -4,    7), S(  19,   -5), S(   9,  -10), S(  60,  -20), S(  -2,  -21),
  S( -10,  -11), S(  20,   15), S(  17,   26), S(   8,   10), S(  11,   35), S(  30,    0), S(  26,  -14), S(  15,  -19),
  S( -11,  -13), S( -16,   12), S(  13,   25), S(  31,   37), S(  25,   18), S(  17,    8), S(   5,   -1), S(   1,  -26),
  S( -13,   -6), S(  -6,   19), S(   0,   23), S(  42,   37), S(  20,   30), S(  27,   12), S(  11,    3), S(   2,  -11),
  S( -14,   -2), S(  -6,   25), S(   0,   20), S(  22,    6), S(  25,   15), S(  48,   34), S(  24,   24), S(   9,   -1),
  S( -28,   -2), S( -28,    4), S( -14,    3), S( -18,   -2), S( -21,   -3), S(  -6,    5), S( -23,   -6), S( -39,  -29),
  S( -20,   -1), S( -21,    0), S( -28,  -11), S( -24,   -7), S( -24,   -7), S( -60,  -18), S(  -7,    1), S(  -5,  -15),
};
inline const std::array rook_psqt = {
  S( -26,  -14), S( -11,  -21), S(   0,  -12), S(  22,  -25), S(  37,  -42), S(  28,  -40), S( -25,  -13), S(  -9,  -65),
  S( -69,  -15), S( -38,  -18), S( -29,   -8), S( -18,  -14), S( -19,  -30), S(   8,  -45), S(  -6,  -40), S( -86,  -44),
  S( -59,    0), S( -33,    1), S( -35,    8), S( -20,   -6), S( -11,  -19), S(  -4,  -25), S(  14,  -32), S( -14,  -46),
  S( -49,   15), S( -40,   13), S( -16,   10), S( -16,    8), S(  -7,  -10), S(  -3,  -13), S(  -2,  -16), S( -29,  -28),
  S( -35,   36), S( -19,   25), S(  -1,   23), S(   7,   10), S(  20,    0), S(  28,   -3), S(  11,    3), S(   6,   -9),
  S( -18,   41), S(   4,   28), S(  12,   21), S(  32,    9), S(  53,    2), S(  49,    2), S(  30,   23), S(   8,    5),
  S(  -3,   38), S( -14,   40), S(  21,   36), S(  43,   31), S(  42,   18), S(  49,   21), S(  25,   28), S(  46,    9),
  S(  13,    7), S(  17,   20), S(  15,   28), S(  28,   20), S(  22,   20), S(  11,   16), S(  24,   23), S(  35,   12),
};
inline const std::array queen_psqt = {
  S( -29,  -32), S( -28,  -38), S( -14,  -33), S(  14,  -39), S( -22,  -42), S( -63,  -57), S( -51,  -51), S( -29,  -33),
  S( -30,  -35), S( -30,  -22), S(  -4,  -27), S(   0,   -2), S(   7,   -5), S(   5,  -39), S(  -3,  -43), S( -26,  -34),
  S( -42,  -27), S(  -9,   -3), S(  -7,    5), S(  -9,    2), S(   4,   25), S(  10,   19), S(  12,   -2), S( -15,  -23),
  S( -24,    1), S( -26,   -6), S( -14,   29), S(   1,   48), S(   8,   50), S(  11,   23), S(  21,    8), S(   0,    0),
  S( -16,    3), S(  -7,   31), S(  -6,   24), S(   2,   70), S(  30,   60), S(  32,   26), S(  38,   33), S(  25,  -17),
  S( -17,   -5), S(   1,   18), S(   4,   40), S(   9,   36), S(  40,   33), S(  59,   29), S(  62,   18), S(  30,  -20),
  S( -30,   -1), S( -38,   12), S(  -8,   34), S(   3,   25), S(  -5,   16), S(  57,   12), S(  48,   16), S(  72,    3),
  S( -34,  -30), S( -16,  -17), S(  -8,  -13), S(  -6,  -13), S(  10,  -14), S(   5,  -11), S(  16,   -6), S(  32,   -7),
};
inline const std::array king_psqt = {
  S( -35,  -59), S(  30,  -65), S(  54,  -54), S( -68,  -56), S(  41,  -86), S(  -6,  -67), S( 112, -102), S(  77, -126),
  S(   0,  -41), S(   0,  -25), S(   8,  -11), S( -35,   -1), S( -27,    3), S(  32,  -14), S(  79,  -45), S(  77,  -67),
  S( -12,  -34), S(  -4,  -14), S( -26,    2), S( -46,   16), S( -37,   20), S( -20,    6), S(   5,  -22), S( -46,  -37),
  S( -19,  -31), S( -10,    0), S( -22,   15), S( -20,   26), S( -18,   33), S( -22,   25), S( -33,    0), S( -65,  -37),
  S(  -6,   -5), S(  -1,   33), S(   2,   44), S(   0,   47), S(  -2,   53), S(   0,   58), S(  -7,   39), S( -25,   -6),
  S(  -1,    4), S(  10,   45), S(  11,   58), S(   6,   52), S(   8,   56), S(  13,   74), S(  10,   62), S(   1,   26),
  S(   0,   -1), S(   7,   26), S(   7,   40), S(   4,   26), S(   6,   30), S(   8,   39), S(   6,   39), S(   0,    7),
  S(  -2,  -11), S(   0,   -3), S(   0,    5), S(   0,    0), S(   1,    5), S(   3,    9), S(   0,    0), S(   0,   -6),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
