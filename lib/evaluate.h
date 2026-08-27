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
  { et.trace_pawn_material(stm) };
  { et.trace_knight_material(stm) };
  { et.trace_bishop_material(stm) };
  { et.trace_rook_material(stm) };
  { et.trace_queen_material(stm) };
  { et.trace_pawn_psqt(stm, sq) };
  { et.trace_knight_psqt(stm, sq) };
  { et.trace_bishop_psqt(stm, sq) };
  { et.trace_rook_psqt(stm, sq) };
  { et.trace_queen_psqt(stm, sq) };
  { et.trace_king_psqt(stm, sq) };
  { et.trace_bishop_pair(stm) };
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
      tracer.trace_pawn_material(stm);
      tracer.trace_pawn_psqt(stm, sq);
    }

    if (ptype == piece_type::knight()) {
      tracer.trace_knight_material(stm);
      tracer.trace_knight_psqt(stm, sq);
    }

    if (ptype == piece_type::bishop()) {
      tracer.trace_bishop_material(stm);
      tracer.trace_bishop_psqt(stm, sq);
    }

    if (ptype == piece_type::rook()) {
      tracer.trace_rook_material(stm);
      tracer.trace_rook_psqt(stm, sq);
    }

    if (ptype == piece_type::queen()) {
      tracer.trace_queen_material(stm);
      tracer.trace_queen_psqt(stm, sq);
    }

    if (ptype == piece_type::king()) {
      tracer.trace_king_psqt(stm, sq);
    }
  }
}

template<eval_tracer E, color_constant Stm>
auto trace_bishops(const position& pos, E& tracer) -> void {
  const color stm = constant_v<Stm>;
  const i32 bishop_count = pos.bb(stm, piece_type::bishop()).ipopcount();

  if (bishop_count >= 2) {
    tracer.trace_bishop_pair(stm);
  }
}

}  // namespace evaluate_detail

template<eval_tracer E>
auto trace_eval(const position& pos, E& tracer) -> void {
  using namespace evaluate_detail;

  trace_ids<E, white_constant>(pos, tracer);
  trace_ids<E, black_constant>(pos, tracer);
  trace_bishops<E, white_constant>(pos, tracer);
  trace_bishops<E, black_constant>(pos, tracer);
}

inline auto evaluate(const position& pos) -> score {
  struct tracer {
    score mg = 0;
    score eg = 0;

    const position& pos;

    auto sgn(color stm) -> i16 {
      return stm == pos.stm() ? 1 : -1;
    }

    // Is this macro abuse? Is it dry? Who knows, but I think it will help my sanity.
#define SURVEYOR_TRACE_VALUE(name)                      \
  constexpr auto trace_##name(color stm) -> void {      \
    mg += evaluation_constants::name.first * sgn(stm);  \
    eg += evaluation_constants::name.second * sgn(stm); \
  }

#define SURVEYOR_TRACE_SQUARE(name)                              \
  constexpr auto trace_##name(color stm, square sq) -> void {    \
    const square rel = sq.relative(stm);                         \
    mg += evaluation_constants::name[rel.idx].first * sgn(stm);  \
    eg += evaluation_constants::name[rel.idx].second * sgn(stm); \
  }

#define SURVEYOR_TRACE_NUMBER(name)                        \
  constexpr auto trace_##name(color stm, i32 n) -> void {  \
    mg += evaluation_constants::name[n].first * sgn(stm);  \
    eg += evaluation_constants::name[n].second * sgn(stm); \
  }

    SURVEYOR_TRACE_VALUE(pawn_material);
    SURVEYOR_TRACE_VALUE(knight_material);
    SURVEYOR_TRACE_VALUE(bishop_material);
    SURVEYOR_TRACE_VALUE(rook_material);
    SURVEYOR_TRACE_VALUE(queen_material);
    SURVEYOR_TRACE_SQUARE(pawn_psqt);
    SURVEYOR_TRACE_SQUARE(knight_psqt);
    SURVEYOR_TRACE_SQUARE(bishop_psqt);
    SURVEYOR_TRACE_SQUARE(rook_psqt);
    SURVEYOR_TRACE_SQUARE(queen_psqt);
    SURVEYOR_TRACE_SQUARE(king_psqt);
    SURVEYOR_TRACE_VALUE(bishop_pair);

    // And is it really macro abuse if I undefine them straight after?
#undef SURVEYOR_TRACE_VALUE
#undef SURVEYOR_TRACE_SQUARE
#undef SURVEYOR_TRACE_NUMBER
  };

  tracer t{0, 0, pos};
  trace_eval(pos, t);

  const i32 phase = pos.phase();

  return (t.mg * phase + t.eg * (position::max_phase - phase)) / position::max_phase;
}

}  // namespace surveyor
#endif  // SURVEYOR_EVALUATE_H
