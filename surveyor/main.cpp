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

#include "interface.h"

#include <iostream>

auto main(int argc, char** argv) -> int {
  surveyor::interface interface{};

  if (argc > 1) {
    for (surveyor::i32 i = 1; i < argc; ++i) {
      interface.parse_command(argv[i]);
    }

    return 0;
  }

  std::string line;

  while (std::getline(std::cin, line)) {
    interface.parse_command(line);
  }
}
