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

#pragma once
#include "position.hpp"
#include "repetition_table.hpp"
#include "search.hpp"

#include <format>
#include <memory>
#include <string_view>

namespace surveyor {

struct uci_error {
  virtual ~uci_error() = default;

  [[nodiscard]] virtual auto msg() const -> std::string = 0;
};

struct uci_error_bad_cmd : uci_error {
  uci_error_bad_cmd(std::string_view cmd)
      : cmd(cmd) {
  }

  [[nodiscard]] auto msg() const -> std::string override {
    return std::format("bad command \"{}\".", cmd);
  }

  std::string cmd;
};

class uci {
public:
  auto loop() -> void;

private:
  auto dispatch_command(std::string_view command, std::istringstream& arguments)
    -> std::optional<std::unique_ptr<uci_error>>;

  auto execute_uci(std::istringstream& arguments) -> std::optional<std::unique_ptr<uci_error>>;
  auto execute_d(std::istringstream&) -> std::optional<std::unique_ptr<uci_error>>;
  auto execute_perft(std::istringstream& arguments) -> std::optional<std::unique_ptr<uci_error>>;
  auto execute_position(std::istringstream& arguments) -> std::optional<std::unique_ptr<uci_error>>;
  auto execute_go(std::istringstream& arguments) -> std::optional<std::unique_ptr<uci_error>>;
  auto execute_stop(std::istringstream&) -> std::optional<std::unique_ptr<uci_error>>;
  auto execute_bench(std::istringstream&) -> std::optional<std::unique_ptr<uci_error>>;
  auto execute_setoption(std::istringstream& arguments)
    -> std::optional<std::unique_ptr<uci_error>>;
  auto execute_testsee(std::istringstream&) -> std::optional<std::unique_ptr<uci_error>>;

  search_manager m_manager{};
  position m_pos = position::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  repetition_table m_repetitions{};
};

}  // namespace surveyor

template<>
struct std::formatter<surveyor::uci_error> : std::formatter<std::string> {
  auto format(const surveyor::uci_error& err, std::format_context& ctx) const {
    return std::formatter<std::string>::format(err.msg(), ctx);
  }
};
