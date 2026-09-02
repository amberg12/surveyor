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

#include "config.h"
#include "util/math.h"

#include <cmath>
#include <print>
#include <random>

namespace surveyor_tuner {
namespace {
namespace features {
struct f {
  std::string name;
  usize       idx;
  usize       cnt;
};

#define CREATE_FEATURE(name, idx, cnt) constexpr f name = {#name, idx, cnt};

CREATE_FEATURE(pawn_material, 0, 1)
CREATE_FEATURE(knight_material, pawn_material.idx + pawn_material.cnt, 1)
CREATE_FEATURE(bishop_material, knight_material.idx + knight_material.cnt, 1)
CREATE_FEATURE(rook_material, bishop_material.idx + bishop_material.cnt, 1)
CREATE_FEATURE(queen_material, rook_material.idx + rook_material.cnt, 1)
CREATE_FEATURE(pawn_psqt, queen_material.idx + queen_material.cnt, 64)
CREATE_FEATURE(knight_psqt, pawn_psqt.idx + pawn_psqt.cnt, 64)
CREATE_FEATURE(bishop_psqt, knight_psqt.idx + knight_psqt.cnt, 64)
CREATE_FEATURE(rook_psqt, bishop_psqt.idx + bishop_psqt.cnt, 64)
CREATE_FEATURE(queen_psqt, rook_psqt.idx + rook_psqt.cnt, 64)
CREATE_FEATURE(king_psqt, queen_psqt.idx + queen_psqt.cnt, 64)
CREATE_FEATURE(bishop_pair, king_psqt.idx + king_psqt.cnt, 1)
CREATE_FEATURE(knight_mobility, bishop_pair.idx + bishop_pair.cnt, 9);
CREATE_FEATURE(bishop_mobility, knight_mobility.idx + knight_mobility.cnt, 14);
CREATE_FEATURE(rook_mobility, bishop_mobility.idx + bishop_mobility.cnt, 15);
CREATE_FEATURE(queen_mobility, rook_mobility.idx + rook_mobility.cnt, 28);
CREATE_FEATURE(passed_pawn, queen_mobility.idx + queen_mobility.cnt, 8)
CREATE_FEATURE(isolated_pawn, passed_pawn.idx + passed_pawn.cnt, 1);
CREATE_FEATURE(shelter_edge, isolated_pawn.idx + isolated_pawn.cnt, 8)
CREATE_FEATURE(shelter_mid, shelter_edge.idx + shelter_edge.cnt, 8)
CREATE_FEATURE(shelter_centre, shelter_mid.idx + shelter_mid.cnt, 8)

#undef CREATE_FEATURE

}  // namespace features

constexpr usize feature_count = features::shelter_centre.idx + features::shelter_centre.cnt;

template<typename T>
using feature_array = std::array<T, feature_count>;

auto calculate_local_learning_rate(f64 min, f64 max, usize step_counter, usize period_length)
  -> f64 {
  return min
    + (max - min) * 0.5
    * (1.0
       + std::cos(std::numbers::pi * f64{static_cast<double>(step_counter)}
                  / f64{static_cast<double>(period_length)}));
}

auto extract_features(const position& pos) -> feature_array<i8> {
  feature_array<i8> out{};

  struct extractor {
    const position&    e_pos;
    feature_array<i8>& backing_array;

    auto sgn(color stm) const -> i8 {
      return stm == e_pos.stm() ? 1 : -1;
    }

#define SURVEYOR_TRACE_VALUE(name)                 \
  auto trace_##name(color stm) -> void {           \
    backing_array[features::name.idx] += sgn(stm); \
  }

#define SURVEYOR_TRACE_SQUARE(name)                          \
  auto trace_##name(color stm, square sq) -> void {          \
    const square rel = sq.relative(stm);                     \
    backing_array[features::name.idx + rel.idx] += sgn(stm); \
  }

#define SURVEYOR_TRACE_NUMBER(name)                    \
  auto trace_##name(color stm, i32 n) -> void {        \
    backing_array[features::name.idx + n] += sgn(stm); \
  }

    SURVEYOR_TRACE_VALUE(pawn_material)
    SURVEYOR_TRACE_VALUE(knight_material)
    SURVEYOR_TRACE_VALUE(bishop_material)
    SURVEYOR_TRACE_VALUE(rook_material)
    SURVEYOR_TRACE_VALUE(queen_material)
    SURVEYOR_TRACE_SQUARE(pawn_psqt)
    SURVEYOR_TRACE_SQUARE(knight_psqt)
    SURVEYOR_TRACE_SQUARE(bishop_psqt)
    SURVEYOR_TRACE_SQUARE(rook_psqt)
    SURVEYOR_TRACE_SQUARE(queen_psqt)
    SURVEYOR_TRACE_SQUARE(king_psqt)
    SURVEYOR_TRACE_VALUE(bishop_pair)
    SURVEYOR_TRACE_NUMBER(knight_mobility)
    SURVEYOR_TRACE_NUMBER(bishop_mobility)
    SURVEYOR_TRACE_NUMBER(rook_mobility)
    SURVEYOR_TRACE_NUMBER(queen_mobility)
    SURVEYOR_TRACE_NUMBER(passed_pawn)
    SURVEYOR_TRACE_VALUE(isolated_pawn)
    SURVEYOR_TRACE_NUMBER(shelter_edge)
    SURVEYOR_TRACE_NUMBER(shelter_mid)
    SURVEYOR_TRACE_NUMBER(shelter_centre)

#undef SURVEYOR_TRACE_VALUE
#undef SURVEYOR_TRACE_SQUARE
#undef SURVEYOR_TRACE_NUMBER
  };

  extractor e{pos, out};
  trace_eval(pos, e);

  return out;
}

auto print_feature(features::f feat, feature_array<f64> mg, feature_array<f64> eg) {
  if (feat.cnt == 1) {
    const i32 mg_score = mg[feat.idx] * config::result_scale;
    const i32 eg_score = eg[feat.idx] * config::result_scale;
    std::println("constexpr std::pair<score, score> {} = {{{}, {}}};", feat.name, mg_score,
                 eg_score);
  } else {
    std::print("constexpr std::array<std::pair<score, score>, {}> {} = {{{{", feat.cnt, feat.name);

    for (i32 i = 0; i < feat.cnt; ++i) {
      const i32 mg_score = mg[feat.idx + i] * config::result_scale;
      const i32 eg_score = eg[feat.idx + i] * config::result_scale;
      std::print("{{{}, {}}}, ", mg_score, eg_score);
    }

    std::println("}}}};");
  }
}
}  // namespace

auto tune_evaluation(std::vector<tuner_position> dataset) -> void {
  namespace rg = std::ranges;
  namespace rv = std::ranges::views;

  std::mt19937 rng(std::random_device{}());

  usize step_counter  = 0;
  usize period_length = config::initial_period_length;

  f64 learning_rate_max = config::initial_learning_rate_max;
  f64 learning_rate_min = config::initial_learning_rate_min;

  feature_array<f64> momentum_mg{};
  feature_array<f64> momentum_eg{};

  feature_array<f64> weight_mg{};
  feature_array<f64> weight_eg{};

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

    feature_array<f64> gradient_mg{};
    feature_array<f64> gradient_eg{};

    i32 batch_pos = 0;

    for (tuner_position& pos : dataset) {
      const feature_array<i8> feature_vector = extract_features(pos.pos);

      const f64 dot_product_mg = dot_product(feature_vector, weight_mg);
      const f64 dot_product_eg = dot_product(feature_vector, weight_eg);

      const f64 phase            = static_cast<f64>(pos.pos.phase()) / 24.0;
      const f64 predicted_result = sigmoid(phase * dot_product_mg + (1.0 - phase) * dot_product_eg);
      const f64 prediction_error = predicted_result - pos.result;

      for (auto [gmg, geg, feat] : rv::zip(gradient_mg, gradient_eg, feature_vector)) {
        gmg += prediction_error * phase * feat;
        geg += prediction_error * (1.0 - phase) * feat;
      }

      ++batch_pos;

      if (batch_pos == config::batch_size || &pos == &dataset.back()) {
        for (auto [gmg, geg, mmg, meg, wmg, weg] :
             rv::zip(gradient_mg, gradient_eg, momentum_mg, momentum_eg, weight_mg, weight_eg)) {
          const f64 avg_gmg = gmg / static_cast<f64>(batch_pos) + config::lambda * wmg;
          const f64 avg_geg = geg / static_cast<f64>(batch_pos) + config::lambda * weg;
          mmg               = config::mu * mmg + avg_gmg;
          meg               = config::mu * meg + avg_geg;
          wmg -= mmg * local_learning_rate;
          weg -= meg * local_learning_rate;
        }

        gradient_mg = {};
        gradient_eg = {};
        batch_pos   = 0;
      }
    }

    std::println("epoch {}/{}", epoch + 1, config::epochs);
  }

  print_feature(features::pawn_material, weight_mg, weight_eg);
  print_feature(features::knight_material, weight_mg, weight_eg);
  print_feature(features::bishop_material, weight_mg, weight_eg);
  print_feature(features::rook_material, weight_mg, weight_eg);
  print_feature(features::queen_material, weight_mg, weight_eg);
  print_feature(features::pawn_psqt, weight_mg, weight_eg);
  print_feature(features::knight_psqt, weight_mg, weight_eg);
  print_feature(features::bishop_psqt, weight_mg, weight_eg);
  print_feature(features::rook_psqt, weight_mg, weight_eg);
  print_feature(features::queen_psqt, weight_mg, weight_eg);
  print_feature(features::king_psqt, weight_mg, weight_eg);
  print_feature(features::bishop_pair, weight_mg, weight_eg);
  print_feature(features::knight_mobility, weight_mg, weight_eg);
  print_feature(features::bishop_mobility, weight_mg, weight_eg);
  print_feature(features::rook_mobility, weight_mg, weight_eg);
  print_feature(features::queen_mobility, weight_mg, weight_eg);
  print_feature(features::passed_pawn, weight_mg, weight_eg);
  print_feature(features::isolated_pawn, weight_mg, weight_eg);
  print_feature(features::shelter_centre, weight_mg, weight_eg);
  print_feature(features::shelter_mid, weight_mg, weight_eg);
  print_feature(features::shelter_edge, weight_mg, weight_eg);
}
}  // namespace surveyor_tuner
