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

#ifndef SURVEYOR_UCI_OUTPUT_H
#define SURVEYOR_UCI_OUTPUT_H
#include <surveyor/include.h>

namespace surveyor {

namespace uci_output_detail {

auto uci_stringify_pv(const line& l) -> std::string {
  std::string out;

  for (usize i = 0; i < l.size(); ++i) {
    out += std::format("{}", l[i]);

    if (i < l.size() - 1) {
      out += " ";
    }
  }

  return out;
}

}  // namespace uci_output_detail

class uci_output : public engine_output {
public:
  auto info(info_line info) -> void override {
    using namespace uci_output_detail;

    std::println("info depth {} score {} time {} nodes {} nps {} pv {}", info.depth,
                 scoring::to_uci(info.sc), time::cast<time::milliseconds>(info.elapsed).count(),
                 info.nodes, time::nps(info.nodes, info.elapsed), uci_stringify_pv(info.pv));
  }

  auto best_move(move mv) -> void override {
    std::println("bestmove {}", mv);
  }
};
}  // namespace surveyor

#endif  // SURVEYOR_UCI_OUTPUT_H
