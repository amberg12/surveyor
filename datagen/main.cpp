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

#include "common.h"
#include "datagen_manager.h"

auto main(int argc, char** argv) -> int {
  const surveyor::usize concurrency = *surveyor::parse_number<surveyor::usize>(argv[1]);
  const surveyor::i64   games       = *surveyor::parse_number<surveyor::i64>(argv[2]);

  auto manager = surveyor_datagen::manager{concurrency, games};
  manager.run();
}
