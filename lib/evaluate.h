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
};

namespace evaluate_detail {

template<eval_tracer E, color_constant Stm>
auto trace_ids(const position& pos, E& tracer) -> void {
  const color stm = constant_v<Stm>;

  const piece_mask piece_ids = pos.mask(stm);

  for (const auto id : piece_ids) {
    const piece_type ptype = pos.ptype_of(stm, id);

    if (ptype == piece_type::pawn()) {
      tracer.trace_pawn_material(stm);
    }

    if (ptype == piece_type::knight()) {
      tracer.trace_knight_material(stm);
    }

    if (ptype == piece_type::bishop()) {
      tracer.trace_bishop_material(stm);
    }

    if (ptype == piece_type::queen()) {
      tracer.trace_queen_material(stm);
    }
  }
}

}  // namespace evaluate_detail

template<eval_tracer E>
auto trace_eval(const position& pos, E& tracer) -> void {
  using namespace evaluate_detail;
}

inline auto evaluate(const position& pos) -> score {
  struct tracer {
    score mg = 0;
    score eg = 0;

    constexpr auto trace_pawn_material(color stm) -> void {
      if (stm == color::white()) {
        mg += std::get<0>(evaluation_constants::pawn_material);
        eg += std::get<1>(evaluation_constants::pawn_material);
      } else {
        mg -= std::get<0>(evaluation_constants::pawn_material);
        eg -= std::get<1>(evaluation_constants::pawn_material);
      }
    }

    constexpr auto trace_knight_material(color stm) -> void {
      if (stm == color::white()) {
        mg += std::get<0>(evaluation_constants::knight_material);
        eg += std::get<1>(evaluation_constants::knight_material);
      } else {
        mg -= std::get<0>(evaluation_constants::knight_material);
        eg -= std::get<1>(evaluation_constants::knight_material);
      }
    }

    constexpr auto trace_bishop_material(color stm) -> void {
      if (stm == color::white()) {
        mg += std::get<0>(evaluation_constants::bishop_material);
        eg += std::get<1>(evaluation_constants::bishop_material);
      } else {
        mg -= std::get<0>(evaluation_constants::bishop_material);
        eg -= std::get<1>(evaluation_constants::bishop_material);
      }
    }

    constexpr auto trace_rook_material(color stm) -> void {
      if (stm == color::white()) {
        mg += std::get<0>(evaluation_constants::rook_material);
        eg += std::get<1>(evaluation_constants::rook_material);
      } else {
        mg -= std::get<0>(evaluation_constants::rook_material);
        eg -= std::get<1>(evaluation_constants::rook_material);
      }
    }

    constexpr auto trace_queen_material(color stm) -> void {
      if (stm == color::white()) {
        mg += std::get<0>(evaluation_constants::queen_material);
        eg += std::get<1>(evaluation_constants::queen_material);
      } else {
        mg -= std::get<0>(evaluation_constants::queen_material);
        eg -= std::get<1>(evaluation_constants::queen_material);
      }
    }
  };

  tracer t;
  trace_eval(pos, t);

  const i32 phase = pos.phase();

  score s = (t.mg * phase + t.eg * (position::max_phase - phase)) / position::max_phase;

  return pos.stm() == color::white() ? s : -s;
}

}  // namespace surveyor
#endif  // SURVEYOR_EVALUATE_H
