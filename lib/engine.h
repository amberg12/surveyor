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

#ifndef SURVEYOR_ENGINE_H
#define SURVEYOR_ENGINE_H
#include "engine_output.h"
#include "game.h"
#include "search.h"
#include "search_ctrls.h"

#include <memory>

namespace surveyor {
struct search_shared;
class engine {
public:
  engine();

  auto go(game g, ctrls::ctrls limits) -> void;
  auto stop() -> void;
  auto set_output(std::shared_ptr<engine_output> output) -> void;

private:
  std::shared_ptr<engine_output> m_output = std::make_unique<null_output>();

  std::unique_ptr<search_shared> m_shared;
  std::unique_ptr<worker>        m_searcher;
};

}  // namespace surveyor

#endif  // SURVEYOR_ENGINE_H
