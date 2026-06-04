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
#include "move_generation.hpp"

namespace surveyor {

class move_picker {
public:
  explicit move_picker(const position& pos)
      : m_pos(pos) {
  }

  auto next_move() -> move {
    switch (m_phase) {
    case phase::generate_moves: {
      const move_list all_moves = generate_moves(m_pos);

      for (const move mv : all_moves) {
        if (mv.is_noisy()) {
          m_noisy_moves.emplace_back(mv);
        } else {
          m_quiet_moves.emplace_back(mv);
        }
      }

      m_phase = phase::emit_noisy;
      [[fallthrough]];
    }
    case phase::emit_noisy: {
      if (m_noisy_idx < m_noisy_moves.size()) {
        return m_noisy_moves[m_noisy_idx++];
      }

      m_phase = phase::emit_quiet;
      [[fallthrough]];
    }
    case phase::emit_quiet: {
      if (m_quiet_idx < m_quiet_moves.size()) {
        return m_quiet_moves[m_quiet_idx++];
      }
    } break;
    }

    return move::null();
  }

private:
  enum class phase {
    generate_moves,
    emit_noisy,
    emit_quiet,
  };

  const position& m_pos;

  phase m_phase = phase::generate_moves;

  move_list m_noisy_moves;
  usize     m_noisy_idx = 0;

  move_list m_quiet_moves;
  usize     m_quiet_idx = 0;
};

}  // namespace surveyor
