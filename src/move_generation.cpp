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
  const color  stm     = pos.stm();
  const square king_sq = pos.king_square(stm);

  const bitboard pinned       = pos.pin_board() & ~bitboard::file_bb(king_sq.file());
  const bitboard moving_pawns = pos.bb(stm, piece_type::pawn()) & ~pinned;

  const bitboard allowed_dsts = allowed & ~pos.bb();

  const geometry::direction dir = geometry::pawn_direction(stm);

  const bitboard single_move_dsts        = moving_pawns.shift(dir) & allowed_dsts;
  const bitboard pseudo_single_move_dsts = moving_pawns.shift(dir) & ~pos.bb();

  const bitboard normal_single_move_dsts = single_move_dsts & ~bitboard::promo_zome(stm);
  for (const square dst : single_move_dsts) {
    const square src = geometry::from_x88(geometry::to_x88(dst) + geometry::pawn_direction(~stm));

    ml.emplace_back(move::make(src, dst, move::normal));
  }

  const bitboard single_move_promo_dsts = single_move_dsts & bitboard::promo_zome(stm);
  for (const square dst : single_move_promo_dsts) {
    const square src = geometry::from_x88(geometry::to_x88(dst) + geometry::pawn_direction(~stm));

    ml.emplace_back(move::make(src, dst, move::promo_q));
    ml.emplace_back(move::make(src, dst, move::promo_n));
    ml.emplace_back(move::make(src, dst, move::promo_r));
    ml.emplace_back(move::make(src, dst, move::promo_b));
  }

  const bitboard double_push_mask =
    bitboard{stm == color::white() ? 16711680ull : 280375465082880ull};
  const bitboard double_move_dsts =
    (pseudo_single_move_dsts & double_push_mask).shift(dir) & allowed_dsts;
  for (const square dst : double_move_dsts) {
    const square src =
      geometry::from_x88(geometry::to_x88(dst) + 2 * geometry::pawn_direction(~stm));

    ml.emplace_back(move::make(src, dst, move::double_push));
  }
}

auto write(const position&  pos,
           move_list&       ml,
           bitboard         dsts,
           piece_mask       subset,
           enum move::flags flag) -> void {
  const attack_box& atk = pos.pin_at();
  const color stm = pos.stm();

  for (const square dst : dsts) {
    const piece_mask attackers = atk[dst] & subset;

    for (const piece_id id : attackers) {
      const square src = pos.sq_of(stm, id);
      ml.emplace_back(move::make(src, dst, flag));
    }
  }
}

auto generate_moves_to(const position& pos, bitboard allowed, move_list& ml) -> void {
  const color stm = pos.stm();

  const bitboard empty = ~pos.bb() & allowed;
  const bitboard enemy = pos.color_bb(~stm) & allowed;

  const piece_mask mask          = pos.mask(stm) & ~piece_mask{piece_id::king()};
  const piece_mask pawn_mask     = pos.ptype_mask(stm, piece_type::pawn());
  const piece_mask non_pawn_mask = mask & ~pawn_mask;

  const bitboard promo_zone = bitboard::promo_zome(stm);

  write(pos, ml, enemy & promo_zone, pawn_mask, move::cap_promo_q);
  write(pos, ml, enemy & promo_zone, pawn_mask, move::cap_promo_n);
  write(pos, ml, enemy & promo_zone, pawn_mask, move::cap_promo_r);
  write(pos, ml, enemy & promo_zone, pawn_mask, move::cap_promo_b);

  write(pos, ml, enemy & ~promo_zone, pawn_mask, move::cap_normal);

  write(pos, ml, enemy, non_pawn_mask, move::cap_normal);
  write(pos, ml, empty, non_pawn_mask, move::normal);
}

auto generate_en_passant_move(const position& pos, bitboard allowed, move_list& ml) -> void {
  const square ep        = pos.ep();
  const color  stm       = pos.stm();
  const square ep_victim = *geometry::shift(ep, geometry::pawn_direction(~stm));

  if (!ep.has_value() || !allowed.has_value(ep_victim)) {
    return;
  }

  const attack_box& at      = pos.pin_at();
  const square      king_sq = pos.king_square(stm);

  for (const piece_id attacker : at[ep]) {
    const piece_type ptype = pos.ptype_of(stm, attacker);

    if (ptype == piece_type::pawn()) {
      const square src = pos.sq_of(stm, attacker);

      if ([&]() -> bool {
            const square cap{ep.file(), src.rank()};

            if (king_sq.rank() != src.rank()) {
              return false;
            }

            const i32 rank = king_sq.rank();

            for (i32 dir : {-1, 1}) {
              for (i32 file = king_sq.file() + dir; 0 <= file && file < 8; file += dir) {
                const square s{file, rank};

                if (s == src || s == cap) {
                  continue;
                }

                if (!pos.has_value(s)) {
                  continue;
                }

                const auto [c, pt] = pos.piece_at(s);
                return c != stm && (pt == piece_type::rook() || pt == piece_type::queen());
              }
            }

            return false;
          }()) {
        continue;
      }

      ml.emplace_back(move::make(src, ep, move::en_passant));
    }
  }
}

auto generate_castling(const position& pos, move_list& ml) -> void {
  const color  stm     = pos.stm();
  const square king_sq = pos.king_square(stm);

  const auto is_valid = [&](square rook_src, i8 king_dst_file, i8 rook_dst_file) -> bool {
    const square   king_dst_square{king_dst_file, stm == color::white() ? 0 : 7};
    const bitboard king_path = bitboard::ray_exclusive(king_sq, king_dst_square);

    if (pos.is_attacked(~stm, king_dst_square) || pos.has_value(king_dst_square)) {
      return false;
    }

    for (const square path_square : king_path) {
      if (pos.is_attacked(~stm, path_square)) {
        return false;
      }

      if (pos.has_value(path_square) && path_square != rook_src) {
        return false;
      }
    }

    const square   rook_dst{rook_dst_file, stm == color::white() ? 0 : 7};
    const bitboard rook_path = bitboard::ray_exclusive(rook_src, rook_dst);

    if (pos.has_value(rook_dst)) {
      return false;
    }

    for (const square path_square : rook_path) {
      if (pos.has_value(path_square) && path_square != king_sq) {
        return false;
      }
    }

    return true;
  };

  if (pos.a_side(stm).has_value() && is_valid(*pos.a_side(stm), 2, 3)) {
    const square dst{king_sq.file() - 2, king_sq.rank()};
    ml.emplace_back(move::make(king_sq, dst, move::castle_aside));
  }

  if (pos.h_side(stm).has_value() && is_valid(*pos.h_side(stm), 6, 5)) {
    const square dst{king_sq.file() + 2, king_sq.rank()};
    ml.emplace_back(move::make(king_sq, dst, move::castle_hside));
  }
}

auto generate_moves_no_checkers(const position& pos) -> move_list {
  move_list ml{};

  generate_moves_to(pos, bitboard::full(), ml);
  generate_pawn_moves_to(pos, bitboard::full(), ml);
  generate_en_passant_move(pos, bitboard::full(), ml);
  generate_king_moves(pos, ml);
  generate_castling(pos, ml);

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
