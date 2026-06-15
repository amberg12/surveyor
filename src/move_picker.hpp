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
  move_picker(const position& pos, move tt_move, piece_to_history& piece_to)
      : m_pos(pos)
      , m_tt_move(tt_move)
      , m_piece_to(piece_to) {
  }

  auto skip_quiet() -> void {
    m_skip_quiet = true;
  }

  auto next_move() -> move {
    const auto next_move = [&](move_list& ml, std::array<i32, 256>& scores, usize& idx) -> move {
      usize best_idx   = idx;
      i32   best_score = scores[idx];

      for (usize i = idx; i < ml.size(); ++i) {
        if (scores[i] > best_score) {
          best_idx   = i;
          best_score = scores[i];
        }
      }

      std::swap(ml[idx], ml[best_idx]);
      std::swap(scores[idx], scores[best_idx]);

      return ml[idx++];
    };

    switch (m_phase) {
    case phase::generate_moves: {
      const move_list all_moves = generate_moves(m_pos);

      for (const move mv : all_moves) {
        if (mv.is_noisy()) {
          m_noisy_moves.emplace_back(mv);
        } else {
          m_quiet_moves.emplace_back(mv);
        }

        if (mv == m_tt_move) {
          m_tt_move_valid = true;
        }
      }

      m_phase = phase::emit_tt;
      [[fallthrough]];
    }
    case phase::emit_tt: {
      m_phase = phase::score_noisy;

      if (m_tt_move_valid) {
        return m_tt_move;
      }

      m_tt_move = move::null();
      [[fallthrough]];
    }
    case phase::score_noisy: {
      for (usize i = 0; i < m_noisy_moves.size(); ++i) {
        const move mv = m_noisy_moves[i];

        const auto [victim_stm, victim_ptype] = mv.is_en_passant()
          ? std::tuple{~m_pos.stm(), piece_type::pawn()}
          : m_pos.piece_at(mv.dst());

        const auto [attacker_stm, attacker_ptype] = m_pos.piece_at(mv.src());

        m_noisy_scores[i] = victim_ptype.compressed_idx() * 10 - attacker_ptype.compressed_idx();
      }

      m_phase = phase::emit_noisy;
      [[fallthrough]];
    }
    case phase::emit_noisy: {
      if (m_noisy_idx < m_noisy_moves.size()) {
        move nm = move::null();

        do {
          nm = next_move(m_noisy_moves, m_noisy_scores, m_noisy_idx);
        } while (nm == m_tt_move && m_noisy_idx < m_noisy_moves.size());

        if (nm.has_value()) {
          return nm;
        }
      }

      if (m_skip_quiet) {
        m_phase = phase::exit;
        goto exit;
      } else {
        m_phase = phase::score_quiet;
      }
      [[fallthrough]];
    }
    case phase::score_quiet: {
      for (usize i = 0; i < m_quiet_moves.size(); ++i) {
        m_quiet_scores[i] = m_piece_to.read(m_pos, m_quiet_moves[i]);
      }

      m_phase = phase::emit_quiet;
      [[fallthrough]];
    }
    case phase::emit_quiet: {
      if (m_quiet_idx < m_quiet_moves.size()) {
        move nm = move::null();

        do {
          nm = next_move(m_quiet_moves, m_quiet_scores, m_quiet_idx);
        } while (nm == m_tt_move && m_quiet_idx < m_quiet_moves.size());

        if (nm.has_value()) {
          return nm;
        }
      }

      m_phase = phase::exit;
      [[fallthrough]];
    }
    case phase::exit: {
exit:
    } break;
    }

    return move::null();
  }

private:
  enum class phase {
    generate_moves,
    emit_tt,
    score_noisy,
    emit_noisy,
    score_quiet,
    emit_quiet,
    exit,
  };

  bool m_skip_quiet = false;

  const position& m_pos;
  move            m_tt_move       = move::null();
  bool            m_tt_move_valid = false;

  piece_to_history& m_piece_to;

  phase m_phase = phase::generate_moves;

  move_list            m_noisy_moves;
  std::array<i32, 256> m_noisy_scores{};
  usize                m_noisy_idx = 0;

  move_list            m_quiet_moves;
  std::array<i32, 256> m_quiet_scores{};
  usize                m_quiet_idx = 0;
};

}  // namespace surveyor
