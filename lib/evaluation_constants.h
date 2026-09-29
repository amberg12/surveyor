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
inline const pair pawn_material = S(134, 254);
inline const pair knight_material = S(559, 665);
inline const pair bishop_material = S(573, 741);
inline const pair rook_material = S(779, 1230);
inline const pair queen_material = S(1671, 1962);

inline const pair bishop_pair = S(117, 146);

inline const std::array knight_mobility = {
  S(-51, -76), S(-15, -37), S(-2, -18), S(4, 0), S(10, 14), S(13, 28), S(11, 29), S(10, 32), S(18, 27),
};
inline const std::array bishop_mobility = {
  S(-65, -88), S(-34, -49), S(-15, -23), S(-4, -15), S(3, 3), S(10, 14), S(10, 22), S(14, 22), S(19, 26), S(18, 34), S(27, 18), S(24, 19), S(-7, -5), S(0, 22),
};
inline const std::array rook_mobility = {
  S(-78, -76), S(-55, -43), S(-41, -28), S(-28, -9), S(-30, -3), S(-12, 1), S(-3, 8), S(2, 10), S(15, 14), S(27, 19), S(32, 23), S(34, 27), S(43, 30), S(54, 6), S(39, 19),
};
inline const std::array queen_mobility = {
  S(-34, -65), S(-28, -65), S(-21, -80), S(-10, -73), S(-6, -61), S(-1, -50), S(0, -35), S(5, -14), S(7, 6), S(6, 20), S(11, 33), S(14, 49), S(15, 50), S(10, 58), S(14, 59), S(7, 71), S(20, 62), S(22, 59), S(28, 54), S(35, 42), S(36, 33), S(28, 34), S(11, 9), S(-3, -2), S(-28, -34), S(-37, -41), S(-52, -61), S(-53, -62),
};

inline const pair pawn_threat_knight = S(83, 40);
inline const pair pawn_threat_bishop = S(87, 52);
inline const pair pawn_threat_rook = S(62, 45);
inline const pair pawn_threat_queen = S(48, 4);

inline const pair knight_threat_pawn = S(-16, 17);
inline const pair knight_threat_bishop = S(55, 47);
inline const pair knight_threat_rook = S(106, 12);
inline const pair knight_threat_queen = S(47, -9);

inline const pair bishop_threat_pawn = S(-9, 8);
inline const pair bishop_threat_knight = S(33, 27);
inline const pair bishop_threat_rook = S(84, 40);
inline const pair bishop_threat_queen = S(78, 26);

inline const std::array passed_pawn = {
  S(-27, -105), S(-41, -94), S(-51, -2), S(-8, 80), S(53, 144), S(147, 279),
};
inline const std::array defended_passed_pawn = {
  S(10, -7), S(14, 26), S(29, 38), S(15, 73), S(50, 103), S(69, 191),
};
inline const std::array blocked_passed_pawn = {
  S(0, -13), S(8, -3), S(-11, -15), S(-19, -33), S(-20, -63), S(-42, -167),
};
inline const std::array friendly_passer_tropism = {
  S(5, 70), S(5, 63), S(12, 39), S(6, 31), S(11, 34), S(23, 37), S(6, 25),
};
inline const std::array enemy_passer_tropism = {
  S(-46, -46), S(8, 34), S(22, 52), S(30, 60), S(27, 65), S(22, 63), S(7, 71),
};

inline const pair isolated_pawn = S(-6, -9);
inline const std::array defended_pawn = {
  S(22, 19), S(30, 14), S(29, 32), S(89, 81), S(69, 119),
};
inline const std::array phalanx = {
  S(7, -11), S(15, 5), S(31, 42), S(81, 91), S(52, 94), S(9, 31),
};

inline const std::array shelter_centre = {
  S(-19, -6), S(12, -9), S(0, -5), S(1, -11), S(-6, -2), S(4, 2), S(8, 32),
};
inline const std::array shelter_mid = {
  S(-27, -13), S(18, -14), S(9, -10), S(10, -10), S(1, -5), S(-12, 8), S(-1, 46),
};
inline const std::array shelter_edge = {
  S(-40, -19), S(27, -35), S(25, -23), S(13, -18), S(-13, -2), S(-19, 28), S(7, 72),
};

inline const std::array storm_centre = {
  S(-19, -6), S(12, -9), S(0, -5), S(1, -11), S(-6, -2), S(4, 2), S(8, 32),
};
inline const std::array storm_mid = {
  S(-27, -13), S(18, -14), S(9, -10), S(10, -10), S(1, -5), S(-12, 8), S(-1, 46),
};
inline const std::array storm_edge = {
  S(-13, -17), S(47, 65), S(-23, 23), S(-13, -3), S(-5, -19), S(6, -24), S(2, -23),
};

inline const std::array king_ring = {
  S(-37, 14), S(-32, 15), S(-26, 0), S(-26, 7), S(-5, -84),
};

inline const std::array pawn_psqt = {
  S( -59,   -4), S( -17,   -4), S( -37,  -10), S( -46,  -14), S( -44,    6), S(   7,  -25), S(  55,  -60), S( -43,  -59),
  S( -54,  -29), S( -40,  -20), S( -28,  -47), S( -43,  -38), S( -35,  -35), S( -63,  -41), S(  17,  -81), S( -40,  -78),
  S( -63,  -10), S( -49,  -21), S( -21,  -46), S(  -7,  -64), S( -20,  -66), S( -30,  -56), S( -22,  -51), S( -50,  -58),
  S( -51,   10), S(   6,   -8), S( -15,  -28), S(  17,  -59), S(  19,  -63), S(   5,  -58), S(  22,  -39), S( -33,  -41),
  S( -18,   73), S(  18,   67), S(  53,   31), S(  78,   -1), S(  65,   -6), S(  55,   -9), S(  30,   47), S(  -8,   41),
  S( 105,  170), S( 109,  164), S(  95,  141), S(  94,  115), S(  75,   82), S(  14,   64), S(  -9,  107), S(   9,  121),
};
inline const std::array knight_psqt = {
  S( -40,  -27), S( -51,  -42), S( -41,  -26), S( -29,  -21), S( -33,  -18), S(  -2,  -29), S( -40,  -28), S( -28,  -37),
  S( -48,  -31), S( -40,  -25), S( -32,  -10), S(  -9,    7), S(  11,    2), S(   9,  -21), S( -14,  -17), S( -14,  -26),
  S( -65,  -17), S( -22,    6), S(  -4,   13), S(  17,   38), S(  27,   22), S(  35,    9), S(  40,   -8), S( -30,  -23),
  S( -33,   -1), S(  -1,   11), S(  19,   36), S(  36,   41), S(  48,   45), S(  51,   18), S(  41,   13), S(   9,  -16),
  S(  -4,   13), S(  16,   19), S(  29,   44), S(  80,   51), S(  39,   57), S( 115,   27), S(  29,   27), S(  56,    0),
  S( -25,  -15), S(  -2,   16), S(  40,   34), S(  67,   32), S(  69,   27), S(  65,   46), S(  24,   15), S(   6,   -2),
  S( -67,  -19), S( -40,   -3), S(   3,   -1), S(  30,   20), S(  16,    4), S(  27,    3), S( -33,  -20), S(  -7,  -28),
  S(-144,  -68), S( -24,  -19), S( -41,  -15), S(  -5,    2), S(   0,  -10), S( -51,  -25), S(  -8,   -9), S( -24,  -39),
};
inline const std::array bishop_psqt = {
  S( -13,  -38), S( -13,  -34), S( -13,  -22), S( -17,  -15), S( -17,  -32), S( -30,    0), S( -12,  -24), S(  -4,   -9),
  S(   9,  -23), S(   7,  -10), S(  10,   -9), S( -16,    9), S(  13,   -4), S(  18,  -20), S(  59,  -19), S(  -3,  -19),
  S( -15,   -9), S(  19,    9), S(  17,   22), S(   5,   12), S(   6,   46), S(  26,    8), S(  21,   -8), S(   6,   -6),
  S( -16,  -12), S( -21,   21), S(  15,   24), S(  26,   51), S(  38,   20), S(  13,   19), S(   6,   -1), S(  -7,  -21),
  S( -19,    3), S( -13,   18), S(  -2,   26), S(  59,   30), S(  25,   37), S(  16,   12), S(   2,    9), S(  -6,  -13),
  S( -20,  -14), S(   1,   20), S(   0,   18), S(  29,    5), S(  53,   18), S(  52,   38), S(  43,   21), S(  13,  -13),
  S( -37,   -4), S( -29,    7), S(  -7,   -1), S( -21,  -10), S( -27,   -1), S(   2,    0), S( -20,   -6), S( -37,  -26),
  S( -14,   -9), S( -16,   -3), S( -33,  -17), S( -19,  -13), S( -19,   -2), S( -54,  -13), S( -10,  -14), S(   0,   -7),
};
inline const std::array rook_psqt = {
  S( -31,  -29), S( -21,  -30), S(  -4,  -21), S(  10,  -32), S(  23,  -53), S(  16,  -49), S( -25,  -17), S(  -9,  -71),
  S( -73,  -18), S( -46,  -23), S( -36,  -11), S( -23,  -29), S( -23,  -38), S(   6,  -48), S(   0,  -47), S( -88,  -47),
  S( -58,    0), S( -43,   -2), S( -35,    5), S( -30,  -17), S( -22,  -22), S(  -9,  -28), S(  16,  -33), S( -17,  -38),
  S( -47,   11), S( -45,   13), S( -25,    9), S(  -2,   -7), S( -16,  -17), S(  -8,  -12), S( -10,  -14), S( -26,  -32),
  S( -39,   38), S( -30,   28), S(   0,   27), S(  11,   16), S(  12,   -5), S(  28,    4), S(  11,   -7), S(  -1,    0),
  S( -19,   46), S(  14,   33), S(  12,   36), S(  33,   20), S(  59,    7), S(  62,   18), S(  34,   22), S(   9,    3),
  S(  -7,   53), S(  -6,   58), S(  38,   48), S(  58,   40), S(  48,   33), S(  80,   20), S(  32,   38), S(  62,   22),
  S(  18,   12), S(  20,   17), S(  19,   21), S(  33,   21), S(  34,    9), S(  13,   23), S(  23,   23), S(  41,   17),
};
inline const std::array queen_psqt = {
  S( -30,  -29), S( -25,  -34), S( -10,  -37), S(  12,  -40), S( -20,  -43), S( -64,  -63), S( -42,  -42), S( -41,  -36),
  S( -40,  -31), S( -25,  -12), S(  -5,  -13), S(   0,  -13), S(   8,  -14), S(   5,  -36), S(  -2,  -42), S( -31,  -31),
  S( -35,  -26), S( -13,   -5), S( -15,   11), S(  -8,    8), S(  -4,   41), S(  13,    8), S(  22,    0), S(  -8,  -15),
  S( -25,    2), S( -34,    0), S( -11,   17), S(  -7,   55), S(  12,   36), S(   1,   30), S(  18,   11), S(  -6,    0),
  S( -24,    1), S( -20,   41), S(  -4,   26), S(  -1,   62), S(  25,   55), S(  30,   24), S(  21,   43), S(  21,  -20),
  S( -18,   -7), S(  -4,   16), S(  10,   26), S(   9,   34), S(  42,   29), S(  65,   30), S(  65,   22), S(  32,   -9),
  S( -26,  -18), S( -30,   20), S(   0,   27), S(   2,   30), S(   6,   17), S(  55,   15), S(  48,   16), S(  81,    1),
  S( -26,  -46), S(  -9,  -21), S(   3,  -17), S(  -2,  -16), S(   7,  -12), S(  21,    4), S(  12,  -15), S(  23,  -16),
};
inline const std::array king_psqt = {
  S( -30,  -49), S(  17,  -64), S(  41,  -41), S( -56,  -58), S(  42,  -88), S(  -3,  -60), S( 120,  -94), S(  83, -117),
  S(  -5,  -43), S(   3,  -32), S(   2,   -7), S( -33,    1), S( -20,    7), S(  34,   -8), S(  90,  -37), S(  83,  -65),
  S( -24,  -51), S(   1,  -17), S( -23,    0), S( -33,   20), S( -46,   26), S( -20,   12), S(  14,  -15), S( -45,  -31),
  S( -19,  -22), S( -18,   -9), S( -26,   20), S( -20,   23), S( -19,   30), S( -36,   29), S( -36,    0), S( -55,  -30),
  S( -12,   -5), S(   0,   31), S(   1,   38), S(   0,   39), S(  -3,   51), S(   0,   64), S(  -5,   43), S( -26,  -11),
  S(   0,   10), S(   1,   29), S(   7,   54), S(   8,   47), S(  10,   58), S(  12,   82), S(  10,   60), S(   0,   21),
  S(  -2,   -8), S(   3,   14), S(   7,   32), S(   6,   23), S(   7,   24), S(   9,   41), S(   3,   30), S(   0,    0),
  S(  -1,   -8), S(   1,   -3), S(   1,    4), S(   0,    0), S(   1,    1), S(   2,    5), S(   0,    2), S(   0,   -4),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
