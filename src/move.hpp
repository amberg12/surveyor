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

#include <format>
#include <string_view>

namespace surveyor {

class position;

enum class move_type {
  normal,
};

class move {
public:
  // Constants
  // https://87flowers.com/chess-moveflags/
  enum flags : u16 {
    normal       = 0x0000,
    double_push  = 0x1000,
    castle_aside = 0x2000,
    castle_hside = 0x3000,
    promo_q      = 0x4000,
    promo_n      = 0x5000,
    promo_r      = 0x6000,
    promo_b      = 0x7000,
    cap_normal   = 0x8000,
    en_passant   = 0x9000,
    cap_promo_q  = 0xC000,
    cap_promo_n  = 0xD000,
    cap_promo_r  = 0xE000,
    cap_promo_b  = 0xF000
  };

  // Constructors
  static constexpr auto make(square src, square dst) -> move {
    move out;
    out.m_raw |= src.idx;
    out.m_raw |= dst.idx << 6;

    return out;
  }

  static constexpr auto make(square src, square dst, flags f) -> move {
    move out = make(src, dst);
    out.m_raw |= static_cast<u16>(f);

    return out;
  }

  // Methods
  [[nodiscard]] constexpr auto src() const -> square {
    return square{m_raw & 0b111111};
  }

  [[nodiscard]] constexpr auto dst() const -> square {
    return square{m_raw >> 6 & 0b111111};
  }

  [[nodiscard]] constexpr auto is_capture() const -> bool {
    return m_raw & 0x8000;
  }

  [[nodiscard]] constexpr auto is_promo() const -> bool {
    return m_raw & 0x4000;
  }

  [[nodiscard]] constexpr auto is_en_passant() const -> bool {
    return (m_raw & 0xF000) == en_passant;
  }

  [[nodiscard]] constexpr auto is_castle() const -> bool {
    return (m_raw & 0xE000) == 0x2000;
  }

  [[nodiscard]] constexpr auto flags() const -> flags {
    return static_cast<enum flags>(m_raw & 0xF000);
  }

  // String
  [[nodiscard]] static auto parse(std::string_view sv, const position& pos) -> move;

private:
  u16 m_raw{};
};

}  // namespace surveyor

template<>
struct std::formatter<surveyor::move> : std::formatter<std::string> {
  auto format(const surveyor::move& mv, std::format_context& ctx) const {
    const std::string str = std::format("{}{}", mv.src(), mv.dst());
    return std::formatter<std::string>::format(str, ctx);
  }
};
