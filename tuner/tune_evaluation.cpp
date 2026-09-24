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

#include "../lib/evaluation_constants.h"

#include <print>

namespace surveyor_tuner {

namespace {
auto print_constant(evaltune_c              constant,
                    std::string_view        name,
                    const std::vector<f64>& mg_vector,
                    const std::vector<f64>& eg_vector) -> void {
  const i32 mg = mg_vector[constant.idx()] * config::result_scale;
  const i32 eg = eg_vector[constant.idx()] * config::result_scale;

  std::println("inline const pair {} = S({}, {});", name, mg, eg);
}

#define PRINT_CONSTANT(name, mg_vector, eg_vector) print_constant(name, #name, mg_vector, eg_vector)

auto print_array(std::span<const evaltune_c> constants,
                 std::string_view            name,
                 const std::vector<f64>&     mg_vector,
                 const std::vector<f64>&     eg_vector) -> void {
  std::println("inline const std::array {} = {{", name);

  std::print("  ");

  for (const auto constant : constants) {
    const i32 mg = mg_vector[constant.idx()] * config::result_scale;
    const i32 eg = eg_vector[constant.idx()] * config::result_scale;

    std::print("S({} {}), ", mg, eg);
  }

  std::println();
  std::println("}}");
}

#define PRINT_ARRAY(name, mg_vector, eg_vector) print_array(name, #name, mg_vector, eg_vector)

auto print_psqt(std::span<const evaltune_c> constants,
                std::string_view            name,
                const std::vector<f64>&     mg_vector,
                const std::vector<f64>&     eg_vector) -> void {
  std::println("inline const std::array {} = {{", name);

  for (usize rank = 0; rank < constants.size() / 8; ++rank) {
    std::print("  ");

    for (usize file = 0; file < 8; ++file) {
      const auto constant = constants[rank * 8 + file];
      const i32 mg = mg_vector[constant.idx()] * config::result_scale;
      const i32 eg = eg_vector[constant.idx()] * config::result_scale;

      std::print("S({:>4}, {:>4}), ", mg, eg);
    }

    std::println();
  }

  std::println("}};");
}

#define PRINT_PSQT(name, mg_vector, eg_vector) print_psqt(name, #name, mg_vector, eg_vector)
}  // namespace

auto tune_evaluation(std::vector<tuner_position> dataset) -> void {
  using namespace surveyor::evaluation_constants;

  const position& pos = dataset[0].pos;
  auto            x   = evaluate_unnormalized(pos);

  const auto [mg, eg] = x.to_vector();

  PRINT_CONSTANT(pawn_material, mg, eg);
  PRINT_CONSTANT(knight_material, mg, eg);
  PRINT_CONSTANT(bishop_material, mg, eg);
  PRINT_CONSTANT(rook_material, mg, eg);
  PRINT_CONSTANT(queen_material, mg, eg);
  PRINT_CONSTANT(bishop_pair, mg, eg);

  std::println();

  PRINT_ARRAY(knight_mobility, mg, eg);
  PRINT_ARRAY(bishop_mobility, mg, eg);
  PRINT_ARRAY(rook_mobility, mg, eg);
  PRINT_ARRAY(queen_mobility, mg, eg);

  std::println();

  PRINT_CONSTANT(isolated_pawn, mg, eg);

  PRINT_ARRAY(passed_pawn, mg, eg);
  PRINT_ARRAY(defended_passed_pawn, mg, eg);
  PRINT_ARRAY(defended_pawn, mg, eg);

  std::println();

  PRINT_ARRAY(shelter_centre, mg, eg);
  PRINT_ARRAY(shelter_mid, mg, eg);
  PRINT_ARRAY(shelter_edge, mg, eg);

  std::println();

  PRINT_PSQT(pawn_psqt, mg, eg);
  PRINT_PSQT(knight_psqt, mg, eg);
  PRINT_PSQT(bishop_psqt, mg, eg);
  PRINT_PSQT(rook_psqt, mg, eg);
  PRINT_PSQT(queen_psqt, mg, eg);
  PRINT_PSQT(king_psqt, mg, eg);
}

}  // namespace surveyor_tuner
