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
#include "see.hpp"

namespace surveyor {

class move_picker {
public:
  move_picker(const position&    pos,
              move               tt_move,
              piece_to_history&  piece_to,
              capture_history&   capthist,
              search_stack*      ss,
              std::optional<i32> bad_noisy_threshold = std::nullopt)
      : m_pos(pos)
      , m_tt_move(tt_move)
      , m_piece_to(piece_to)
      , m_capthist(capthist)
      , m_ss(ss)
      , m_bad_noisy_threshold(bad_noisy_threshold) {
  }

  auto skip_quiet() -> void {
    m_skip_quiet = true;
  }

  auto next_move() -> move {
    const auto inc_sort_move = [&](move_list& ml, std::array<i32, 256>& scores,
                                   usize& idx) -> move {
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
      const move_list legal_moves = generate_moves(m_pos);

      bool tt_move_found = false;

      for (const move mv : legal_moves) {
        if (mv == m_tt_move) {
          tt_move_found = true;
          continue;
        }

        if (mv.is_noisy()) {
          m_noisy_moves.emplace_back(mv);
        } else {
          m_quiet_moves.emplace_back(mv);
        }
      }

      if (!tt_move_found) {
        m_tt_move = move::null();
      }

      m_phase = phase::emit_tt;
      [[fallthrough]];
    }
    case phase::emit_tt: {
      m_phase = phase::score_noisy;

      if (m_tt_move.has_value()) {
        return m_tt_move;
      }

      [[fallthrough]];
    }
    case phase::score_noisy: {
      for (i32 i = 0; i < m_noisy_moves.size(); ++i) {
        const move mv = m_noisy_moves[i];

        const i32 move_score = [&] {
          if (!mv.is_capture()) {
            return 0;
          }

          const piece_type victim =
            mv.is_en_passant() ? piece_type::pawn() : m_pos.ptype_at(mv.dst());

          return static_cast<i32>(history_max + history_max * victim.idx()
                                  + m_capthist.read(m_pos, mv) / 8);
        }();

        m_noisy_scores[i] = move_score;
      }

      m_phase = phase::emit_noisy;
      [[fallthrough]];
    }
    case phase::emit_noisy: {
      while (m_noisy_idx < m_noisy_moves.size()) {
        const move mv = inc_sort_move(m_noisy_moves, m_noisy_scores, m_noisy_idx);

        if (m_bad_noisy_threshold && see(m_pos, mv) < *m_bad_noisy_threshold) {
          m_bad_noisy_moves.emplace_back(mv);
          continue;
        }

        return mv;
      }

      m_phase = phase::score_quiet;
      [[fallthrough]];
    }
    case phase::score_quiet: {
      if (!m_skip_quiet) {
        for (i32 i = 0; i < m_quiet_moves.size(); ++i) {
          const move mv = m_quiet_moves[i];

          const i32 move_score = [&] {
            i32 out = m_piece_to.read(m_pos, mv);

            for (const i32 ply : conthist_plies) {
              continuation_history::subtable* subtable = m_ss[-ply].conthist_subtable;

              if (subtable) {
                out += subtable->read(m_pos, mv);
              }
            }

            return out;
          }();

          m_quiet_scores[i] = move_score;
        }

        m_phase = phase::emit_quiet;
        [[fallthrough]];
      }
    }
    case phase::emit_quiet: {
      if (!m_skip_quiet) {
        while (m_quiet_idx < m_quiet_moves.size()) {
          return inc_sort_move(m_quiet_moves, m_quiet_scores, m_quiet_idx);
        }
      }

      m_phase = phase::emit_bad_noisy;
      [[fallthrough]];
    }
    case phase::emit_bad_noisy: {
      while (m_bad_noisy_idx < m_bad_noisy_moves.size()) {
        return m_bad_noisy_moves[m_bad_noisy_idx++];
      }
    }
    case phase::exit:
      break;
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
    emit_bad_noisy,
    exit,
  };

  bool m_skip_quiet = false;

  const position& m_pos;
  move            m_tt_move = move::null();
  search_stack*   m_ss;

  piece_to_history& m_piece_to;
  capture_history&  m_capthist;

  phase m_phase = phase::generate_moves;

  move_list            m_noisy_moves;
  std::array<i32, 256> m_noisy_scores{};
  usize                m_noisy_idx = 0;

  move_list            m_quiet_moves;
  std::array<i32, 256> m_quiet_scores{};
  usize                m_quiet_idx = 0;

  std::optional<i32> m_bad_noisy_threshold = std::nullopt;
  move_list          m_bad_noisy_moves;
  usize              m_bad_noisy_idx = 0;
};

}  // namespace surveyor
