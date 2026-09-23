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

#include "util/math.h"

#include <random>

namespace surveyor_tuner {
namespace {
// Based off sirius (yoinked, really)
auto phase_p(i32 phase) {
  const auto p = [&](const auto x) {
    return std::round(x) - 2 * std::floor(std::round(x) / 2);
  };

  const auto l = [&](const auto x) {
    return std::fmin(0.9, -0.09793221 * (x - 23) + 0.189393939);
  };

  const auto s = [&](const auto x) {
    return p(x) * l(std::round(x)) + (1 - p(x));
  };

  const auto f = [&](const auto x) {
    if (x > 16) {
      return 1 - std::pow(std::round(x) - 16, 2) / 73.1428571;
    }

    return 1 - std::pow(std::round(x) - 16, 2) / 269.478634;
  };

  return phase > 12 ? s(phase) * f(phase) : f(phase);
}

const double phase_weight_sum = [] {
  double sum = 0.0;
  for (i32 ph = 0; ph <= 24; ++ph) sum += phase_p(ph);
  return sum;
}();
}  // namespace

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

  const auto num_games      = games.size();
  const auto expected_pos = num_games * 25;

  std::array<i64, 25> phase_distribution{};

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
               std::min<i32>(40, static_cast<i32>(candidate_idx.size())), rng);

    position current_pos = g.root;

    for (const auto [i, move_pair] : rv::enumerate(g.moves)) {
      const auto& [uci_best_move, eval] = move_pair;
      const f32  game_result = current_pos.stm() == color::white() ? g.result : 1.0f - g.result;
      const move parsed_move = move::parse(uci_best_move, current_pos);

      const auto phase              = current_pos.phase();
      const i64  expected_for_phase = expected_pos * phase_p(phase) / phase_weight_sum;
      const i64  actual_for_phase   = phase_distribution[std::clamp(phase, 0, 24)];

      const f64 sampling_p = std::clamp(
        1.0 - static_cast<f64>(actual_for_phase) / static_cast<f64>(expected_for_phase), 0.0, 1.0);
      std::uniform_real_distribution<double> dist(0.0, 1.0);

      const f64 sigmoid_score = sigmoid(*parse_number<f64>(eval) / 300.0);

      const f64 max_mismatch = std::max<f64>(game_result, 1.0 - game_result);
      const f64 mismatch     = std::abs(game_result - sigmoid_score) / max_mismatch;

      if (i >= to_skip && !parsed_move.is_capture() && !current_pos.checkers()
          && rg::find(sampled_idx, static_cast<i32>(i)) != sampled_idx.end()
          && current_pos.material() > 4 && dist(rng) < sampling_p && mismatch < 0.45) {
        result.emplace_back(game_result, current_pos);
        phase_distribution[std::clamp(phase, 0, 24)] += 1;
      }

      current_pos = current_pos.make_move(parsed_move);
    }
  }
  return result;
}
}  // namespace surveyor_tuner
