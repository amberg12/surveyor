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

#ifndef SURVEYOR_EVAL_TYPES_H
#define SURVEYOR_EVAL_TYPES_H
#include "score.h"
#include "util/integer.h"

#ifdef EVALTUNE
#include "./../tuner/tuner_types.h"
using namespace surveyor_tuner;
#endif

namespace surveyor {

#ifdef EVALTUNE

using pair = evaltune_c;

using out_pair = evaltune_pair;

#define S(mg, eg) evaltune_c::create(mg, eg)

#else
class pair {
public:
  constexpr pair() = default;

  constexpr pair(i32 mg, i32 eg) : m_mg(mg), m_eg(eg) {
  }

  [[nodiscard]] constexpr auto mg() const {
    return m_mg;
  }

  [[nodiscard]] constexpr auto eg() const {
    return m_eg;
  }

  friend auto operator+(const pair& lhs, const pair& rhs) -> pair {
    return {lhs.m_mg + rhs.m_mg, lhs.m_eg + rhs.m_eg};
  }

  friend auto operator += (pair& lhs, const pair& rhs) -> pair {
    lhs = lhs + rhs;
    return lhs;
  }

  friend auto operator-(const pair& lhs, const pair& rhs) -> pair {
    return {lhs.m_mg - rhs.m_mg, lhs.m_eg - rhs.m_eg};
  }

  friend auto operator-=(pair& lhs, const pair& rhs) -> pair {
    lhs = lhs - rhs;
    return lhs;
  }

  friend auto operator-(const pair& p) -> pair {
    return pair{} - p;
  }

  auto phase(const i32 phase) const -> score {
    const auto mg = m_mg * phase;
    const auto eg = m_eg * (24 - phase);
    return (mg + eg) / 24;
  }

private:
  i32 m_mg;
  i32 m_eg;
};

using out_pair = pair;

#define S(mg, eg) pair(mg, eg)

#endif

}


#endif  // SURVEYOR_EVAL_TYPES_H
