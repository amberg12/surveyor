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
#include "square.hpp"
#include "util/integer.hpp"

namespace surveyor {

struct bitboard {
  using iterator = cast_iterator<bit_iterator<u64>, square>;

  u64 raw = 0;

  // Constructors
  static constexpr auto square_bb(square sq) -> bitboard {
    return {1ull << sq.idx};
  }

  static constexpr auto full() -> bitboard {
    return {~0ull};
  }

  static constexpr auto empty() -> bitboard {
    return {0};
  }

  // Methods
  constexpr auto set(square sq) -> void {
    *this |= square_bb(sq);
  }

  constexpr auto del(square sq) -> void {
    *this &= ~square_bb(sq);
  }

  [[nodiscard]] constexpr auto has_value(square sq) const -> bool {
    return (*this & square_bb(sq)).raw != 0;
  }

  [[nodiscard]] constexpr auto popcount() const -> usize {
    return std::popcount(raw);
  }

  [[nodiscard]] constexpr auto ipopcount() const -> isize {
    return std::popcount(raw);
  }

  [[nodiscard]] constexpr auto lsb() const -> square {
    return square{std::countr_zero(surveyor::lsb(raw))};
  }

  // Overloads
  friend constexpr auto operator~(bitboard bb) -> bitboard {
    return bitboard{~bb.raw};
  }

  friend constexpr auto operator|(bitboard lhs, bitboard rhs) -> bitboard {
    return {lhs.raw | rhs.raw};
  }

  friend constexpr auto operator|=(bitboard& lhs, bitboard rhs) -> bitboard& {
    lhs = lhs | rhs;
    return lhs;
  }

  friend constexpr auto operator&(bitboard lhs, bitboard rhs) -> bitboard {
    return {lhs.raw & rhs.raw};
  }

  friend constexpr auto operator&=(bitboard& lhs, bitboard rhs) -> bitboard& {
    lhs = lhs & rhs;
    return lhs;
  }

  friend constexpr auto operator==(const bitboard& lhs, const bitboard& rhs) -> bool = default;

  // Iterator
  [[nodiscard]] constexpr auto begin() const -> iterator {
    return iterator{raw};
  }

  [[nodiscard]] static constexpr auto end() -> iterator {
    return iterator{0};
  }

  // Ctor (needs to be at end)
  static constexpr auto ray_exclusive(square src, square dst) {
    constexpr std::array<std::array<bitboard, 64>, 64> rays = [] {
      std::array<std::array<bitboard, 64>, 64> out;

      for (const square src : squares) {
        for (const square dst : squares) {
          if (src == dst) {
            continue;
          }

          if (!src.diag_to(dst) && !src.orth_to(dst)) {
            continue;
          }

          i8 d_file = signum(dst.file() - src.file());
          i8 d_rank = signum(dst.rank() - src.rank());

          i8 file = src.file() + d_file;
          i8 rank = src.rank() + d_rank;

          bitboard bb{};

          while (file != dst.file() || rank != dst.rank()) {
            bb |= square_bb(square{file, rank});
            file += d_file;
            rank += d_rank;
          }

          out[src.idx][dst.idx] = bb;
        }
      }

      return out;
    }();

    return rays[src.idx][dst.idx];
  }

  static constexpr auto ray_inclusive(square src, square dst) -> bitboard {
    constexpr std::array<std::array<bitboard, 64>, 64> rays = [] {
      std::array<std::array<bitboard, 64>, 64> out;

      for (const square src : squares) {
        for (const square dst : squares) {
          if (!src.diag_to(dst) && !src.orth_to(dst)) {
            continue;
          }

          out[src.idx][dst.idx] = ray_exclusive(src, dst) | square_bb(src) | square_bb(dst);
        }
      }

      return out;
    }();

    return rays[src.idx][dst.idx];
  }
};

}  // namespace surveyor
