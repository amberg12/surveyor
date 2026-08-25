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

#ifndef SURVEYOR_EVALUATE_H
#define SURVEYOR_EVALUATE_H
#include "evaluation_constants.h"
#include "position.h"

namespace surveyor {

template<typename E>
concept eval_tracer = requires(E et, color stm, square sq) {
  { et.trace_pawn_material(stm, sq) };
  { et.trace_knight_material(stm, sq) };
  { et.trace_bishop_material(stm, sq) };
  { et.trace_rook_material(stm, sq) };
  { et.trace_queen_material(stm, sq) };
  { et.trace_king_material(stm, sq) };
};

namespace evaluate_detail {

template<eval_tracer E, color_constant Stm>
auto trace_ids(const position& pos, E& tracer) -> void {
  const color stm = constant_v<Stm>;

  const piece_mask piece_ids = pos.mask(stm);

  for (const auto id : piece_ids) {
    const piece_type ptype = pos.ptype_of(stm, id);
    const square     sq    = pos.sq_of(stm, id);

    if (ptype == piece_type::pawn()) {
      tracer.trace_pawn_material(stm, sq);
    }

    if (ptype == piece_type::knight()) {
      tracer.trace_knight_material(stm, sq);
    }

    if (ptype == piece_type::rook()) {
      tracer.trace_rook_material(stm, sq);
    }

    if (ptype == piece_type::bishop()) {
      tracer.trace_bishop_material(stm, sq);
    }

    if (ptype == piece_type::queen()) {
      tracer.trace_queen_material(stm, sq);
    }

    if (ptype == piece_type::king()) {
      tracer.trace_king_material(stm, sq);
    }
  }
}

}  // namespace evaluate_detail

template<eval_tracer E>
auto trace_eval(const position& pos, E& tracer) -> void {
  using namespace evaluate_detail;

  trace_ids<E, white_constant>(pos, tracer);
  trace_ids<E, black_constant>(pos, tracer);
}

inline auto evaluate(const position& pos) -> score {
  struct tracer {
    score mg = 0;
    score eg = 0;

    const position& pos;

    auto sgn(color stm) -> i16 {
      return stm == pos.stm() ? 1 : -1;
    }

    constexpr auto trace_pawn_material(color stm, square sq) -> void {
      mg += (evaluation_constants::pawn_material.first
             + evaluation_constants::knight_psqt[sq.relative(stm).idx].first);
      eg += (evaluation_constants::pawn_material.second
             + evaluation_constants::knight_psqt[sq.relative(stm).idx].second);
    }

    constexpr auto trace_knight_material(color stm, square sq) -> void {
      mg += (evaluation_constants::knight_material.first
             + evaluation_constants::knight_psqt[sq.relative(stm).idx].first)
        * sgn(stm);
      eg += (evaluation_constants::knight_material.second
             + evaluation_constants::knight_psqt[sq.relative(stm).idx].second)
        * sgn(stm);
    }

    constexpr auto trace_bishop_material(color stm, square sq) -> void {
      mg += (evaluation_constants::bishop_material.first
             + evaluation_constants::bishop_psqt[sq.relative(stm).idx].first)
        * sgn(stm);
      eg += (evaluation_constants::bishop_material.second
             + evaluation_constants::bishop_psqt[sq.relative(stm).idx].second)
        * sgn(stm);
    }

    constexpr auto trace_rook_material(color stm, square sq) -> void {
      mg += (evaluation_constants::rook_material.first
             + evaluation_constants::rook_psqt[sq.relative(stm).idx].first)
        * sgn(stm);
      eg += (evaluation_constants::rook_material.second
             + evaluation_constants::rook_psqt[sq.relative(stm).idx].second)
        * sgn(stm);
    }

    constexpr auto trace_queen_material(color stm, square sq) -> void {
      mg += (evaluation_constants::queen_material.first
             + evaluation_constants::queen_psqt[sq.relative(stm).idx].first)
        * sgn(stm);
      eg += (evaluation_constants::queen_material.second
             + evaluation_constants::queen_psqt[sq.relative(stm).idx].second)
        * sgn(stm);
    }

    constexpr auto trace_king_material(color stm, square sq) -> void {
      mg += evaluation_constants::king_psqt[sq.relative(stm).idx].first * sgn(stm);
      eg += evaluation_constants::king_psqt[sq.relative(stm).idx].second * sgn(stm);
    }
  };

  tracer t{0, 0, pos};
  trace_eval(pos, t);

  const i32 phase = pos.phase();

  score s = (t.mg * phase + t.eg * (position::max_phase - phase)) / position::max_phase;

  return pos.stm() == color::white() ? s : -s;
}

}  // namespace surveyor
#endif  // SURVEYOR_EVALUATE_H
