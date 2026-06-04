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
#include "evaluation_constants.hpp"
#include "position.hpp"

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
  const color stm = constant_v<Stm>;
  const square sq = pos.king_square(stm);
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
    score s;

    constexpr auto trace_pawn_material(color stm) -> void {
      if (stm == color::white()) {
        s += evaluation_constants::pawn_material;
      } else {
        s -= evaluation_constants::pawn_material;
      }
    }

    constexpr auto trace_pawn_psqt(color stm, square sq) -> void {
      if (stm == color::white()) {
        s += evaluation_constants::pawn_psqt[sq.idx - 8];
      } else {
        s -= evaluation_constants::pawn_psqt[sq.mirror().idx - 8];
      }
    }

    constexpr auto trace_knight_material(color stm) -> void {
      if (stm == color::white()) {
        s += evaluation_constants::knight_material;
      } else {
        s -= evaluation_constants::knight_material;
      }
    }

    constexpr auto trace_knight_psqt(color stm, square sq) -> void {
      if (stm == color::white()) {
        s += evaluation_constants::knight_psqt[sq.idx];
      } else {
        s -= evaluation_constants::knight_psqt[sq.mirror().idx];
      }
    }

    constexpr auto trace_bishop_material(color stm) -> void {
      if (stm == color::white()) {
        s += evaluation_constants::bishop_material;
      } else {
        s -= evaluation_constants::bishop_material;
      }
    }

    constexpr auto trace_bishop_psqt(color stm, square sq) -> void {
      if (stm == color::white()) {
        s += evaluation_constants::bishop_psqt[sq.idx];
      } else {
        s -= evaluation_constants::bishop_psqt[sq.mirror().idx];
      }
    }

    constexpr auto trace_rook_material(color stm) -> void {
      if (stm == color::white()) {
        s += evaluation_constants::rook_material;
      } else {
        s -= evaluation_constants::rook_material;
      }
    }

    constexpr auto trace_rook_psqt(color stm, square sq) -> void {
      if (stm == color::white()) {
        s += evaluation_constants::rook_psqt[sq.idx];
      } else {
        s -= evaluation_constants::rook_psqt[sq.mirror().idx];
      }
    }

    constexpr auto trace_queen_material(color stm) -> void {
      if (stm == color::white()) {
        s += evaluation_constants::queen_material;
      } else {
        s -= evaluation_constants::queen_material;
      }
    }

    constexpr auto trace_queen_psqt(color stm, square sq) -> void {
      if (stm == color::white()) {
        s += evaluation_constants::queen_psqt[sq.idx];
      } else {
        s -= evaluation_constants::queen_psqt[sq.mirror().idx];
      }
    }

    constexpr auto trace_king_psqt(color stm, square sq) -> void {
      if (stm == color::white()) {
        s += evaluation_constants::king_psqt[sq.idx];
      } else {
        s -= evaluation_constants::king_psqt[sq.mirror().idx];
      }
    }
  };

  tracer t;
  trace_eval(pos, t);

  return pos.stm() == color::white() ? t.s : -t.s;
}

}  // namespace surveyor
