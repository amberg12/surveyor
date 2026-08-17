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

#ifndef SURVEYOR_ENGINE_OUTPUT_H
#define SURVEYOR_ENGINE_OUTPUT_H
#include "move.h"

namespace surveyor {

struct info_line {
  line pv;
};

class engine_output {
public:
  virtual ~engine_output() = default;

  virtual auto info(info_line info) -> void = 0;
  virtual auto best_move(move mv) -> void   = 0;
};

class null_output : public engine_output {
public:
  auto info(info_line info) -> void override {
    (void)info;
  }

  auto best_move(move mv) -> void override {
    (void)mv;
  }
};

}  // namespace surveyor

#endif  // SURVEYOR_ENGINE_OUTPUT_H
