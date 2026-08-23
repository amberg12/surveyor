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

#ifndef SURVEYOR_INTERFACE
#define SURVEYOR_INTERFACE

#include <print>
#include <string_view>
#include <surveyor/include.h>

namespace surveyor {
class interface {
public:
  interface();
  auto parse_command(std::string_view command) -> void;

private:
  auto uci_parse_command(std::string_view command) -> void;

  auto uci_perft(tokenizer& toks) -> void;
  auto uci_position(tokenizer& toks) -> void;
  auto uci_uci(tokenizer& toks) -> void;
  auto uci_go(tokenizer& toks) -> void;
  auto uci_stop(tokenizer& toks) -> void;
  auto uci_ucinewgame(tokenizer& toks) -> void;
  auto uci_isready(tokenizer& toks) -> void;
  auto uci_bench(tokenizer& toks) -> void;
  auto uci_setoption(tokenizer& toks) -> void;

  template<typename... Args>
  auto uci_print_error(std::string_view cmd, std::format_string<Args...> fmt, Args&&... args)
    -> void {
    std::println("info string {}: {}", cmd, std::format(fmt, args...));
  }

  auto uci_print_bad_token(std::string_view cmd, std::string_view tok) -> void {
    uci_print_error(cmd, "unknown token: {}", tok);
  }

  game   m_game{position::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")};
  engine m_engine;

  bool m_soft_nodes = false;
};

}  // namespace surveyor

#endif  // SURVEYOR_INTERFACE
