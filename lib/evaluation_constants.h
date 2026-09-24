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
inline const pair pawn_material = S(144, 244);
inline const pair knight_material = S(501, 574);
inline const pair bishop_material = S(540, 670);
inline const pair rook_material = S(727, 1114);
inline const pair queen_material = S(1589, 1942);

inline const std::array pawn_psqt = {
  S(-56, -9),  S(-25, -21), S(-43, -15), S(-44, -19), S(-34, 12),  S(15, -25),  S(54, -62),  S(-47, -61),
  S(-58, -25), S(-35, -30), S(-22, -42), S(-22, -37), S(-22, -30), S(-53, -33), S(25, -79),  S(-38, -64),
  S(-69, -1),  S(-44, -6),  S(-16, -37), S(-6, -60),  S(-16, -65), S(-21, -50), S(-21, -45), S(-60, -41),
  S(-55, 27),  S(6, 0),     S(-11, -25), S(15, -50),  S(20, -57),  S(-6, -55),  S(19, -37),  S(-47, -35),
  S(-16, 85),  S(19, 82),   S(64, 41),   S(90, 1),    S(76, -20),  S(68, -10),  S(43, 51),   S(0, 42),
  S(111, 183), S(118, 185), S(106, 155), S(96, 116),  S(80, 88),   S(17, 76),   S(1, 121),   S(-8, 130),
};


inline const std::array knight_psqt = {
  S(-35, -13),  S(-49, -38), S(-39, -19), S(-29, -20), S(-23, -11), S(-1, -28),  S(-31, -28), S(-23, -26),
  S(-42, -21),  S(-37, -18), S(-32, -4),  S(-6, 16),   S(20, 16),   S(0, -14),   S(-18, -14), S(-8, -21),
  S(-77, -15),  S(-28, 5),   S(-16, 42),  S(16, 54),   S(30, 32),   S(31, 16),   S(39, 0),    S(-37, -21),
  S(-39, 5),    S(-5, 24),   S(15, 61),   S(33, 60),   S(48, 60),   S(44, 45),   S(35, 18),   S(10, -15),
  S(-3, 17),    S(5, 36),    S(26, 68),   S(84, 71),   S(52, 73),   S(135, 37),  S(53, 42),   S(75, 0),
  S(-19, -11),  S(23, 22),   S(53, 57),   S(101, 50),  S(124, 36),  S(89, 61),   S(85, 15),   S(21, 7),
  S(-58, -14),  S(-33, -2),  S(34, 3),    S(61, 26),   S(33, 11),   S(62, 8),    S(-23, -15), S(12, -22),
  S(-138, -59), S(-18, -12), S(-33, -10), S(2, 10),    S(11, -5),   S(-44, -18), S(-1, -2),   S(-17, -33),
};

inline const std::array bishop_psqt = {
  S(-11, -24), S(-5, -20), S(-4, -19), S(-12, -4), S(-18, -24), S(-37, 1),  S(-6, -15), S(-4, 2),
  S(16, -10),  S(11, -2),  S(18, 0),   S(-27, 18), S(11, 5),    S(14, -12), S(57, -7),  S(0, -9),
  S(1, 6),     S(22, 21),  S(19, 35),  S(8, 27),   S(10, 60),   S(31, 17),  S(15, 2),   S(13, 5),
  S(-5, -1),   S(-7, 30),  S(25, 44),  S(44, 67),  S(48, 33),   S(10, 30),  S(2, 9),    S(5, -14),
  S(-14, 6),   S(-6, 29),  S(12, 35),  S(75, 45),  S(43, 51),   S(29, 26),  S(24, 19),  S(5, -4),
  S(-15, -4),  S(4, 30),   S(15, 29),  S(51, 10),  S(72, 27),   S(75, 55),  S(61, 28),  S(37, -1),
  S(-33, 2),   S(-10, 13), S(-7, 2),   S(-16, 0),  S(5, 18),    S(16, 12),  S(4, 3),    S(-25, -16),
  S(-6, 0),    S(-12, 3),  S(-28, -10), S(-12, 0), S(-8, 10),   S(-47, -2), S(-3, -4),  S(5, 2),
};

inline const std::array rook_psqt = {
  S(-19, -10), S(-20, -9),  S(14, 2),   S(11, -12), S(39, -33), S(36, -28), S(-21, -2), S(-5, -51),
  S(-61, 0),   S(-38, -4),  S(-29, 5),  S(-14, -19), S(-9, -16), S(15, -29), S(19, -29), S(-72, -30),
  S(-54, 15),  S(-52, 13),  S(-28, 19), S(-21, 1),  S(-13, -10), S(-6, -15), S(31, -15), S(-8, -28),
  S(-46, 30),  S(-39, 33),  S(-25, 23), S(-1, 5),   S(-15, -1),  S(2, -2),   S(1, 2),    S(-10, -12),
  S(-39, 58),  S(-24, 55),  S(-1, 45),  S(9, 34),   S(15, 13),   S(41, 20),  S(27, 9),   S(18, 17),
  S(-14, 66),  S(22, 52),   S(13, 50),  S(42, 38),  S(68, 27),   S(81, 40),  S(51, 37),  S(28, 20),
  S(9, 65),    S(9, 77),    S(61, 69),  S(77, 62),  S(70, 51),   S(104, 39), S(56, 54),  S(90, 41),
  S(37, 21),   S(36, 31),   S(36, 36),  S(53, 40),  S(53, 26),   S(28, 43),  S(40, 35),  S(63, 36),
};

inline const std::array queen_psqt = {
  S(-13, -8),  S(-12, -18), S(3, -32),  S(37, -60),  S(-11, -39), S(-57, -47), S(-22, -17), S(-23, -12),
  S(-25, -13), S(-12, 0),   S(17, -12), S(7, -23),   S(29, -32),  S(19, -20),  S(9, -22),   S(-13, -5),
  S(-20, -13), S(0, -1),    S(1, 25),   S(10, 17),   S(13, 40),   S(26, 25),   S(31, 24),   S(13, 8),
  S(-20, -3),  S(-13, 13),  S(8, 30),   S(-3, 79),   S(14, 53),   S(18, 73),   S(37, 52),   S(5, 43),
  S(-2, 6),    S(-15, 38),  S(15, 42),  S(12, 85),   S(45, 109),  S(56, 87),   S(37, 104),  S(54, 58),
  S(-9, 2),    S(2, 24),    S(25, 41),  S(30, 68),   S(80, 90),   S(132, 113), S(125, 98),  S(97, 74),
  S(-3, 8),    S(-11, 50),  S(26, 60),  S(28, 70),   S(62, 78),   S(113, 87),  S(92, 64),   S(125, 54),
  S(5, -1),    S(26, 24),   S(48, 34),  S(46, 48),   S(70, 62),   S(79, 68),   S(62, 38),   S(70, 43),
};

inline const std::array king_psqt = {
  S(-14, -47), S(47, -75),  S(81, -52), S(-31, -66), S(72, -110), S(23, -82), S(167, -118), S(131, -135),
  S(6, -44),   S(7, -36),   S(4, -13),  S(-47, -4),  S(-43, 5),   S(33, -14), S(81, -47),   S(116, -81),
  S(-23, -53), S(-12, -21), S(-52, 2),  S(-65, 26),  S(-87, 29),  S(-70, 26), S(-19, -19),  S(-38, -32),
  S(-20, -23), S(-23, -4),  S(-37, 32), S(-31, 37),  S(-35, 37),  S(-61, 38), S(-53, 6),    S(-52, -24),
  S(-10, -9),  S(-2, 35),   S(0, 48),   S(-1, 45),   S(-4, 66),   S(-2, 83),  S(-8, 52),    S(-23, -6),
  S(0, 11),    S(1, 35),    S(9, 61),   S(9, 50),    S(11, 65),   S(12, 90),  S(12, 68),    S(0, 22),
  S(0, -10),   S(4, 14),    S(9, 34),   S(6, 26),    S(7, 26),    S(9, 43),   S(3, 30),     S(0, -1),
  S(-1, -12),  S(1, -4),    S(1, 3),    S(0, -1),    S(0, 0),     S(1, 3),    S(0, 1),      S(0, -6),
};

inline const pair bishop_pair = S(55, 87);

inline const std::array knight_mobility = {
  S(7, -10), S(48, 35), S(52, 49), S(65, 74), S(62, 87), S(63, 89), S(65, 85), S(64, 89), S(70, 72),
};

inline const std::array bishop_mobility = {
  S(-37, -50), S(4, 0),   S(24, 24), S(30, 31), S(37, 48), S(46, 58), S(52, 80), S(50, 71), S(63, 80), S(52, 76), S(77, 73), S(67, 65), S(31, 42), S(38, 66),
};

inline const std::array rook_mobility = {
  S(-34, -3), S(-13, 33), S(5, 47),  S(10, 71), S(14, 76),  S(31, 75), S(37, 78), S(53, 87), S(63, 84),  S(83, 95),  S(78, 85), S(91, 96), S(97, 99),  S(111, 90), S(96, 95),
};

inline const std::array queen_mobility = {
  S(38, 1),   S(21, -1),  S(28, -15), S(39, -13), S(38, -3),  S(43, 8),   S(45, 19), S(61, 42),  S(50, 61),  S(64, 76),  S(73, 93),  S(69, 111), S(62, 112), S(68, 130), S(63, 126), S(65, 145), S(69, 137), S(83, 137), S(85, 130), S(95, 123), S(101, 119), S(94, 121), S(80, 95), S(65, 85),  S(37, 45),  S(25, 35),  S(6, 8), S(5, 8),
};

inline const std::array passed_pawn = {
  S(0, 0), S(3, 11), S(-5, 3), S(-9, 83), S(17, 142), S(66, 205), S(126, 316), S(0, 0),
};

inline const std::array defended_passed_pawn = {
  S(0, 0), S(0, 0), S(8, 0), S(13, 48), S(28, 63), S(12, 107), S(54, 141), S(71, 222),
};

inline const pair isolated_pawn = S(-10, -3);

inline const std::array defended_pawn = {
  S(0, 0), S(0, 0), S(4, 25), S(12, 12), S(22, 19), S(89, 71), S(68, 112), S(0, 0),
};

inline const std::array shelter_centre = {
  S(-27, -10), S(22, -3), S(14, 0), S(-7, 11), S(-6, -3), S(2, 6), S(1, 0), S(0, 0),
};

inline const std::array shelter_mid = {
  S(-45, -20), S(60, -20), S(2, -5), S(-29, 8), S(0, 12), S(5, 9), S(6, 16), S(0, 0),
};

inline const std::array shelter_edge = {
  S(-31, -15), S(47, -18), S(7, 4), S(-23, 5), S(-4, 4), S(2, 14), S(2, 3), S(0, 0),
}
;
}
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
