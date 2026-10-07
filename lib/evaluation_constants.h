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
inline const pair pawn_material = S(157, 300);
inline const pair knight_material = S(624, 770);
inline const pair bishop_material = S(651, 845);
inline const pair rook_material = S(873, 1384);
inline const pair queen_material = S(1878, 2196);

inline const pair bishop_pair = S(161, 189);

inline const std::array knight_mobility = {
  S(-52, -76), S(-24, -57), S(-11, -24), S(0, 0), S(11, 16), S(13, 27), S(15, 36), S(19, 40), S(27, 38),
};
inline const std::array bishop_mobility = {
  S(-65, -101), S(-38, -58), S(-15, -39), S(-8, -20), S(0, -4), S(8, 8), S(7, 22), S(10, 31), S(12, 33), S(21, 40), S(32, 25), S(32, 36), S(0, 1), S(3, 26),
};
inline const std::array rook_mobility = {
  S(-86, -109), S(-60, -56), S(-45, -42), S(-29, -21), S(-28, -7), S(-13, -7), S(-5, 5), S(2, 5), S(12, 13), S(19, 24), S(33, 29), S(37, 39), S(48, 40), S(71, 27), S(45, 58),
};
inline const std::array queen_mobility = {
  S(-47, -75), S(-36, -83), S(-24, -85), S(-14, -83), S(-11, -71), S(-5, -55), S(0, -43), S(6, -19), S(5, -1), S(8, 12), S(8, 33), S(7, 49), S(17, 56), S(13, 62), S(17, 63), S(20, 68), S(19, 72), S(26, 74), S(28, 64), S(37, 59), S(35, 43), S(40, 47), S(15, 14), S(5, 3), S(-19, -26), S(-38, -43), S(-58, -68), S(-58, -66),
};

inline const pair pawn_threat_knight = S(89, 24);
inline const pair pawn_threat_bishop = S(88, 48);
inline const pair pawn_threat_rook = S(73, 38);
inline const pair pawn_threat_queen = S(34, -8);

inline const pair pp_threat_knight = S(44, 29);
inline const pair pp_threat_bishop = S(24, 3);
inline const pair pp_threat_rook = S(11, 27);
inline const pair pp_threat_queen = S(41, -42);

inline const pair knight_threat_pawn = S(14, 42);
inline const pair knight_threat_bishop = S(77, 27);
inline const pair knight_threat_rook = S(101, -13);
inline const pair knight_threat_queen = S(42, -5);

inline const pair bishop_threat_pawn = S(9, 21);
inline const pair bishop_threat_knight = S(43, 33);
inline const pair bishop_threat_rook = S(86, 21);
inline const pair bishop_threat_queen = S(74, 22);

inline const pair rook_threat_pawn = S(5, 44);
inline const pair rook_threat_knight = S(59, 31);
inline const pair rook_threat_bishop = S(64, 39);
inline const pair rook_threat_queen = S(81, -13);

inline const pair hanging = S(28, 48);

inline const std::array passed_pawn = {
  S(-47, -120), S(-56, -104), S(-54, 4), S(-7, 89), S(72, 156), S(182, 270),
};
inline const std::array defended_passed_pawn = {
  S(8, -5), S(12, 27), S(27, 39), S(29, 68), S(44, 123), S(42, 153),
};
inline const std::array blocked_passed_pawn = {
  S(-2, -12), S(10, 3), S(-18, -14), S(-26, -43), S(-17, -97), S(-37, -143),
};
inline const std::array friendly_passer_tropism = {
  S(12, 80), S(1, 71), S(9, 42), S(7, 29), S(13, 28), S(30, 24), S(14, 19),
};
inline const std::array enemy_passer_tropism = {
  S(-87, -70), S(7, 26), S(33, 48), S(43, 61), S(37, 73), S(34, 77), S(19, 79),
};

inline const pair isolated_pawn = S(-10, -3);
inline const std::array defended_pawn = {
  S(32, 16), S(33, 20), S(33, 31), S(89, 85), S(79, 118),
};
inline const std::array phalanx = {
  S(13, -15), S(33, 10), S(40, 52), S(93, 109), S(61, 97), S(10, 29),
};

inline const std::array shelter_centre = {
  S(-33, -16), S(27, -16), S(0, -18), S(3, -18), S(-5, -5), S(-9, 20), S(17, 55),
};
inline const std::array shelter_mid = {
  S(-60, -23), S(45, -29), S(26, -24), S(13, -16), S(-5, -2), S(-24, 30), S(5, 65),
};
inline const std::array shelter_edge = {
  S(-38, -21), S(31, -42), S(25, -29), S(13, -19), S(-21, 0), S(-24, 38), S(13, 74),
};

inline const std::array king_ring = {
  S(-48, 15), S(-35, 11), S(-31, 2), S(-37, 6), S(-8, -109),
};

inline const std::array pawn_psqt = {
  S( -55,   10), S( -29,    4), S( -39,  -13), S( -52,  -26), S( -57,    2), S(   4,  -34), S(  57,  -55), S( -41,  -55),
  S( -62,  -23), S( -63,  -20), S( -32,  -56), S( -41,  -44), S( -42,  -45), S( -67,  -41), S(  12,  -80), S( -43,  -75),
  S( -59,   -3), S( -50,  -20), S( -22,  -54), S(  -1,  -76), S( -16,  -73), S( -25,  -59), S( -21,  -53), S( -53,  -64),
  S( -38,   26), S(   6,    1), S( -10,  -31), S(  15,  -61), S(  30,  -71), S(   8,  -67), S(  25,  -34), S( -28,  -32),
  S(  -6,   89), S(  24,   75), S(  40,   46), S(  69,    8), S(  46,   16), S(  54,    5), S(  15,   49), S(   0,   36),
  S( 123,  172), S( 113,  169), S( 101,  137), S( 108,  100), S(  70,   91), S(  31,   63), S( -22,   74), S(  25,   97),
};
inline const std::array knight_psqt = {
  S( -57,  -43), S( -61,  -49), S( -40,  -32), S( -44,  -19), S( -24,  -20), S( -22,  -27), S( -44,  -33), S( -49,  -36),
  S( -61,  -37), S( -39,  -16), S( -36,  -15), S(  -7,    1), S(  12,   -2), S(   1,  -19), S( -10,  -24), S( -17,  -26),
  S( -67,  -25), S( -22,   -5), S(   0,    8), S(  13,   36), S(  32,   32), S(  31,   -3), S(  41,  -16), S( -28,  -27),
  S( -32,   -2), S(  -8,   17), S(  26,   37), S(  36,   55), S(  52,   47), S(  54,   26), S(  40,   16), S(  14,  -13),
  S(  -6,    0), S(  17,   22), S(  31,   41), S(  89,   53), S(  41,   61), S( 114,   33), S(  29,   38), S(  66,   -1),
  S( -36,  -13), S(  -3,   16), S(  26,   37), S(  42,   31), S(  69,   34), S(  92,   35), S(  21,   33), S(   2,   -4),
  S( -52,  -21), S( -28,   -8), S(   9,    0), S(  21,   26), S(  18,   14), S(  47,    3), S( -13,   -8), S(  -3,  -18),
  S(-128,  -73), S( -23,  -18), S( -28,  -10), S( -11,  -10), S(  11,    6), S( -42,  -22), S( -14,  -11), S( -41,  -45),
};
inline const std::array bishop_psqt = {
  S( -21,  -25), S( -22,  -27), S(  -1,  -20), S( -19,  -12), S( -12,  -27), S( -29,    3), S( -20,  -20), S(  -8,  -14),
  S(  12,  -29), S(  14,  -13), S(   9,  -11), S(  -3,    7), S(  23,  -11), S(  10,   -9), S(  59,  -23), S(  -3,  -22),
  S( -12,  -12), S(  21,   16), S(  18,   26), S(   8,   11), S(  12,   36), S(  33,   -1), S(  29,  -15), S(  16,  -20),
  S( -10,  -14), S( -19,   14), S(   9,   25), S(  32,   38), S(  27,   18), S(  20,   12), S(   8,    0), S(  -1,  -26),
  S( -13,   -6), S(  -7,   21), S(  -2,   24), S(  44,   39), S(  24,   31), S(  30,   13), S(  14,    3), S(   3,  -11),
  S( -13,   -2), S(  -7,   29), S(   0,   20), S(  23,    5), S(  27,   16), S(  50,   36), S(  26,   26), S(   9,   -2),
  S( -32,   -3), S( -31,    6), S( -16,    2), S( -19,   -4), S( -22,   -4), S(  -6,    6), S( -24,   -4), S( -40,  -31),
  S( -21,   -1), S( -22,    0), S( -28,  -11), S( -25,   -6), S( -26,   -6), S( -63,  -19), S(  -8,    1), S(  -5,  -17),
};
inline const std::array rook_psqt = {
  S( -27,  -13), S( -12,  -21), S(   1,  -10), S(  24,  -30), S(  38,  -45), S(  32,  -42), S( -26,  -11), S( -12,  -65),
  S( -73,  -14), S( -40,  -21), S( -30,   -7), S( -19,  -15), S( -19,  -31), S(   6,  -47), S(  -6,  -41), S( -92,  -44),
  S( -64,    2), S( -35,    0), S( -38,   11), S( -22,   -7), S( -13,  -19), S(  -2,  -22), S(  14,  -32), S( -15,  -49),
  S( -52,   15), S( -41,   13), S( -15,   10), S( -16,    7), S(  -6,   -9), S(  -3,  -15), S(  -1,  -17), S( -32,  -28),
  S( -38,   37), S( -18,   26), S(   0,   24), S(   8,   10), S(  23,    0), S(  30,   -6), S(  13,    5), S(   4,  -10),
  S( -20,   42), S(   6,   28), S(  15,   22), S(  36,   10), S(  58,    1), S(  54,    4), S(  32,   23), S(   8,    5),
  S(  -2,   40), S( -14,   42), S(  22,   37), S(  46,   32), S(  45,   21), S(  51,   22), S(  25,   28), S(  47,    8),
  S(  13,    6), S(  17,   19), S(  15,   28), S(  30,   21), S(  22,   20), S(  11,   17), S(  24,   22), S(  35,   11),
};
inline const std::array queen_psqt = {
  S( -29,  -32), S( -27,  -38), S( -15,  -34), S(  13,  -41), S( -23,  -45), S( -66,  -60), S( -53,  -52), S( -31,  -34),
  S( -30,  -36), S( -32,  -21), S(  -2,  -28), S(   0,    0), S(  10,   -7), S(   5,  -42), S(  -1,  -45), S( -27,  -36),
  S( -46,  -27), S( -10,   -1), S(  -7,    6), S( -11,    2), S(   8,   27), S(  10,   19), S(  15,    0), S( -17,  -25),
  S( -24,    1), S( -27,   -5), S( -17,   31), S(   2,   52), S(  10,   53), S(  12,   25), S(  22,    7), S(   0,   -2),
  S( -19,    2), S(  -7,   32), S(  -6,   26), S(   3,   75), S(  30,   62), S(  35,   26), S(  39,   33), S(  26,  -18),
  S( -17,   -4), S(   1,   19), S(   5,   42), S(  11,   37), S(  41,   33), S(  62,   30), S(  66,   18), S(  32,  -22),
  S( -33,    0), S( -40,   14), S(  -8,   36), S(   3,   26), S(  -8,   16), S(  59,   13), S(  51,   16), S(  74,    1),
  S( -36,  -32), S( -17,  -19), S(  -9,  -14), S(  -7,  -14), S(   9,  -16), S(   3,  -12), S(  15,   -8), S(  33,  -10),
};
inline const std::array king_psqt = {
  S( -38,  -62), S(  34,  -67), S(  60,  -54), S( -74,  -57), S(  41,  -87), S( -12,  -68), S( 113, -106), S(  82, -132),
  S(  -1,  -42), S(   0,  -26), S(  11,   -9), S( -38,    1), S( -29,    5), S(  29,  -16), S(  82,  -47), S(  78,  -72),
  S( -12,  -34), S(  -4,  -15), S( -28,    5), S( -50,   19), S( -37,   21), S( -19,   10), S(   6,  -21), S( -48,  -35),
  S( -19,  -31), S( -10,    0), S( -22,   15), S( -20,   28), S( -17,   34), S( -23,   25), S( -33,    0), S( -65,  -38),
  S(  -6,   -7), S(  -1,   34), S(   3,   45), S(   0,   50), S(  -2,   54), S(   1,   60), S(  -7,   41), S( -26,   -7),
  S(  -1,    2), S(  10,   45), S(  11,   58), S(   6,   54), S(   8,   56), S(  13,   75), S(  10,   62), S(   1,   28),
  S(   0,   -2), S(   7,   26), S(   7,   41), S(   4,   26), S(   6,   30), S(   9,   39), S(   6,   39), S(   0,    6),
  S(  -1,  -11), S(   0,   -3), S(   0,    5), S(   0,    0), S(   1,    5), S(   3,    9), S(   0,    0), S(   0,   -7),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
