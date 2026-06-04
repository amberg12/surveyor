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

#include "evaluate.hpp"

namespace surveyor {

auto evaluate(const position& pos) -> score {
  const score out = 100
      * (pos.ptype_count(color::white(), piece_type::pawn())
         - pos.ptype_count(color::black(), piece_type::pawn()))
    + 320
      * (pos.ptype_count(color::white(), piece_type::knight())
         - pos.ptype_count(color::black(), piece_type::knight()))
    + 330
      * (pos.ptype_count(color::white(), piece_type::bishop())
         - pos.ptype_count(color::black(), piece_type::bishop()))
    + 500
      * (pos.ptype_count(color::white(), piece_type::rook())
         - pos.ptype_count(color::black(), piece_type::rook()))
    + 900
      * (pos.ptype_count(color::white(), piece_type::queen())
         - pos.ptype_count(color::black(), piece_type::queen()));

  return out;
}

}  // namespace surveyor
