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

#include "tune_evaluation.h"

#include <print>

namespace surveyor_tuner {

auto tune_evaluation(std::vector<tuner_position> dataset) -> void {
  const position& pos = dataset[0].pos;
  auto x = evaluate_unnormalized(pos);

  const auto [mg, eg] = x.to_vector();

  for (i32 i = 0; i < mg.size(); ++i) {
    std::println("{} {}", mg[i], eg[i]);
  }
}

}  // namespace surveyor_tuner
