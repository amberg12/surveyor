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
#include "transposition_table.hpp"
#include "util/integer.hpp"
#include "util/multi_array.hpp"

namespace surveyor {
constexpr std::array conthist_plies = {1, 2};
constexpr i16        history_max    = 16384;

namespace history_detail {
static_assert(history_max < std::numeric_limits<i16>::max());
static_assert(-history_max > std::numeric_limits<i16>::min());

constexpr auto gravity(i16& value, i32 bonus) {
  i16 clamped_bonus =
    std::clamp(static_cast<i16>(bonus), static_cast<i16>(-history_max), history_max);

  value += static_cast<i16>(clamped_bonus - std::abs(clamped_bonus) * value / history_max);
}
}  // namespace history_detail

constexpr auto bonus(i32 depth) -> i32 {
  return std::clamp(320 * depth - 400, 0, 2400);
}

constexpr auto malus(i32 depth) -> i32 {
  return -std::clamp(240 * depth - 400, 0, 1200);
}

class piece_to_history {
public:
  auto read(const position& pos, move m) -> i16 {
    return entry(pos, m);
  }

  auto write(const position& pos, move m, i32 score) -> void {
    i16& e = entry(pos, m);
    history_detail::gravity(e, score);
  }

private:
  auto entry(const position& pos, move m) -> i16& {
    const auto [stm, ptype] = pos.piece_at(m.src());
    return m_piece_to_history[pos.stm().idx()][ptype.compressed_idx()][m.dst().idx];
  }

  multi_array_t<i16, 2, 6, 64> m_piece_to_history{};
};

class continuation_history {
public:
  auto read(const position& pos, move m) -> piece_to_history* {
    return entry(pos, m);
  }

private:
  auto entry(const position& pos, move m) -> piece_to_history* {
    const auto [stm, ptype] = pos.piece_at(m.src());
    return &m_conthist_tables[pos.stm().idx()][ptype.compressed_idx()][m.dst().idx];
  }

  multi_array_t<piece_to_history, 2, 6, 64> m_conthist_tables;
};

class capture_history {
public:
  auto read(const position& pos, move m) -> i16 {
    return m.is_capture() ? entry(pos, m) : 0;
  }

  auto write(const position& pos, move m, i32 score) -> void {
    if (!m.is_capture()) {
      return;
    }

    i16& e = entry(pos, m);
    history_detail::gravity(e, score);
  }

private:
  auto entry(const position& pos, move m) -> i16& {
    const piece_type victim   = m.is_en_passant() ? piece_type::pawn() : pos.ptype_at(m.dst());
    const piece_type attacker = pos.ptype_at(m.src());

    return m_capture_history[pos.stm().idx()][attacker.compressed_idx()][m.dst().idx]
                            [victim.compressed_idx()];
  }

  multi_array_t<i16, 2, 6, 64, 6> m_capture_history{};
};

}  // namespace surveyor
