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

engine::engine() {
  m_shared   = std::make_unique<search_shared>();
  m_searcher = std::make_unique<worker>(*m_shared);

  m_searcher->launch();
}

engine::~engine() {
  m_shared->halt();
  m_shared->message = engine_message::destroy;
}

auto engine::go(game g, ctrls::ctrls limits) -> void {
  m_shared->tt.age();

  m_shared->g     = g;
  m_shared->ctrls = limits;

  m_shared->stopped = false;
  m_shared->message = engine_message::go;
}

auto engine::stop() -> void {
  m_shared->halt();
}

auto engine::set_output(std::shared_ptr<engine_output> output) -> void {
  m_output         = output;
  m_shared->output = output;
}

auto engine::reset() -> void {
  m_shared->tt.clear();
  m_searcher->reset();
}

auto engine::await() -> void {
  while (m_shared->message == engine_message::go) {

  }
}

}  // namespace surveyor
