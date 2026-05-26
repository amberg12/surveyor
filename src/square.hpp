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
#include "util/integer.hpp"

#include <concepts>
#include <string_view>

namespace surveyor {

struct square {
  // Constants
  static constexpr u8 count = 64;

  // Member Types

  // Constructors
  constexpr square(std::integral auto idx)
      : idx(idx) {
  }

  constexpr square(std::integral auto file, std::integral auto rank)
      : idx(file + rank * 8) {
  }

  static constexpr auto invalid() -> square {
    return square{count};
  }

  // Methods
  [[nodiscard]] constexpr auto has_value() const -> bool {
    return idx >= count;
  }

  [[nodiscard]] constexpr auto file() const -> i8 {
    return idx / 8;
  }

  [[nodiscard]] constexpr auto rank() const -> i8 {
    return idx % 8;
  }

  // Strings
  static constexpr auto parse(std::string_view s) -> square {
    const char file_char = s[0];
    const char rank_char = s[1];

    return {file_char - 'a', rank_char - '1'};
  }

  u8 idx;
};

static_assert(sizeof(square) == sizeof(u8));

}  // namespace surveyor
