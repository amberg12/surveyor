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

#include "transposition_table.hpp"

#include "position.hpp"

namespace surveyor::tt {
namespace {
constexpr auto idx(u64 key, u64 cluster_count) -> u64 {
  return static_cast<u64>(static_cast<u128>(key) * static_cast<u128>(cluster_count) >> 64);
}
}

auto transposition_table::write(const position& pos, move mv, node_type nt) -> void {
  entry& cluster = m_clusters[idx(pos.key(), m_cluster_count)];

  const entry new_entry = {
    .key = pos.key(),
    .mv = mv,
    .info = entry::construct_info(nt, m_age),
  };

  cluster = new_entry;
}

auto transposition_table::probe(const position& pos) const -> std::optional<entry> {
  const entry& e = m_clusters[idx(pos.key(), m_cluster_count)];

  if (e.key == pos.key() && e.node().has_value()) {
    return e;
  }

  return std::nullopt;
}

}  // namespace surveyor
