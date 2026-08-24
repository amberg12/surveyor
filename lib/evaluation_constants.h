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
constexpr std::pair<score, score> pawn_material = {68, 124};
constexpr std::pair<score, score> knight_material = {99, 214};
constexpr std::pair<score, score> bishop_material = {131, 277};
constexpr std::pair<score, score> rook_material = {173, 464};
constexpr std::pair<score, score> queen_material = {438, 575};
}  // namespace surveyor::evaluation_constants
#endif  // SURVEYOR_EVALUATION_CONSTANTS_H
