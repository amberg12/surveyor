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

#include "move_generation.hpp"

#include "geometry.hpp"

#include <cassert>

namespace surveyor {
namespace {
auto generate_king_moves(const position& pos, move_list& ml) -> void {
  const attack_box& at      = pos.pin_at();
  const color       stm     = pos.stm();
  const square      king_sq = pos.king_square(stm);

  const piece_mask king_attackers    = pos.attackers_to(~stm, king_sq);
  const usize      king_attackers_nb = king_attackers.popcount();

  for (const square sq : squares) {
    if (!at[sq].is_set(piece_id::king())) {
      continue;
    }

    if (const auto [dst_color, dst_ptype] = pos.piece_at(sq);
        pos.has_value(sq) && dst_color == stm) {
      continue;
    }

    if (pos.attackers_to(~stm, sq).popcount() != 0) {
      continue;
    }

    if (king_attackers_nb >= 1 && [&] {
          for (const piece_id attacker_id : king_attackers) {
            const square     attacker_square = pos.sq_of(~stm, attacker_id);
            const piece_type attacker_ptype  = pos.ptype_of(~stm, attacker_id);

            if (attacker_square == sq || !attacker_ptype.slider()) {
              continue;
            }

            const bool orth_unsafe =
              king_sq.orth_to(attacker_square) && sq.orth_to(attacker_square);
            const bool diag_unsafe =
              king_sq.diag_to(attacker_square) && sq.diag_to(attacker_square);

            if (orth_unsafe || diag_unsafe) {
              return true;
            }
          }

          return false;
        }()) {
      continue;
    }

    if (pos.has_value(sq)) {
      ml.emplace_back(move::make(king_sq, sq, move::cap_normal));
    } else {
      ml.emplace_back(move::make(king_sq, sq, move::normal));
    }
  }
}

auto generate_pawn_moves_to(const position& pos, bitboard allowed, move_list& ml) -> void {
  const color               stm     = pos.stm();
  const piece_mask          pawns   = pos.ptype_mask(stm, piece_type::pawn());
  const geometry::direction pd      = geometry::pawn_direction(stm);
  const square              king_sq = pos.king_square(stm);

  for (const piece_id pawn_id : pawns) {
    const square src = pos.sq_of(pos.stm(), pawn_id);

    if (pos.pinned(src) && src.file() != king_sq.file()) {
      continue;
    }

    if (auto dst = geometry::shift(src, pd); dst.has_value()) {
      if (pos.has_value(*dst)) {
        continue;
      }

      if (allowed.has_value(*dst)) {
        ml.emplace_back(move::make(src, *dst));
      }

      if (dst->relative_rank(stm) == 2) {
        const square dst2 = *geometry::shift(*dst, pd);
        if (pos.has_value(dst2) || !allowed.has_value(dst2)) {
          continue;
        }

        ml.emplace_back(move::make(src, dst2, move::double_push));
      }
    }
  }
}

auto generate_moves_to(const position& pos, bitboard allowed, move_list& ml) -> void {
  const color       stm = pos.stm();
  const attack_box& at  = pos.pin_at();

  for (const square dst : allowed) {
    const piece_mask attackers = at[dst];

    for (const piece_id id : attackers) {
      if (id == piece_id::king()) {
        continue;
      }

      if (pos.has_value(dst)) {
        const auto [dst_stm, dst_ptype] = pos.piece_at(dst);

        if (stm == dst_stm) {
          continue;
        }
      }

      // We already check to see if the dst is friendly so no need to do so here.
      const bool capture = pos.has_value(dst);

      const auto src                  = pos.sq_of(stm, id);
      const auto [src_stm, src_ptype] = pos.piece_at(src);

      if (src_ptype == piece_type::pawn() && !capture) {
        continue;
      }

      if (src_ptype == piece_type::king() && pos.attackers_to(~stm, dst).has_value()) {
        continue;
      }

      if (capture) {
        ml.emplace_back(move::make(src, dst, move::cap_normal));
      } else {
        ml.emplace_back(move::make(src, dst));
      }
    }
  }
}

auto generate_en_passant_move(const position& pos, bitboard allowed, move_list& ml) -> void {
  const square ep = pos.ep();

  if (!ep.has_value()) {
    return;
  }

  const attack_box& at  = pos.pin_at();
  const color       stm = pos.stm();

  if (!allowed.has_value(ep)) {
    return;
  }

  for (const piece_id attacker : at[ep]) {
    const piece_type ptype = pos.ptype_of(stm, attacker);

    if (ptype == piece_type::pawn()) {
      const square src = pos.sq_of(stm, attacker);
      ml.emplace_back(move::make(src, ep, move::en_passant));
    }
  }
}

auto generate_moves_no_checkers(const position& pos) -> move_list {
  move_list ml{};

  generate_moves_to(pos, bitboard::full(), ml);
  generate_pawn_moves_to(pos, bitboard::full(), ml);
  generate_en_passant_move(pos, bitboard::full(), ml);
  generate_king_moves(pos, ml);

  return ml;
}

auto generate_moves_one_checker(const position& pos) -> move_list {
  move_list ml{};

  const bitboard allowed_squares = [&] {
    const color      stm            = pos.stm();
    const square     king_sq        = pos.king_square(stm);
    const piece_mask king_attackers = pos.attackers_to(~stm, king_sq);

    assert(king_attackers.popcount() == 1);

    const piece_id king_attacker = king_attackers.lsb();

    const square     attacker_square = pos.sq_of(~stm, king_attacker);
    const piece_type attacker_ptype  = pos.ptype_of(~stm, king_attacker);

    return bitboard::square_bb(attacker_square) | [&] {
      if (!attacker_ptype.slider()) {
        return bitboard::empty();
      }

      return bitboard::ray_exclusive(attacker_square, king_sq);
    }();
  }();

  generate_moves_to(pos, allowed_squares, ml);
  generate_pawn_moves_to(pos, allowed_squares, ml);
  generate_en_passant_move(pos, allowed_squares, ml);
  generate_king_moves(pos, ml);

  return ml;
}

auto generate_moves_two_checkers(const position& pos) -> move_list {
  move_list ml{};

  generate_king_moves(pos, ml);

  return ml;
}
}  // namespace

auto generate_moves(const position& pos) -> move_list {
  move_list ml{};

  switch (pos.checkers()) {
  case 0:
    return generate_moves_no_checkers(pos);
  case 1:
    return generate_moves_one_checker(pos);
  default:
    return generate_moves_two_checkers(pos);
  }

  return ml;
}

}  // namespace surveyor
