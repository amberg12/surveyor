/*
  Surveyor - A UCI chess engine.
  Copyright (C) 2026 Amber Goulding

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once
#include "position.hpp"

namespace surveyor {

class repetition_table {
public:
  auto push(const position& pos) -> void {
    m_keys.emplace_back(pos.key());
  }

  auto pop() -> void {
    m_keys.pop_back();
  }

  auto set_uci_moves() -> void {
    m_uci_moves = m_keys.size();
  }

  [[nodiscard]] auto is_repetition(const position& pos) const -> bool {
    i32 times_position_found = 0;

    for (i32 i = m_keys.size() - 3; i >= 0; i -= 2) {
      times_position_found += m_keys[i] == pos.key();

      if (times_position_found == 1 && i >= m_uci_moves) {
        return true;
      }

      if (times_position_found == 2) {
        return true;
      }
    }

    return false;
  }

private:
  usize m_uci_moves = 0;

  std::vector<z_key> m_keys;
};

}  // namespace surveyor