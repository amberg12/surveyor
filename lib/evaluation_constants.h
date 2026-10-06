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
inline const pair pawn_material = S(134, 262);
inline const pair knight_material = S(553, 683);
inline const pair bishop_material = S(568, 753);
inline const pair rook_material = S(756, 1233);
inline const pair queen_material = S(1647, 1987);

inline const pair bishop_pair = S(110, 148);

inline const std::array knight_mobility = {
  S(-54, -73), S(-16, -41), S(6, -23), S(3, -2), S(8, 16), S(11, 28), S(13, 29), S(11, 32), S(15, 33),
};
inline const std::array bishop_mobility = {
  S(-69, -94), S(-31, -59), S(-15, -30), S(-3, -19), S(0, 0), S(6, 12), S(6, 21), S(9, 30), S(18, 26), S(19, 35), S(24, 23), S(24, 30), S(2, 0), S(6, 24),
};
inline const std::array rook_mobility = {
  S(-67, -90), S(-48, -52), S(-37, -33), S(-27, -16), S(-28, -11), S(-13, -3), S(-6, 2), S(0, 6), S(15, 13), S(22, 19), S(25, 23), S(30, 33), S(41, 38), S(58, 21), S(34, 47),
};
inline const std::array queen_mobility = {
  S(-53, -67), S(-37, -67), S(-24, -85), S(-16, -73), S(-2, -60), S(0, -46), S(7, -37), S(6, -14), S(8, 2), S(10, 17), S(14, 30), S(9, 42), S(12, 41), S(15, 54), S(13, 57), S(14, 69), S(16, 64), S(19, 58), S(28, 61), S(29, 46), S(36, 39), S(28, 43), S(17, 11), S(7, 6), S(-25, -28), S(-35, -41), S(-51, -61), S(-52, -63),
};

inline const pair pawn_threat_knight = S(73, 23);
inline const pair pawn_threat_bishop = S(82, 37);
inline const pair pawn_threat_rook = S(56, 30);
inline const pair pawn_threat_queen = S(37, -12);

inline const pair pp_threat_knight = S(36, 13);
inline const pair pp_threat_bishop = S(18, 0);
inline const pair pp_threat_rook = S(6, 19);
inline const pair pp_threat_queen = S(23, -36);

inline const pair knight_threat_pawn = S(11, 31);
inline const pair knight_threat_bishop = S(59, 29);
inline const pair knight_threat_rook = S(91, -13);
inline const pair knight_threat_queen = S(35, -15);

inline const pair bishop_threat_pawn = S(6, 16);
inline const pair bishop_threat_knight = S(34, 25);
inline const pair bishop_threat_rook = S(77, 15);
inline const pair bishop_threat_queen = S(72, 22);

inline const pair rook_threat_pawn = S(-1, 37);
inline const pair rook_threat_knight = S(46, 24);
inline const pair rook_threat_bishop = S(55, 31);
inline const pair rook_threat_queen = S(76, -10);

inline const pair hanging = S(17, 44);

inline const std::array passed_pawn = {
  S(-32, -107), S(-48, -88), S(-56, 4), S(-14, 90), S(54, 156), S(166, 251),
};
inline const std::array defended_passed_pawn = {
  S(7, -8), S(13, 30), S(25, 39), S(9, 78), S(45, 110), S(50, 151),
};
inline const std::array blocked_passed_pawn = {
  S(-1, -10), S(9, -3), S(-12, -16), S(-21, -32), S(-15, -65), S(-28, -99),
};
inline const std::array friendly_passer_tropism = {
  S(14, 62), S(12, 59), S(15, 34), S(1, 30), S(2, 40), S(22, 43), S(0, 36),
};
inline const std::array enemy_passer_tropism = {
  S(-75, -41), S(9, 24), S(30, 46), S(38, 60), S(32, 63), S(20, 73), S(11, 80),
};

inline const pair isolated_pawn = S(-2, -6);
inline const std::array defended_pawn = {
  S(22, 12), S(24, 15), S(17, 26), S(83, 70), S(65, 114),
};
inline const std::array phalanx = {
  S(9, -8), S(20, 10), S(23, 42), S(79, 90), S(54, 93), S(8, 21),
};

inline const std::array shelter_centre = {
  S(-34, -10), S(42, -10), S(-21, 2), S(-1, -13), S(0, -2), S(5, 1), S(9, 33),
};
inline const std::array shelter_mid = {
  S(-63, -7), S(49, -21), S(26, -16), S(15, -16), S(0, 0), S(-18, 15), S(-10, 47),
};
inline const std::array shelter_edge = {
  S(-45, -4), S(30, -34), S(10, -10), S(9, -17), S(1, -6), S(0, 21), S(-4, 51),
};

inline const std::array king_ring = {
  S(-40, 14), S(-38, 12), S(-29, 4), S(-32, 10), S(-22, -86),
};

inline const std::array pawn_psqt = {
  S( -54,  -34), S(   9,  -31), S( -23,  -14), S( -59,   -3), S( -59,   -3), S( -29,  -14), S(   5,  -32), S( -53,  -32),
  S( -42,  -55), S( -21,  -52), S( -29,  -46), S( -37,  -31), S( -44,  -32), S( -30,  -48), S( -17,  -51), S( -48,  -51),
  S( -54,  -34), S( -33,  -30), S( -24,  -47), S( -15,  -62), S( -14,  -65), S( -24,  -43), S( -35,  -29), S( -54,  -29),
  S( -35,  -15), S(  15,  -21), S(  -1,  -39), S(  23,  -58), S(  21,  -61), S( -11,  -37), S(  14,  -15), S( -42,  -14),
  S(  -1,   51), S(  34,   54), S(  39,   22), S(  70,    2), S(  72,   10), S(  63,   21), S(  19,   71), S( -16,   60),
  S(  49,  109), S(  45,  109), S(  41,   80), S(  88,   76), S(  89,  103), S(  83,  119), S(  73,  137), S(  56,  113),
};
inline const std::array knight_psqt = {
  S( -40,  -33), S( -48,  -34), S( -19,  -28), S( -34,  -29), S( -36,   -9), S( -16,  -15), S( -51,  -36), S( -28,  -29),
  S( -15,  -25), S( -32,  -20), S( -17,   -6), S(   2,    6), S(   0,    6), S( -17,  -17), S( -30,  -19), S( -28,  -27),
  S( -53,  -23), S(  18,   -5), S(  16,    5), S(  23,   27), S(  23,   27), S(  20,   12), S(  12,   -4), S( -49,  -17),
  S(  -1,  -12), S(  17,    8), S(  31,   27), S(  46,   46), S(  44,   41), S(  43,   27), S(  27,   10), S( -12,   -2),
  S(  40,   -4), S(  24,   16), S(  61,   38), S(  49,   55), S(  45,   57), S(  69,   28), S(  15,   25), S(  44,    3),
  S(  -8,   -2), S(  19,   10), S(  32,   35), S(  51,   16), S(  47,   28), S(  45,   30), S(  12,   13), S(  -9,   -7),
  S( -17,  -18), S( -27,  -10), S(  13,    9), S(  21,   19), S(  22,   14), S(  17,    0), S( -32,  -11), S( -45,  -16),
  S( -88,  -59), S(  -8,  -18), S( -33,  -15), S(   2,    1), S(  -3,   -7), S( -42,  -18), S( -15,  -12), S( -94,  -53),
};
inline const std::array bishop_psqt = {
  S( -18,  -19), S( -11,  -34), S( -23,  -11), S( -21,  -12), S( -18,  -22), S( -20,   -2), S( -17,  -19), S(  -7,  -22),
  S(  -5,  -26), S(  29,  -19), S(  13,  -20), S(   1,   -3), S(   4,   -2), S(   7,   -9), S(  27,   -6), S(   1,  -16),
  S( -11,  -14), S(  22,    0), S(  11,   13), S(   2,   26), S(  -2,   30), S(  19,   12), S(   9,    5), S( -11,    3),
  S(  -3,  -23), S(  -6,    2), S(  12,   22), S(  24,   26), S(  24,   33), S(  16,   11), S(  -5,   13), S(  -6,   -9),
  S(   0,   -6), S(   4,   11), S(   9,   21), S(  29,   39), S(  40,   24), S(  13,   21), S(   3,   12), S(   0,   -6),
  S(  11,  -10), S(  32,    7), S(   9,   31), S(  39,    5), S(  31,   15), S(  20,   22), S(  30,   14), S(  11,   -6),
  S( -35,   -6), S( -41,   11), S(   7,   -4), S( -14,   -7), S( -21,   -2), S(  -3,    0), S( -12,  -14), S( -27,  -12),
  S( -20,    3), S( -10,   -7), S( -38,  -10), S( -14,    1), S( -16,  -11), S( -42,  -21), S( -13,   -8), S( -16,  -10),
};
inline const std::array rook_psqt = {
  S( -19,  -26), S(  -9,  -22), S(  13,  -24), S(  25,  -34), S(  24,  -34), S(  15,  -22), S( -11,  -20), S( -19,  -34),
  S( -69,  -23), S( -17,  -22), S(  -6,  -16), S( -16,  -21), S( -19,  -23), S( -13,  -17), S( -28,  -28), S( -79,  -13),
  S( -28,  -19), S(  -6,  -13), S( -15,   -7), S( -13,  -14), S( -21,  -12), S( -17,   -3), S(  -6,  -11), S( -35,  -13),
  S( -33,   -6), S( -27,    0), S( -10,   -3), S(  -3,  -13), S(  -6,   -7), S( -14,   -1), S( -20,    0), S( -40,   -3),
  S( -11,   13), S(  -2,    7), S(  20,    6), S(  16,   -2), S(  12,   -2), S(  11,    8), S( -14,   11), S( -23,   16),
  S(  -4,   22), S(  25,   14), S(  32,   12), S(  42,    2), S(  39,    2), S(  24,   15), S(  10,   17), S( -11,   20),
  S(   5,   28), S(   5,   36), S(  44,   24), S(  39,   21), S(  49,   17), S(  36,   20), S(  -6,   41), S(   8,   31),
  S(  29,    8), S(  17,   18), S(  20,   16), S(  32,   11), S(  38,   20), S(  19,   21), S(  11,   17), S(  15,   16),
};
inline const std::array queen_psqt = {
  S( -23,  -31), S( -32,  -32), S( -22,  -52), S(   5,  -26), S(  15,  -41), S( -19,  -40), S( -25,  -42), S( -31,  -28),
  S( -34,  -25), S( -15,  -27), S(   0,  -26), S(   1,    0), S(   6,   -8), S(   3,  -21), S( -13,  -26), S( -28,  -33),
  S( -22,  -23), S(  -2,    4), S(   2,    8), S( -11,   25), S(  -3,   25), S(   1,   10), S(   1,   -1), S( -27,  -16),
  S( -21,    7), S(   7,   -9), S(   0,   24), S(   4,   38), S(  -2,   35), S(   4,   17), S(   6,   12), S( -10,   -1),
  S(  24,  -22), S(  11,   32), S(  18,   12), S(  16,   51), S(   2,   58), S(   9,   22), S(  10,   39), S(  16,  -19),
  S(   5,  -10), S(  36,    8), S(  21,   25), S(  18,   33), S(  19,   34), S(  24,   33), S(  20,   14), S(   3,   -5),
  S(  17,  -15), S( -19,   15), S(  13,   19), S(  -2,   24), S(   2,   24), S(  16,   23), S( -24,   10), S(  13,  -11),
  S(  -6,  -30), S(   3,  -10), S(   9,    0), S(  12,   -5), S(  -3,  -11), S(   7,   -2), S(  -7,  -15), S(  -1,  -17),
};
inline const std::array king_psqt = {
  S(  62, -115), S( 114,  -94), S(   5,  -55), S(  37,  -93),
  S(  80,  -70), S(  71,  -40), S(  23,  -12), S( -28,    6),
  S( -57,  -35), S(   5,  -22), S( -24,    9), S( -47,   20),
  S( -68,  -36), S( -58,   -1), S( -54,   21), S( -35,   26),
  S( -37,   -8), S( -18,   39), S(  -8,   54), S( -16,   50),
  S(  -4,   28), S(   7,   58), S(  10,   80), S(   7,   64),
  S(   0,    2), S(   4,   37), S(  11,   48), S(  12,   35),
  S(   0,   -7), S(   0,   -4), S(   2,    7), S(   1,    5),
};
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
