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

#include "data.h"

namespace surveyor_tuner {

auto parse(std::istream& is) -> std::vector<game> {
  std::vector<game> result;
  std::string       line;

  while (std::getline(is, line)) {
    std::string        tok;
    std::istringstream ss(line);

    ss >> tok;
    f32 game_result = *parse_number<f32>(tok);

    std::string fen;
    for (i32 i = 0; i < 6; ++i) {
      ss >> tok;
      fen += tok + " ";
    }

    const position game_root = position::parse(fen);

    std::vector<std::pair<std::string, i32>> game_moves;
    while (ss >> tok) {
      std::string move = tok;
      ss >> tok;
      game_moves.emplace_back(move, *parse_number<i32>(tok));
    }

    result.emplace_back(game_result, game_root, game_moves);
  }

  return result;
}
}  // namespace surveyor_tuner
