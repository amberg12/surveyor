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

#ifndef SURVEYOR_BENCH_OUTPUT_H
#define SURVEYOR_BENCH_OUTPUT_H
#include <iostream>
#include <print>
#include <surveyor/include.h>

namespace surveyor {
class bench_output final : public engine_output {
public:
  u64 current_nodes = 0;
  u64 total_nodes   = 0;

  i32 current_fen = 0;
  i32 total_fens  = 0;

  time::time_point start_time;

  auto info(info_line info) -> void override {
    current_nodes = info.nodes;
  }

  auto best_move(move mv) -> void override {
    total_nodes += current_nodes;
    current_nodes = 0;

    ++current_fen;

    std::print("\r{}/{}", current_fen, total_fens);
    std::flush(std::cout);

    if (current_fen == total_fens) {
      const u64 nps = time::nps(total_nodes, time::clock::now() - start_time);
      std::println();
      std::println("nodes {} nps {}", total_nodes, nps);
    }
  }
};
}  // namespace surveyor
#endif  // SURVEYOR_BENCH_OUTPUT_H
