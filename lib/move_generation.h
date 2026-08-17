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

#ifndef SURVEYOR_MOVE_GENERATION_H
#define SURVEYOR_MOVE_GENERATION_H

#include "move.h"
#include "position.h"
#include "util/static_vector.h"

namespace surveyor {

using move_list = static_vector<move, 256>;

auto generate_moves(const position& pos) -> move_list;

}  // namespace surveyor

#endif  // SURVEYOR_MOVE_GENERATION_H
