/*
  Surveyor - A UCI chess engine.
  Copyright (C) 2026 Amber Goulding

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "uci.hpp"

#include "move_generation.hpp"
#include "util/parse.hpp"

#include <iostream>
#include <print>
#include <sstream>

namespace surveyor {

auto uci::loop() -> void {
  std::string line, cmd;

  while (std::getline(std::cin, line)) {
    std::istringstream ss(line);
    ss >> cmd;

    const std::optional<std::unique_ptr<uci_error>> err = dispatch_command(cmd, ss);

    if (err) {
      std::println("Error: {}", **err);
    }
  }
}

auto uci::dispatch_command(std::string_view command, std::istringstream& arguments)
  -> std::optional<std::unique_ptr<uci_error>> {
  if (command == "uci") {
    return execute_uci(arguments);
  }

  if (command == "d") {
    return execute_d(arguments);
  }

  if (command == "perft") {
    return execute_perft(arguments);
  }

  if (command == "position") {
    return execute_position(arguments);
  }

  if (command == "go") {
    return execute_go(arguments);
  }

  return std::make_unique<uci_error_bad_cmd>(command);
}

auto uci::execute_uci(std::istringstream& arguments) -> std::optional<std::unique_ptr<uci_error>> {
  (void)arguments;
  std::println("id name Surveyor");
  std::println("id author Amber Goulding");
  std::println("uciok");
  return std::nullopt;
}

auto uci::execute_d(std::istringstream&) -> std::optional<std::unique_ptr<uci_error>> {
  std::println("{}", m_pos);
  return std::nullopt;
}

auto uci::execute_perft(std::istringstream& arguments)
  -> std::optional<std::unique_ptr<uci_error>> {
  std::string tok;
  arguments >> tok;

  perft_settings ps = perft_settings::standard;

  if (tok == "bulk") {
    ps = perft_settings::bulk;
    arguments >> tok;
  }

  const auto depth = parse_number<i32>(tok);

  if (depth.has_value()) {
    if (ps == perft_settings::standard) {
      perft<perft_settings::standard, true>(m_pos, *depth);
    } else {
      perft<perft_settings::bulk, true>(m_pos, *depth);
    }
  }

  return std::nullopt;
}

auto uci::execute_position(std::istringstream& arguments)
  -> std::optional<std::unique_ptr<uci_error>> {
  std::string tok;

  arguments >> tok;

  const std::string fen = [&] -> std::string {
    if (tok == "startpos") {
      return "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    }

    std::string out;

    for (int i = 0; i < 6; ++i) {
      arguments >> tok;
      out += tok + " ";
    }

    return out;
  }();

  m_pos = position::parse(fen);
  arguments >> tok /* moves */;

  while (arguments >> tok) {
    const move m = move::parse(tok, m_pos);
    m_pos        = m_pos.make_move(m);
  }

  return std::nullopt;
}

auto uci::execute_go(std::istringstream& arguments) -> std::optional<std::unique_ptr<uci_error>> {
  std::string tok;
  m_manager.set_position(m_pos);

  search_limits limits;

  while (arguments >> tok) {
    if (tok == "infinite") {
      limits.infinite = true;
    }

    if (tok == "depth") {
      i32 depth;
      arguments >> depth;
      limits.depth = depth;
    }

    if (tok == "nodes") {
      nodes n;
      arguments >> n;
      limits.node_limit = n;
    }

    if (tok == "wtime") {
      u64 n;
      arguments >> n;
      limits.wtime = time::milliseconds{n};
    }

    if (tok == "btime") {
      u64 n;
      arguments >> n;
      limits.btime = time::milliseconds{n};
    }

    if (tok == "winc") {
      u64 n;
      arguments >> n;
      limits.winc = time::milliseconds{n};
    }

    if (tok == "binc") {
      u64 n;
      arguments >> n;
      limits.binc = time::milliseconds{n};
    }
  }

  while (arguments >> tok)
    ;

  m_manager.go(limits);

  return std::nullopt;
}

}  // namespace surveyor
