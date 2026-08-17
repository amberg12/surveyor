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

namespace surveyor {
auto interface::parse_command(std::string_view command) -> void {
  uci_parse_command(command);
}

auto interface::uci_parse_command(std::string_view command) -> void {
  tokenizer toks{command};

  const std::optional<std::string> cmd = toks.next();

  if (cmd == "uci") {
    uci_uci(toks);
  } else {
    if (cmd.has_value()) {
      uci_print_error(*cmd, "unknown command");
    }
  }
}

auto interface::uci_uci(tokenizer& toks) -> void {
  std::println("id name surveyor");
  std::println("id author Amber Goulding");
  std::println("uciok");
}
} // surveyor