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

#include "engine.h"

#include "move_generation.h"

namespace surveyor {

auto engine::go(game g, search_limits limits) -> void {
  move_list moves = generate_moves(g.root());

  line pv;
  pv.emplace_back(moves[0]);

  m_output->info({.pv = pv});
  m_output->best_move(pv[0]);
}

auto engine::set_output(std::unique_ptr<engine_output> output) -> void {
  m_output = std::move(output);
}

}  // namespace surveyor
