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
inline const pair pawn_material = S(134, 260);
inline const pair knight_material = S(565, 678);
inline const pair bishop_material = S(581, 750);
inline const pair rook_material = S(780, 1228);
inline const pair queen_material = S(1672, 1987);

inline const pair bishop_pair = S(114, 147);

inline const std::array knight_mobility = {
  S(-52, -73), S(-19, -42), S(-5, -22), S(0, -1), S(8, 16), S(12, 25), S(16, 31), S(17, 34), S(20, 32),
};
inline const std::array bishop_mobility = {
  S(-70, -94), S(-38, -59), S(-17, -29), S(-5, -18), S(-1, 0), S(6, 11), S(6, 21), S(8, 24), S(19, 27), S(23, 35), S(27, 23), S(30, 30), S(2, 0), S(8, 27),
};
inline const std::array rook_mobility = {
  S(-76, -81), S(-55, -46), S(-44, -27), S(-28, -16), S(-28, -8), S(-14, -6), S(-9, -1), S(6, 3), S(12, 9), S(24, 16), S(28, 22), S(36, 32), S(44, 36), S(63, 20), S(40, 49),
};
inline const std::array queen_mobility = {
  S(-40, -67), S(-34, -67), S(-26, -86), S(-20, -75), S(-7, -62), S(-5, -43), S(0, -37), S(0, -13), S(3, 2), S(6, 18), S(6, 29), S(9, 42), S(14, 42), S(15, 53), S(15, 56), S(13, 66), S(18, 62), S(24, 57), S(32, 59), S(35, 47), S(41, 40), S(33, 44), S(21, 13), S(8, 7), S(-24, -28), S(-35, -40), S(-51, -61), S(-53, -63),
};

inline const pair pawn_threat_knight = S(73, 24);
inline const pair pawn_threat_bishop = S(86, 37);
inline const pair pawn_threat_rook = S(59, 30);
inline const pair pawn_threat_queen = S(38, -11);

inline const pair pp_threat_knight = S(36, 24);
inline const pair pp_threat_bishop = S(23, -3);
inline const pair pp_threat_rook = S(28, 25);
inline const pair pp_threat_queen = S(33, -30);

inline const pair knight_threat_pawn = S(9, 33);
inline const pair knight_threat_bishop = S(52, 30);
inline const pair knight_threat_rook = S(94, -13);
inline const pair knight_threat_queen = S(36, -16);

inline const pair bishop_threat_pawn = S(6, 16);
inline const pair bishop_threat_knight = S(37, 26);
inline const pair bishop_threat_rook = S(80, 17);
inline const pair bishop_threat_queen = S(71, 22);

inline const pair rook_threat_pawn = S(3, 40);
inline const pair rook_threat_knight = S(48, 27);
inline const pair rook_threat_bishop = S(53, 30);
inline const pair rook_threat_queen = S(74, -9);

inline const pair hanging = S(23, 41);

inline const std::array passed_pawn = {
  S(-28, -105), S(-40, -90), S(-49, 2), S(-15, 85), S(50, 152), S(154, 245),
};
inline const std::array defended_passed_pawn = {
  S(10, -6), S(17, 28), S(27, 38), S(15, 75), S(47, 108), S(49, 149),
};
inline const std::array blocked_passed_pawn = {
  S(0, -12), S(9, -5), S(-10, -17), S(-21, -33), S(-11, -65), S(-30, -98),
};
inline const std::array friendly_passer_tropism = {
  S(4, 68), S(0, 64), S(13, 39), S(8, 29), S(14, 34), S(22, 29), S(6, 23),
};
inline const std::array enemy_passer_tropism = {
  S(-58, -42), S(11, 24), S(22, 46), S(32, 59), S(27, 64), S(24, 67), S(10, 70),
};

inline const pair isolated_pawn = S(-9, -7);
inline const std::array defended_pawn = {
  S(16, 13), S(21, 10), S(25, 24), S(84, 71), S(64, 114),
};
inline const std::array phalanx = {
  S(7, -10), S(17, 11), S(25, 38), S(76, 92), S(53, 92), S(7, 21),
};

inline const std::array shelter_centre = {
  S(-33, -14), S(24, -15), S(-4, -4), S(5, -16), S(-8, 0), S(0, 7), S(16, 42),
};
inline const std::array shelter_mid = {
  S(-57, -16), S(38, -22), S(21, -14), S(19, -20), S(-4, -1), S(-16, 15), S(0, 59),
};
inline const std::array shelter_edge = {
  S(-42, -15), S(24, -31), S(21, -15), S(12, -23), S(-7, -3), S(-17, 27), S(9, 61),
};

inline const std::array king_ring = {
  S(-38, 14), S(-31, 11), S(-30, -1), S(-33, 12), S(-5, -84),
};

inline const std::array pawn_psqt = {
  S( -55,    1), S( -23,   -4), S( -39,  -12), S( -47,  -18), S( -47,    2), S(   4,  -26), S(  50,  -56), S( -42,  -54),
  S( -54,  -23), S( -43,  -22), S( -29,  -48), S( -41,  -36), S( -36,  -34), S( -68,  -37), S(  13,  -78), S( -40,  -73),
  S( -62,   -3), S( -51,  -17), S( -20,  -41), S( -13,  -60), S( -21,  -63), S( -27,  -51), S( -29,  -45), S( -51,  -53),
  S( -43,   19), S(   2,   -1), S( -12,  -24), S(  18,  -58), S(  23,  -64), S(  10,  -59), S(  20,  -36), S( -30,  -42),
  S( -13,   81), S(  22,   76), S(  51,   39), S(  75,    9), S(  59,    3), S(  54,    0), S(  31,   52), S(  -1,   32),
  S( 104,  139), S( 115,  147), S(  97,  130), S(  98,  108), S(  83,   75), S(  14,   53), S(  -3,   87), S(   1,   87),
};
inline const std::array knight_psqt = {
  S( -43,  -29), S( -53,  -41), S( -41,  -21), S( -29,  -21), S( -33,  -17), S(  -2,  -26), S( -35,  -30), S( -23,  -31),
  S( -44,  -33), S( -47,  -20), S( -37,  -10), S(  -7,    8), S(  13,    2), S(  10,  -19), S( -12,  -21), S(  -6,  -26),
  S( -62,  -22), S( -22,    0), S(  -9,    7), S(  13,   30), S(  21,   25), S(  30,    2), S(  34,  -10), S( -31,  -21),
  S( -34,   -4), S(  -7,    7), S(  18,   37), S(  33,   42), S(  42,   47), S(  49,   21), S(  41,   13), S(  12,   -9),
  S( -10,   11), S(  12,   18), S(  19,   43), S(  75,   53), S(  39,   57), S( 116,   26), S(  36,   25), S(  66,   -3),
  S( -24,  -10), S(  -4,   10), S(  31,   26), S(  46,   24), S(  65,   20), S(  60,   42), S(  25,   17), S(   7,    0),
  S( -56,  -15), S( -33,   -7), S(   2,   -2), S(  30,   24), S(  17,    9), S(  39,   13), S( -25,  -19), S(  -2,  -19),
  S(-143,  -61), S( -20,  -22), S( -30,  -17), S(  -7,   -1), S(   5,   -3), S( -46,  -17), S(  -4,   -7), S( -22,  -41),
};
inline const std::array bishop_psqt = {
  S( -16,  -36), S( -16,  -28), S( -10,  -15), S( -17,   -7), S( -16,  -26), S( -32,    5), S( -10,  -21), S(  -3,   -4),
  S(  10,  -21), S(   5,   -7), S(  11,  -10), S( -14,    7), S(  10,   -4), S(  14,  -14), S(  53,  -21), S( -12,  -20),
  S( -19,   -8), S(  19,   10), S(  13,   18), S(  -1,    8), S(   0,   41), S(  23,    5), S(  15,  -11), S(   9,   -4),
  S(  -9,  -11), S( -19,   16), S(  12,   20), S(  17,   41), S(  25,   16), S(  13,   11), S(   6,   -4), S(  -1,  -20),
  S( -13,   -1), S(  -3,   15), S(  -2,   28), S(  47,   30), S(  26,   30), S(  24,   12), S(  12,    5), S(   4,   -8),
  S( -15,   -4), S(   0,   17), S(  -1,   21), S(  26,    6), S(  51,   17), S(  41,   34), S(  44,   12), S(  16,   -6),
  S( -34,   -2), S( -27,    1), S(  -8,    0), S( -13,   -5), S( -26,   -1), S(   9,   -1), S( -17,  -12), S( -33,  -25),
  S( -18,    0), S( -13,   -5), S( -27,  -14), S( -16,   -8), S( -15,    0), S( -56,  -18), S( -12,   -8), S(  -8,  -10),
};
inline const std::array rook_psqt = {
  S( -26,  -15), S( -15,  -21), S(  -1,  -15), S(  14,  -25), S(  31,  -42), S(  22,  -36), S( -22,   -4), S( -10,  -60),
  S( -69,   -7), S( -44,  -13), S( -32,    1), S( -21,  -19), S( -23,  -26), S(   5,  -37), S(   2,  -39), S( -79,  -38),
  S( -52,    5), S( -40,    3), S( -37,   11), S( -24,   -6), S( -12,  -14), S(   1,  -21), S(  19,  -27), S( -15,  -34),
  S( -46,   15), S( -40,    8), S( -25,    9), S(   1,   -6), S( -17,  -14), S(   0,  -11), S(  -7,   -9), S( -20,  -27),
  S( -41,   30), S( -24,   22), S(   0,   19), S(  11,    7), S(  22,  -11), S(  41,   -5), S(  21,    0), S(   4,   -3),
  S( -21,   31), S(   9,   18), S(   6,   23), S(  25,    7), S(  46,    0), S(  55,    3), S(  22,   18), S(   6,    2),
  S( -20,   39), S( -17,   44), S(  25,   28), S(  46,   21), S(  34,   16), S(  64,   16), S(  29,   33), S(  55,   15),
  S(   7,   13), S(  10,   13), S(  21,   19), S(  32,   17), S(  35,   13), S(  16,   21), S(  19,   26), S(  40,   13),
};
inline const std::array queen_psqt = {
  S( -27,  -27), S( -28,  -32), S( -12,  -30), S(  12,  -32), S( -17,  -39), S( -69,  -63), S( -45,  -46), S( -47,  -38),
  S( -37,  -29), S( -27,  -16), S(  -8,  -12), S(  -3,   -9), S(   5,   -6), S(   8,  -38), S(  -7,  -35), S( -24,  -28),
  S( -43,  -23), S( -17,   -3), S( -10,    9), S( -14,    5), S(  -3,   42), S(  14,    5), S(  23,    2), S( -10,  -16),
  S( -24,   -1), S( -32,   -4), S( -14,   18), S(  -4,   42), S(  10,   27), S(  11,   22), S(  18,   11), S(   0,    6),
  S( -23,    1), S( -11,   31), S(  -7,   20), S(   1,   53), S(  30,   50), S(  39,   15), S(  36,   38), S(  33,  -23),
  S( -22,   -9), S(  -8,    5), S(   9,   24), S(   7,   27), S(  40,   35), S(  55,   25), S(  57,   22), S(  28,   -5),
  S( -26,  -18), S( -38,   11), S(  -6,   27), S(  -4,   31), S(   8,   15), S(  58,   15), S(  47,   17), S(  74,   -2),
  S( -23,  -39), S( -13,  -16), S(   2,   -6), S(   0,   -9), S(  15,   -3), S(  22,    7), S(  17,   -3), S(  25,    0),
};
inline const std::array king_psqt = {
  S( -30,  -42), S(  17,  -57), S(  43,  -41), S( -56,  -55), S(  40,  -86), S(   0,  -60), S( 123,  -94), S(  83, -113),
  S(  -6,  -36), S(   5,  -29), S(   3,   -9), S( -32,    1), S( -22,    4), S(  34,   -9), S(  86,  -40), S(  85,  -62),
  S( -21,  -46), S(   0,  -24), S( -20,   -1), S( -28,   16), S( -41,   20), S( -21,   14), S(  11,  -16), S( -47,  -28),
  S( -19,  -21), S( -27,   -6), S( -22,   12), S( -20,   22), S( -18,   26), S( -37,   25), S( -36,    0), S( -55,  -35),
  S( -13,   -5), S(  -2,   27), S(  -1,   37), S(  -3,   40), S(  -7,   49), S(   2,   58), S( -10,   36), S( -24,   -7),
  S(   0,   16), S(   3,   31), S(   6,   51), S(   7,   49), S(   8,   55), S(  13,   78), S(  12,   58), S(  -1,   23),
  S(   0,   -3), S(   4,   20), S(   5,   25), S(   7,   21), S(   8,   28), S(  10,   43), S(   3,   28), S(   0,    5),
  S(  -1,   -9), S(   0,   -7), S(   1,    6), S(   0,    2), S(   1,    5), S(   2,    3), S(   0,    1), S(   0,    0),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
