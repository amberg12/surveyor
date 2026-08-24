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
#include "score.h"

namespace surveyor::evaluation_constants {
constexpr std::pair<score, score> pawn_material = {75, 162};
constexpr std::pair<score, score> knight_material = {296, 259};
constexpr std::pair<score, score> bishop_material = {332, 287};
constexpr std::pair<score, score> rook_material = {425, 411};
constexpr std::pair<score, score> queen_material = {761, 552};
}  // namespace surveyor::evaluation_constants
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
