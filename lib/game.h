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

#ifndef SURVEYOR_GAME_H
#define SURVEYOR_GAME_H
#include "position.h"
#include "repetition_table.h"

namespace surveyor {

class game {
public:
  explicit game(const position& root);

  auto add_move(move mv) -> void;
  auto set_uci_line() -> void;

  auto root() const -> const position&;
  auto repetition_table() const -> repetition_table;

private:
  position               m_root;
  class repetition_table m_repetition_table;
};

}  // namespace surveyor

#endif  // SURVEYOR_GAME_H
