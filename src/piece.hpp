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
#include "util/constant.hpp"
#include "util/integer.hpp"

#include <bit>
#include <concepts>

namespace surveyor {

class color {
public:
  // Constants
  static constexpr usize count = 2;

  // Member Types

  // Constructors
  static constexpr auto white() -> color {
    return color{white_bits};
  }

  static constexpr auto black() -> color {
    return color{black_bits};
  }

  // Overloads
  friend constexpr auto operator==(const color&, const color&) -> bool = default;

private:
  // Constants
  static constexpr u8 white_bits = 0;
  static constexpr u8 black_bits = 1;

  // Constructors
  constexpr color(const u8 bits)
      : m_raw(bits) {
  }

  // Members
  u8 m_raw{};

  // Friends
  friend class place;
};

static_assert(sizeof(color) == sizeof(u8));

struct white_constant {
  static constexpr color value = color::white();
  using value_type             = color;

  /* implicit */ constexpr operator value_type() const noexcept {
    return value;
  }

  /* implicit */ constexpr auto operator()() const noexcept -> value_type {
    return value;
  }
};

struct black_constant {
  static constexpr color value = color::black();
  using value_type             = color;

  /* implicit */ constexpr operator value_type() const noexcept {
    return value;
  }

  /* implicit */ constexpr auto operator()() const noexcept -> value_type {
    return value;
  }
};

template<typename T>
concept color_constant =
  (std::same_as<T, white_constant> || std::same_as<T, black_constant>) && constant<T>;

class piece_type {
public:
  // Constants
  static constexpr usize count            = 7;
  static constexpr usize compressed_count = 6;

  // Member Types

  // Constructors

  static constexpr auto empty() -> piece_type {
    return piece_type{empty_bits};
  }

  static constexpr auto pawn() -> piece_type {
    return piece_type{pawn_bits};
  }

  static constexpr auto knight() -> piece_type {
    return piece_type{knight_bits};
  }

  static constexpr auto bishop() -> piece_type {
    return piece_type{bishop_bits};
  }

  static constexpr auto rook() -> piece_type {
    return piece_type{rook_bits};
  }

  static constexpr auto queen() -> piece_type {
    return piece_type{queen_bits};
  }

  static constexpr auto king() -> piece_type {
    return piece_type{king_bits};
  }

  // Methods
  constexpr auto idx() const -> usize {
    return m_raw;
  }

  /**
   * @brief Returns an index starting from pawn (rather than from empty).
   *
   * @return Index starting from pawn (rather than from empty).
   */
  constexpr auto compressed_idx() const -> usize {
    return m_raw - 1;
  }

  [[nodiscard]] constexpr auto has_value() const -> bool {
    return m_raw > 0;
  }

  // Overloads
  friend constexpr auto operator==(const piece_type&, const piece_type&) -> bool = default;

private:
  // Constants
  static constexpr u8 empty_bits  = 0b000;
  static constexpr u8 pawn_bits   = 0b001;
  static constexpr u8 knight_bits = 0b010;
  static constexpr u8 bishop_bits = 0b011;
  static constexpr u8 rook_bits   = 0b100;
  static constexpr u8 queen_bits  = 0b101;
  static constexpr u8 king_bits   = 0b110;

  // Constructors
  constexpr piece_type(u8 raw)
      : m_raw(raw) {
  }

  // Members
  u8 m_raw{};

  // Friends
  friend class place;
};

static_assert(sizeof(piece_type) == sizeof(u8));

class piece_id {
public:
  // Constructors
  explicit constexpr piece_id(u8 raw)
      : m_raw(raw) {
  }

  static constexpr auto king() -> piece_id {
    return piece_id{0};
  }

  static constexpr auto empty() -> piece_id {
    return piece_id{empty_bits};
  }

  // Methods
  constexpr auto idx() const -> u8 {
    return m_raw;
  }

private:
  // Constants
  static constexpr u8 empty_bits = 0b10000;

  // Members
  u8 m_raw{};
};

class place {
public:
  // Member types
  struct unpacked {
    piece_id   id = piece_id::empty();
    color      c;
    piece_type pt = piece_type::empty();

    [[nodiscard]] constexpr auto has_value() const -> bool {
      return pt.has_value();
    }
  };

  // Constructors
  constexpr place(piece_id id, color c, piece_type type)
      : m_raw(id.idx() << piece_id_shift & piece_id_bits | (c == color::white() ? 0 : color_bits)
              | type.idx()) {
  }

  // Methods
  [[nodiscard]] constexpr auto piece_id() const -> piece_id {
    const u8 bits = (m_raw & piece_id_bits) >> piece_id_shift;
    return surveyor::piece_id{bits};
  }

  [[nodiscard]] constexpr auto color() const -> color {
    return m_raw & color_bits ? color::black() : color::white();
  }

  [[nodiscard]] constexpr auto piece_type() const -> piece_type {
    const u8 bits = m_raw & piece_type_bits;
    return surveyor::piece_type{bits};
  }

  [[nodiscard]] constexpr auto unpack() const -> unpacked {
    return {
      .id = piece_id(),
      .c  = color(),
      .pt = piece_type(),
    };
  }

  [[nodiscard]] constexpr auto has_value() const -> bool {
    return m_raw > 0;
  }

private:
  // Constants
  static constexpr u8 piece_id_bits   = 0b11110000;
  static constexpr u8 color_bits      = 0b00001000;
  static constexpr u8 piece_type_bits = 0b00000111;

  static constexpr int piece_id_shift = 4;
  static constexpr int color_shift    = 3;

  // Members
  u8 m_raw{};
};

}  // namespace surveyor
