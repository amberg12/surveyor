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

#include "data.h"
#include "util/filesystem.h"

#include <fstream>
#include <print>

auto main(int argc, char** argv) -> int {
  const std::string path = argv[1];
  std::ifstream     fin(path);

  std::vector<surveyor_tuner::game>           games     = surveyor_tuner::parse(fin);
  std::vector<surveyor_tuner::tuner_position> positions = surveyor_tuner::filter(games);

  std::println("Post Filtered Position Count: {}", positions.size());
}
