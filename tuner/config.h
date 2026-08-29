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

#ifndef UCI_CONFIG_H
#define UCI_CONFIG_H
#include "util/common.h"

namespace surveyor_tuner::config {

constexpr usize epochs                    = 200;
constexpr usize initial_period_length     = 10;
constexpr usize batch_size                = 32;
constexpr f64   initial_learning_rate_max = 0.01;
constexpr f64   initial_learning_rate_min = 0.001;
constexpr f64   mu                        = 0.9;
constexpr f64   lambda                    = 1e-4;
constexpr i64   result_scale              = 300;


}  // namespace surveyor_tuner::config

#endif  // UCI_CONFIG_H
