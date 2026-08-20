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
  { et.trace_pawn_psqt(stm, sq) };
  { et.trace_knight_material(stm) };
  { et.trace_knight_psqt(stm, sq) };
  { et.trace_bishop_material(stm) };
  { et.trace_bishop_psqt(stm, sq) };
  { et.trace_rook_material(stm) };
  { et.trace_rook_psqt(stm, sq) };
  { et.trace_queen_material(stm) };
  { et.trace_queen_psqt(stm, sq) };
  { et.trace_king_psqt(stm, sq) };
};

namespace evaluate_detail {

template<eval_tracer E, color_constant Stm>
auto trace_pawns(const position& pos, E& tracer) -> void {
  const color stm = constant_v<Stm>;

  const piece_mask pawns = pos.ptype_mask(stm, piece_type::pawn());

  for (const piece_id pawn : pawns) {
    const square sq = pos.sq_of(stm, pawn);

    tracer.trace_pawn_material(stm);
    tracer.trace_pawn_psqt(stm, sq);
  }
}

template<eval_tracer E, color_constant Stm>
auto trace_knights(const position& pos, E& tracer) -> void {
  const color      stm     = constant_v<Stm>;
  const piece_mask knights = pos.ptype_mask(stm, piece_type::knight());

  for (const piece_id n : knights) {
    const square sq = pos.sq_of(stm, n);
    tracer.trace_knight_material(stm);
    tracer.trace_knight_psqt(stm, sq);
  }
}

template<eval_tracer E, color_constant Stm>
auto trace_bishops(const position& pos, E& tracer) -> void {
  const color      stm     = constant_v<Stm>;
  const piece_mask bishops = pos.ptype_mask(stm, piece_type::bishop());

  for (const piece_id b : bishops) {
    const square sq = pos.sq_of(stm, b);
    tracer.trace_bishop_material(stm);
    tracer.trace_bishop_psqt(stm, sq);
  }
}

template<eval_tracer E, color_constant Stm>
auto trace_rooks(const position& pos, E& tracer) -> void {
  const color      stm   = constant_v<Stm>;
  const piece_mask rooks = pos.ptype_mask(stm, piece_type::rook());

  for (const piece_id r : rooks) {
    const square sq = pos.sq_of(stm, r);
    tracer.trace_rook_material(stm);
    tracer.trace_rook_psqt(stm, sq);
  }
}

template<eval_tracer E, color_constant Stm>
auto trace_queens(const position& pos, E& tracer) -> void {
  const color      stm    = constant_v<Stm>;
  const piece_mask queens = pos.ptype_mask(stm, piece_type::queen());

  for (const piece_id q : queens) {
    const square sq = pos.sq_of(stm, q);
    tracer.trace_queen_material(stm);
    tracer.trace_queen_psqt(stm, sq);
  }
}

template<eval_tracer E, color_constant Stm>
auto trace_king(const position& pos, E& tracer) -> void {
  const color  stm = constant_v<Stm>;
  const square sq  = pos.king_square(stm);
  tracer.trace_king_psqt(stm, sq);
}

}  // namespace evaluate_detail

template<eval_tracer E>
auto trace_eval(const position& pos, E& tracer) -> void {
  using namespace evaluate_detail;

  trace_pawns<E, white_constant>(pos, tracer);
  trace_pawns<E, black_constant>(pos, tracer);
  trace_knights<E, white_constant>(pos, tracer);
  trace_knights<E, black_constant>(pos, tracer);
  trace_bishops<E, white_constant>(pos, tracer);
  trace_bishops<E, black_constant>(pos, tracer);
  trace_rooks<E, white_constant>(pos, tracer);
  trace_rooks<E, black_constant>(pos, tracer);
  trace_queens<E, white_constant>(pos, tracer);
  trace_queens<E, black_constant>(pos, tracer);
  trace_king<E, white_constant>(pos, tracer);
  trace_king<E, black_constant>(pos, tracer);
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

    constexpr auto trace_pawn_psqt(color stm, square sq) -> void {
      if (stm == color::white()) {
        mg += std::get<0>(evaluation_constants::pawn_psqt[sq.idx - 8]);
        eg += std::get<1>(evaluation_constants::pawn_psqt[sq.idx - 8]);
      } else {
        mg -= std::get<0>(evaluation_constants::pawn_psqt[sq.mirror().idx - 8]);
        eg -= std::get<1>(evaluation_constants::pawn_psqt[sq.mirror().idx - 8]);
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

    constexpr auto trace_knight_psqt(color stm, square sq) -> void {
      if (stm == color::white()) {
        mg += std::get<0>(evaluation_constants::knight_psqt[sq.idx]);
        eg += std::get<1>(evaluation_constants::knight_psqt[sq.idx]);
      } else {
        mg -= std::get<0>(evaluation_constants::knight_psqt[sq.mirror().idx]);
        eg -= std::get<1>(evaluation_constants::knight_psqt[sq.mirror().idx]);
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

    constexpr auto trace_bishop_psqt(color stm, square sq) -> void {
      if (stm == color::white()) {
        mg += std::get<0>(evaluation_constants::bishop_psqt[sq.idx]);
        eg += std::get<1>(evaluation_constants::bishop_psqt[sq.idx]);
      } else {
        mg -= std::get<0>(evaluation_constants::bishop_psqt[sq.mirror().idx]);
        eg -= std::get<1>(evaluation_constants::bishop_psqt[sq.mirror().idx]);
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

    constexpr auto trace_rook_psqt(color stm, square sq) -> void {
      if (stm == color::white()) {
        mg += std::get<0>(evaluation_constants::rook_psqt[sq.idx]);
        eg += std::get<1>(evaluation_constants::rook_psqt[sq.idx]);
      } else {
        mg -= std::get<0>(evaluation_constants::rook_psqt[sq.mirror().idx]);
        eg -= std::get<1>(evaluation_constants::rook_psqt[sq.mirror().idx]);
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

    constexpr auto trace_queen_psqt(color stm, square sq) -> void {
      if (stm == color::white()) {
        mg += std::get<0>(evaluation_constants::queen_psqt[sq.idx]);
        eg += std::get<1>(evaluation_constants::queen_psqt[sq.idx]);
      } else {
        mg -= std::get<0>(evaluation_constants::queen_psqt[sq.mirror().idx]);
        eg -= std::get<1>(evaluation_constants::queen_psqt[sq.mirror().idx]);
      }
    }

    constexpr auto trace_king_psqt(color stm, square sq) -> void {
      if (stm == color::white()) {
        mg += std::get<0>(evaluation_constants::king_psqt[sq.idx]);
        eg += std::get<1>(evaluation_constants::king_psqt[sq.idx]);
      } else {
        mg -= std::get<0>(evaluation_constants::king_psqt[sq.mirror().idx]);
        eg -= std::get<1>(evaluation_constants::king_psqt[sq.mirror().idx]);
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
