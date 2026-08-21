/*
 * Surveyor - A UCI Chess Engine
 * Copyright (C) 2026 Amber Goulding
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the
 * GNU Affero General Public License as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#include "tokenizer.h"

namespace surveyor {

tokenizer::tokenizer(std::string_view str)
    : m_str(str) {
}

auto tokenizer::next() -> std::optional<std::string> {
  namespace rg = std::ranges;

  std::string_view remaining = std::string_view{m_str}.substr(m_ptr);

  auto first = rg::find_if(remaining, [](char c) {
    return !std::isspace(static_cast<unsigned char>(c));
  });

  if (first == remaining.end()) {
    m_ptr = m_str.size();
    return std::nullopt;
  }

  const isize start = rg::distance(remaining.begin(), first);

  remaining.remove_prefix(start);

  auto last = rg::find_if(remaining, [](char c) {
    return std::isspace(static_cast<unsigned char>(c));
  });

  const auto length = rg::distance(remaining.begin(), last);

  m_ptr += start + length;

  return std::string{remaining.substr(0, length)};
}

}  // namespace surveyor
