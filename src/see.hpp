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

namespace surveyor {

// The SEE function takes heavily from yukari.
inline auto see(const position& pos, move mv) -> i32 {
  constexpr i32 big_see = 100'000;

  constexpr auto score_ptype = [&](piece_type ptype) {
    if (ptype == piece_type::pawn()) {
      return 100;
    }

    if (ptype == piece_type::knight()) {
      return 300;
    }

    if (ptype == piece_type::bishop()) {
      return 300;
    }

    if (ptype == piece_type::rook()) {
      return 500;
    }

    if (ptype == piece_type::queen()) {
      return 900;
    }

    return 0;
  };

  if (mv.is_castle() || mv.is_en_passant() || mv.is_promo()) {
    return big_see;
  }

  bitboard blockers = pos.bb();
  blockers.del(mv.src());

  color stm = pos.stm();

  color_array<piece_mask> attackers{pos.attackers_to(color::white(), mv.dst()),
                                    pos.attackers_to(color::black(), mv.dst())};

  attackers[stm].del(pos.id_at(mv.src()));

  const auto handle_xray = [&](square mover) {
    const square origin = mv.dst();
    blockers.del(mover);

    const geometry::direction dir = geometry::get_direction(origin, mover);

    if (dir == 0) {
      return;
    }

    geometry::x88 scanner = geometry::to_x88(origin) + dir;

    while (!blockers.has_value(geometry::from_x88(scanner))) {
      scanner += dir;

      if (scanner & 0x88) {
        return;
      }
    }

    const square x_ray = geometry::from_x88(scanner);

    const auto [x_ray_id, x_ray_stm, x_ray_ptype] = pos.place_at(x_ray);

    if (x_ray.diag_to(origin) && x_ray_ptype.diag()) {
      attackers[x_ray_stm].set(x_ray_id);
    }

    if (x_ray.orth_to(origin) && x_ray_ptype.orth()) {
      attackers[x_ray_stm].set(x_ray_id);
    }
  };

  std::optional attacker = pos.ptype_at(mv.src());
  std::optional victim   = pos.ptype_at(mv.dst());

  i32 sc    = score_ptype(*victim);
  i32 alpha = -1000;
  i32 beta  = sc;

  const auto next_attacker = [&](color col) -> std::optional<piece_type> {
    piece_mask& pm = attackers[col];

    if (const auto mask = pm & pos.ptype_mask(col, piece_type::pawn()); mask.has_value()) {
      const piece_id attacker_id = mask.lsb();
      pm.del(attacker_id);

      handle_xray(pos.sq_of(col, attacker_id));

      return piece_type::pawn();
    }

    if (const auto mask = pm & pos.ptype_mask(col, piece_type::knight()); mask.has_value()) {
      const piece_id attacker_id = mask.lsb();
      pm.del(attacker_id);
      return piece_type::knight();
    }

    if (const auto mask = pm & pos.ptype_mask(col, piece_type::bishop()); mask.has_value()) {
      const piece_id attacker_id = mask.lsb();
      pm.del(attacker_id);

      handle_xray(pos.sq_of(col, attacker_id));

      return piece_type::bishop();
    }

    if (const auto mask = pm & pos.ptype_mask(col, piece_type::rook()); mask.has_value()) {
      const piece_id attacker_id = mask.lsb();
      pm.del(attacker_id);

      handle_xray(pos.sq_of(col, attacker_id));

      return piece_type::rook();
    }

    if (const auto mask = pm & pos.ptype_mask(col, piece_type::queen()); mask.has_value()) {
      const piece_id attacker_id = mask.lsb();
      pm.del(attacker_id);

      handle_xray(pos.sq_of(col, attacker_id));

      return piece_type::queen();
    }

    if (const auto mask = pm & pos.ptype_mask(col, piece_type::king()); mask.has_value()) {
      const piece_id king_id = mask.lsb();
      pm.del(king_id);

      // Disallow kings moving into attacks.
      if (attackers[~col].has_value()) {
        return std::nullopt;
      }

      return piece_type::king();
    }
    return std::nullopt;
  };

  while (true) {
    victim   = attacker;
    attacker = next_attacker(~stm);
    if (!attacker) {
      sc = beta;
      break;
    }

    sc -= score_ptype(*victim);
    if (sc >= beta) {
      sc = beta;
      break;
    }
    alpha = std::max(alpha, sc);

    victim   = attacker;
    attacker = next_attacker(stm);
    if (!attacker) {
      sc = alpha;
      break;
    }

    sc += score_ptype(*victim);
    if (sc <= alpha) {
      sc = alpha;
      break;
    }

    beta = std::min(beta, sc);
  }

  return sc;
}

}  // namespace surveyor
