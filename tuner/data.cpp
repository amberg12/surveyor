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

#include <random>

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

    std::vector<std::pair<std::string, std::string>> game_moves;
    while (ss >> tok) {
      std::string move = tok;
      ss >> tok;
      game_moves.emplace_back(move, tok);
    }

    result.emplace_back(game_result, game_root, game_moves);
  }

  return result;
}

auto filter(std::vector<game> games) -> std::vector<tuner_position> {
  namespace rg = std::ranges;
  namespace rv = std::views;

  std::vector<tuner_position> result;
  std::mt19937_64             rng;

  for (const auto& g : games) {

    const i32 to_skip = static_cast<i32>(rg::count_if(g.moves, [](const auto& mv) {
      return mv.second == "0";
    }));

    const auto candidate_idx =
      rv::iota(to_skip, static_cast<i32>(g.moves.size())) | rg::to<std::vector<i32>>();

    std::vector<i32> sampled_idx;

    rg::sample(candidate_idx, std::back_inserter(sampled_idx),
               std::min<i32>(25, static_cast<i32>(candidate_idx.size())), rng);

    position current_pos = g.root;

    for (const auto [i, move_pair] : rv::enumerate(g.moves)) {
      const auto& [uci_best_move, eval] = move_pair;
      const f32  game_result = current_pos.stm() == color::white() ? g.result : 1.0f - g.result;
      const move parsed_move = move::parse(uci_best_move, current_pos);

      if (i >= to_skip && !parsed_move.is_capture() && !current_pos.checkers()
          && rg::find(sampled_idx, static_cast<i32>(i)) != sampled_idx.end()) {
        result.emplace_back(game_result, current_pos);
      }

      current_pos = current_pos.make_move(parsed_move);
    }
  }
  return result;
}
}  // namespace surveyor_tuner
