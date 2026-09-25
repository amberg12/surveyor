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
#include "util/math.h"

#include <cmath>
#include <print>
#include <random>
#include <span>
#include <utility>

namespace surveyor_tuner {

namespace {
auto print_constant(const evaltune_c&              constant,
                    std::string_view               name,
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

  for (const auto& constant : constants) {
    const i32 mg = mg_vector[constant.idx()] * config::result_scale;
    const i32 eg = eg_vector[constant.idx()] * config::result_scale;

    std::print("S({}, {}), ", mg, eg);
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
      const auto& constant = constants[rank * 8 + file];
      const i32 mg = mg_vector[constant.idx()] * config::result_scale;
      const i32 eg = eg_vector[constant.idx()] * config::result_scale;

      std::print("S({:>4}, {:>4}), ", mg, eg);
    }

    std::println();
  }

  std::println("}};");
}

#define PRINT_PSQT(name, mg_vector, eg_vector) print_psqt(name, #name, mg_vector, eg_vector)

auto calculate_local_learning_rate(f64 min, f64 max, usize step_counter, usize period_length)
  -> f64 {
  return min
    + (max - min) * 0.5
    * (1.0
       + std::cos(std::numbers::pi * f64{static_cast<f64>(step_counter)}
                  / f64{static_cast<f64>(period_length)}));
}
}  // namespace

auto tune_evaluation(std::vector<tuner_position> dataset) -> void {
  using namespace surveyor::evaluation_constants;

  namespace rg = std::ranges;
  namespace rv = std::views;

  std::mt19937_64 rng(std::random_device{}());

  usize step_counter  = 0;
  usize period_length = config::initial_period_length;

  f64 learning_rate_max = config::initial_learning_rate_max;
  f64 learning_rate_min = config::initial_learning_rate_min;

  const auto feature_array = []<typename T>{
    const auto s = globals::get().params();
    return std::vector<T>(s, T{});
  };

  auto momentum_mg = feature_array.operator()<f64>();
  auto momentum_eg = feature_array.operator()<f64>();

  const auto& params = globals::get().evaltune_params();

  for (const usize epoch : rv::iota(usize{0}, config::epochs)) {
    rg::shuffle(dataset, rng);

    if (step_counter == period_length) {
      period_length *= 2;
      step_counter = 0;

      learning_rate_max *= 0.95;
      learning_rate_min *= 0.95;

      momentum_mg = {};
      momentum_eg = {};
    }

    step_counter += 1;

    const f64 local_learning_rate = calculate_local_learning_rate(
      learning_rate_min, learning_rate_max, step_counter, period_length);

    auto gradient_mg = feature_array.operator()<f64>();
    auto gradient_eg = feature_array.operator()<f64>();

    i32 batch_pos = 0;

    for (tuner_position& pos : dataset) {
      const auto [mg, eg] = evaluate_unnormalized(pos.pos).to_vector();

      const f64 dot_product_mg = [&] {
        f64 out = 0;

        for (i32 i = 0; i < mg.size(); ++i) {
          out += mg[i] * params[i]->mg();
        }

        return out;
      }();

      const f64 dot_product_eg = [&] {
        f64 out = 0;

        for (i32 i = 0; i < eg.size(); ++i) {
          out += eg[i] * params[i]->eg();
        }

        return out;
      }();

      const f64 phase            = static_cast<f64>(pos.pos.phase()) / 24.0;
      const f64 predicted_result = sigmoid(phase * dot_product_mg + (1.0 - phase) * dot_product_eg);
      const f64 prediction_error = predicted_result - pos.result;

      for (usize i = 0; i < params.size(); ++i) {
        gradient_mg[i] += prediction_error * phase * mg[i];
        gradient_eg[i] += prediction_error * (1.0 - phase) * eg[i];
      }

      ++batch_pos;

      if (batch_pos == config::batch_size || &pos == &dataset.back()) {
        const f64 inv_batch = 1.0 / static_cast<f64>(batch_pos);

        for (auto [param, gmg, geg, mmg, meg] :
             rv::zip(params, gradient_mg, gradient_eg, momentum_mg, momentum_eg)) {
          const f64 avg_gmg = gmg * inv_batch + config::lambda * param->mg();
          const f64 avg_geg = geg * inv_batch + config::lambda * param->eg();

          mmg = config::mu * mmg + avg_gmg;
          meg = config::mu * meg + avg_geg;

          param->set(param->mg() - mmg * local_learning_rate,
                     param->eg() - meg * local_learning_rate);
             }

        rg::fill(gradient_mg, 0.0);
        rg::fill(gradient_eg, 0.0);
        batch_pos = 0;
      }
    }

    std::println("epoch {}/{}", epoch + 1, config::epochs);
  }

  std::vector<f64> mg(params.size()), eg(params.size());
  for (const evaltune_c* p : params) {
    mg[p->idx()] = p->mg();
    eg[p->idx()] = p->eg();
  }

  // --- Normalization Logic ---
  // Calculates the mean of a feature array, zero-centers the array, and returns the mean.
  auto normalize = [&](std::span<const evaltune_c> constants) -> std::pair<f64, f64> {
    f64 sum_mg = 0.0;
    f64 sum_eg = 0.0;

    for (const evaltune_c& c : constants) {
      sum_mg += mg[c.idx()];
      sum_eg += eg[c.idx()];
    }

    const f64 mean_mg = sum_mg / static_cast<f64>(constants.size());
    const f64 mean_eg = sum_eg / static_cast<f64>(constants.size());

    for (const evaltune_c& c : constants) {
      mg[c.idx()] -= mean_mg;
      eg[c.idx()] -= mean_eg;
    }

    return {mean_mg, mean_eg};
  };

  auto [p_psqt_mg, p_psqt_eg] = normalize(pawn_psqt);
  mg[pawn_material.idx()] += p_psqt_mg;
  eg[pawn_material.idx()] += p_psqt_eg;

  auto [n_mob_mg, n_mob_eg]   = normalize(knight_mobility);
  auto [n_psqt_mg, n_psqt_eg] = normalize(knight_psqt);
  mg[knight_material.idx()] += n_mob_mg + n_psqt_mg;
  eg[knight_material.idx()] += n_mob_eg + n_psqt_eg;

  auto [b_mob_mg, b_mob_eg]   = normalize(bishop_mobility);
  auto [b_psqt_mg, b_psqt_eg] = normalize(bishop_psqt);
  mg[bishop_material.idx()] += b_mob_mg + b_psqt_mg;
  eg[bishop_material.idx()] += b_mob_eg + b_psqt_eg;

  auto [r_mob_mg, r_mob_eg]   = normalize(rook_mobility);
  auto [r_psqt_mg, r_psqt_eg] = normalize(rook_psqt);
  mg[rook_material.idx()] += r_mob_mg + r_psqt_mg;
  eg[rook_material.idx()] += r_mob_eg + r_psqt_eg;

  auto [q_mob_mg, q_mob_eg]   = normalize(queen_mobility);
  auto [q_psqt_mg, q_psqt_eg] = normalize(queen_psqt);
  mg[queen_material.idx()] += q_mob_mg + q_psqt_mg;
  eg[queen_material.idx()] += q_mob_eg + q_psqt_eg;

  normalize(king_psqt);

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