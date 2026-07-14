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
#include "move.hpp"
#include "node_type.hpp"
#include "score.hpp"
#include "zobrist.hpp"

#include <utility>

namespace surveyor {
class position;
}  // namespace surveyor

namespace surveyor::tt {

constexpr u8 max_age = 0b00011111;

struct entry {
  z_key key{};
  score sc    = scoring::none;
  move  mv    = move::null();
  u8    info  = 0;
  u8    depth = 0;

  [[nodiscard]] constexpr auto node() const -> node_type {
    switch (info & 0b11000000) {
    case 0b00000000:
      return node_type::none();
    case 0b01000000:
      return node_type::pv();
    case 0b10000000:
      return node_type::cut();
    case 0b11000000:
      return node_type::all();
    default:
      std::unreachable();
    }
  }

  [[nodiscard]] constexpr auto age() const -> u8 {
    return info & 0b00011111;
  }

  static constexpr auto construct_info(node_type nt, u8 age) -> u8 {
    const u8 node_type_flag = [&] {
      if (nt == node_type::none()) {
        return 0b00000000;
      }

      if (nt == node_type::pv()) {
        return 0b01000000;
      }

      if (nt == node_type::cut()) {
        return 0b10000000;
      }

      if (nt == node_type::all()) {
        return 0b11000000;
      }

      std::unreachable();
    }();

    return node_type_flag | age;
  }
};

class transposition_table {
public:
  // Constructors
  explicit transposition_table(usize mb)
      : m_clusters(std::make_unique<entry[]>(mb_to_cluster_count(mb)))
      , m_cluster_count(mb_to_cluster_count(mb)) {
  }

  // Methods
  auto clear() -> void {
    std::memset(m_clusters.get(), 0, sizeof(entry) * m_cluster_count);
  }

  auto age() -> void {
    if (++m_age > max_age) {
      m_age = 0;
    }
  }

  auto write(const position& pos, i32 ply, move mv, score sc, i32 depth, node_type nt) -> void;
  [[nodiscard]] auto probe(const position& pos, i32 ply) const -> std::optional<entry>;

  [[nodiscard]] auto hashfull() const -> usize {
    usize out = 0;
    for (usize i = 0; i < 1000; ++i) {
      const entry& e = m_clusters[i];

      if (e.node().has_value() && e.age() == m_age) {
        ++out;
      }
    }

    return out;
  }

private:
  static constexpr auto mb_to_cluster_count(usize mb) -> usize {
    return mb * 1024 * 1024 / sizeof(entry);
  }

  u8 m_age = 0;

  std::unique_ptr<entry[]> m_clusters      = nullptr;
  usize                    m_cluster_count = 0;
};

}  // namespace surveyor::tt
