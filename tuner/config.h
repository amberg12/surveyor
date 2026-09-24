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
#include <cstddef>
#include <cstdint>
namespace surveyor_tuner::config {

constexpr size_t  epochs                    = 25;
constexpr size_t  initial_period_length     = 10;
constexpr size_t  batch_size                = 32;
constexpr double  initial_learning_rate_max = 0.01;
constexpr double  initial_learning_rate_min = 0.001;
constexpr double  mu                        = 0.9;
constexpr double  lambda                    = 1e-4;
constexpr int64_t result_scale              = 300;


}  // namespace surveyor_tuner::config

#endif  // UCI_CONFIG_H
