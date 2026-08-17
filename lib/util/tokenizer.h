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

#ifndef SURVEYOR_TOKENIZER_H
#define SURVEYOR_TOKENIZER_H
#include "integer.h"

#include <string>

namespace surveyor {
class tokenizer {
public:
  explicit tokenizer(std::string_view str);

  auto next() -> std::optional<std::string>;

private:
  std::string m_str;
  usize       m_ptr = 0;
};
}  // namespace surveyor

#endif  // SURVEYOR_TOKENIZER_H
