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

#include "move.hpp"

#include "position.hpp"

namespace surveyor {

auto move::parse(std::string_view sv, const position& pos) -> move {
  const square src = square::parse(sv.substr(0, 2));
  const square dst = square::parse(sv.substr(2, 2));

  const auto [stm, ptype] = pos.piece_at(src);

  if (ptype == piece_type::pawn() && dst == pos.ep()) {
    return make(src, dst, en_passant);
  }

  if (ptype == piece_type::king() && std::abs(src.file() - dst.file()) >= 2) {
    if (src.file() > dst.file()) {
      return make(src, dst, castle_hside);
    } else {
      return make(src, dst, castle_aside);
    }
  }

  const bool is_capture = pos.has_value(dst);
  const bool is_promo   = sv.size() == 5;

  if (is_promo) {
    const char promo = sv[4];

    if (is_capture) {
      switch (promo) {
      case 'n':
        return make(src, dst, cap_promo_n);
      case 'b':
        return make(src, dst, cap_promo_b);
      case 'r':
        return make(src, dst, cap_promo_r);
      case 'q':
        return make(src, dst, cap_promo_q);
      }
    } else {
      switch (promo) {
      case 'n':
        return make(src, dst, promo_n);
      case 'b':
        return make(src, dst, promo_b);
      case 'r':
        return make(src, dst, promo_r);
      case 'q':
        return make(src, dst, promo_q);
      }
    }
  }

  if (is_capture) {
    return make(src, dst, cap_normal);
  }

  return make(src, dst, normal);
}

}  // namespace surveyor
