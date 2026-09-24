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

#ifndef SURVEYOR_TUNER_TYPES_H
#define SURVEYOR_TUNER_TYPES_H
#include "config.h"
#include "../lib/util/integer.h"

#include <functional>
#include <ranges>
#include <utility>
#include <vector>

namespace surveyor_tuner {
using namespace surveyor;

class evaltune_pair;

class globals {
public:
  static auto get() -> globals& {
    static globals instance;
    return instance;
  }

  [[nodiscard]] auto register_param() -> usize {
    return m_params++;
  }

  [[nodiscard]] auto params() const -> usize {
    return m_params;
  }

private:
  usize m_params{};
};

class evaltune_c {
public:
  static auto create(i32 mg, i32 eg) -> evaltune_c {
    const usize idx      = globals::get().register_param();
    const f64   mg_prime = static_cast<f64>(mg) / config::result_scale;
    const f64   eg_prime = static_cast<f64>(eg) / config::result_scale;
    return evaltune_c{mg_prime, eg_prime, idx};
  }

  [[nodiscard]] inline auto to_pair() const -> evaltune_pair;

  [[nodiscard]] auto idx() const -> usize {
    return m_idx;
  }

private:
  evaltune_c(f64 mg, f64 eg, usize idx)
      : m_mg{mg}
      , m_eg{eg}
      , m_idx{idx} {
  }

  mutable f64 m_mg{};
  mutable f64 m_eg{};
  usize       m_idx{};
};

class evaltune_pair {
public:
  evaltune_pair()
      : m_mg_vector(globals::get().params(), 0.0)
      , m_eg_vector(globals::get().params(), 0.0) {
  }

  evaltune_pair(f64 mg, f64 eg, usize idx)
      : m_mg_vector(globals::get().params(), 0.0)
      , m_eg_vector(globals::get().params(), 0.0) {
    m_mg_vector[idx] = mg;
    m_eg_vector[idx] = eg;
  }

  evaltune_pair(const std::vector<f64>& mg, const std::vector<f64>& eg)
      : m_mg_vector(mg)
      , m_eg_vector(eg) {
  }

  /* implicit */ evaltune_pair(const evaltune_c& c) {
    *this = c.to_pair();
  }

  [[nodiscard]] auto to_vector() const -> std::pair<std::vector<f64>, std::vector<f64>> {
    return {m_mg_vector, m_eg_vector};
  }

  friend auto operator+(const evaltune_pair& lhs, const evaltune_c& rhs) -> evaltune_pair {
    return lhs + rhs.to_pair();
  }

  friend auto operator+(const evaltune_pair& lhs, const evaltune_pair& rhs) -> evaltune_pair {
    namespace rg = std::ranges;
    namespace rv = std::views;

    const auto [lhs_mg, lhs_eg] = lhs.to_vector();
    const auto [rhs_mg, rhs_eg] = rhs.to_vector();

    const auto mg = rv::zip_transform(std::plus{}, lhs_mg, rhs_mg) | rg::to<std::vector>();
    const auto eg = rv::zip_transform(std::plus{}, lhs_eg, rhs_eg) | rg::to<std::vector>();

    return {mg, eg};
  }

  friend auto operator+=(evaltune_pair& lhs, const evaltune_c& rhs) -> evaltune_pair {
    return lhs += rhs.to_pair();
  }

  friend auto operator+=(evaltune_pair& lhs, const evaltune_pair& rhs) -> evaltune_pair {
    lhs = lhs + rhs;
    return lhs;
  }

  friend auto operator-(const evaltune_pair& lhs, const evaltune_c& rhs) -> evaltune_pair {
    return lhs - rhs.to_pair();
  }

  friend auto operator-(const evaltune_pair& lhs, const evaltune_pair& rhs) -> evaltune_pair {
    namespace rg = std::ranges;
    namespace rv = std::views;

    const auto [lhs_mg, lhs_eg] = lhs.to_vector();
    const auto [rhs_mg, rhs_eg] = rhs.to_vector();

    const auto mg = rv::zip_transform(std::minus{}, lhs_mg, rhs_mg) | rg::to<std::vector>();
    const auto eg = rv::zip_transform(std::minus{}, lhs_eg, rhs_eg) | rg::to<std::vector>();

    return {mg, eg};
  }

  friend auto operator-=(evaltune_pair& lhs, const evaltune_c& rhs) -> evaltune_pair {
    return lhs -= rhs.to_pair();
  }

  friend auto operator-=(evaltune_pair& lhs, const evaltune_pair& rhs) -> evaltune_pair {
    lhs = lhs - rhs;
    return lhs;
  }

  friend auto operator-(const evaltune_pair& p) -> evaltune_pair {
    return evaltune_pair{} - p;
  }

  [[nodiscard]] static auto phase(i32) -> i16 {
    return 0;
  }

private:
  std::vector<f64> m_mg_vector, m_eg_vector;
};

inline auto evaltune_c::to_pair() const -> evaltune_pair {
  return evaltune_pair{m_mg, m_eg, m_idx};
}

}  // namespace surveyor_tuner

#endif  // SURVEYOR_TUNER_TYPES_H
