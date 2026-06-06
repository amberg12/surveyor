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

  [[nodiscard]] auto is_repetition(const position& pos) const -> bool {
    for (i32 i = 0; i < m_keys.size() - 1; ++i) {
      if (pos.key() == m_keys[i]) {
        return true;
      }
    }

    return false;
  }
private:
  std::vector<z_key> m_keys;
};

}  // namespace surveyor