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

#include "uci_output.h"

namespace surveyor {

interface::interface() {
  std::shared_ptr<engine_output> output = std::make_unique<uci_output>();
  m_engine.set_output(output);
}

auto interface::parse_command(std::string_view command) -> void {
  uci_parse_command(command);
}

auto interface::uci_parse_command(std::string_view command) -> void {
  tokenizer toks{command};

  const std::optional<std::string> cmd = toks.next();

  if (cmd == "uci") {
    uci_uci(toks);
  } else if (cmd == "go") {
    uci_go(toks);
  } else if (cmd == "perft") {
    uci_perft(toks);
  } else if (cmd == "position") {
    uci_position(toks);
  } else if (cmd == "stop") {
    uci_stop(toks);
  } else if (cmd == "ucinewgame") {
    uci_ucinewgame(toks);
  } else if (cmd == "isready") {
    uci_isready(toks);
  }
    else {
    if (cmd.has_value()) {
      uci_print_error(*cmd, "unknown command");
    }
  }
}

auto interface::uci_perft(tokenizer& toks) -> void {
  const std::optional<std::string> perft_depth_tok = toks.next();

  if (!perft_depth_tok.has_value()) {
    uci_print_error("perft", "missing depth");
    return;
  }

  const std::optional<u64> perft_depth = parse_number<u64>(*perft_depth_tok);

  if (!perft_depth.has_value()) {
    uci_print_error("perft", "bad number: {}", *perft_depth_tok);
    return;
  }

  if (*perft_depth <= 0) {
    uci_print_error("perft", "bad number: {}", *perft_depth_tok);
    return;
  }

  const std::optional<std::string> perft_type = toks.next();

  const auto start = time::clock::now();

  const auto total_perft_nodes = [&] -> std::optional<u64> {
    if (!perft_type.has_value() || perft_type == "standard") {
      return perft::standard(m_game.root(), *perft_depth);
    }

    return std::nullopt;
  }();

  if (!total_perft_nodes.has_value()) {
    uci_print_error("perft", "invalid perft type");
    return;
  }

  const auto duration = time::clock::now() - start;

  std::println("total nodes: {}", *total_perft_nodes);
  std::println("nps: {}", time::nps(*total_perft_nodes, duration));
  std::println("duration: {}", time::cast<time::milliseconds>(duration));
}

auto interface::uci_position(tokenizer& toks) -> void {
  const std::optional<std::string> pos_type = toks.next();

  if (!pos_type.has_value()) {
    uci_print_error("position", "no position provided");
  }

  if (pos_type == "startpos") {
    m_game = game{position::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")};
  } else if (pos_type == "fen") {
    const std::optional<std::string> board      = toks.next();
    const std::optional<std::string> color      = toks.next();
    const std::optional<std::string> castle     = toks.next();
    const std::optional<std::string> en_passant = toks.next();
    const std::optional<std::string> move_rule  = toks.next();
    const std::optional<std::string> ply        = toks.next();

    std::string fen;

#define SURVEYOR_ADD_FEN_PART(part)                       \
  if (part.has_value())                                   \
    fen += *part;                                         \
  else                                                    \
    return uci_print_error("position", "missing " #part);

    SURVEYOR_ADD_FEN_PART(board);
    SURVEYOR_ADD_FEN_PART(color);
    SURVEYOR_ADD_FEN_PART(castle);
    SURVEYOR_ADD_FEN_PART(en_passant);
    SURVEYOR_ADD_FEN_PART(move_rule);
    SURVEYOR_ADD_FEN_PART(ply);

#undef SURVEYOR_ADD_FEN_PART

    m_game = game{position::parse(fen)};
  } else {
    uci_print_bad_token("position", *pos_type);
  }

  const std::optional<std::string> move_marker = toks.next();

  if (!move_marker.has_value()) {
    return;
  }

  if (move_marker != "moves") {
    uci_print_bad_token("position", *move_marker);
    return;
  }

  for (auto mv_tok = toks.next(); mv_tok.has_value(); mv_tok = toks.next()) {
    const auto mv = move::parse(*mv_tok, m_game.root());

    m_game.add_move(mv);
  }
}

auto interface::uci_uci(tokenizer& toks) -> void {
  std::println("id name surveyor");
  std::println("id author Amber Goulding");
  std::println("uciok");
}

auto interface::uci_go(tokenizer& toks) -> void {
  const time::time_point now = time::clock::now();

  ctrls::ctrls c;
  bool is_ctrls_set = false;

  for (auto name = toks.next(); name.has_value(); name = toks.next()) {
    if (name == "infinite") {
      is_ctrls_set = true;
      continue;
    }

    const auto value = toks.next();

    if (!value.has_value()) {
      uci_print_error("go", "{} is missing a value", *name);
      return;
    }

    if (!parse_number<u64>(*value).has_value()) {
      uci_print_error("go", "{} is an invalid argument to {}", *value, *name);
      return;
    }

    const u64 parsed_number = *parse_number<u64>(*value);

    if (name == "nodes") {
      if (!is_ctrls_set) {
        c.emplace<ctrls::nodes>();
        is_ctrls_set = true;
      }

      if (!std::holds_alternative<ctrls::nodes>(c)) {
        uci_print_error("go", "nodes is incompatible with the other arguments");
        return;
      }

      std::get<ctrls::nodes>(c).hard_nodes = parsed_number;
      continue;
    }

    if (name == "softnodes") {
      if (!is_ctrls_set) {
        c.emplace<ctrls::nodes>();
        is_ctrls_set = true;
      }

      if (!std::holds_alternative<ctrls::nodes>(c)) {
        uci_print_error("go", "softnodes is incompatible with the other arguments");
        return;
      }

      std::get<ctrls::nodes>(c).soft_nodes = parsed_number;
      continue;
    }

    if (name == "movetime") {
      if (!is_ctrls_set) {
        c.emplace<ctrls::fixed_time>();
        is_ctrls_set = true;
      }

      if (!std::holds_alternative<ctrls::fixed_time>(c)) {
        uci_print_error("go", "movetime is incompatible with the other arguments");
        return;
      }

      std::get<ctrls::fixed_time>(c).hard_time = time::milliseconds{parsed_number};
      continue;
    }

    if (name == "softmovetime") {
      if (!is_ctrls_set) {
        c.emplace<ctrls::fixed_time>();
        is_ctrls_set = true;
      }

      if (!std::holds_alternative<ctrls::fixed_time>(c)) {
        uci_print_error("go", "softmovetime is incompatible with the other arguments");
        return;
      }

      std::get<ctrls::fixed_time>(c).soft_time = time::milliseconds{parsed_number};
      continue;
    }

    uci_print_error("go", "{} is an unknown argument", *name);
    return;
  }

  std::visit([&](auto& x) {
    x.start_time = now;
  }, c);

  m_engine.go(m_game, c);
}

auto interface::uci_stop(tokenizer& toks) -> void {
  m_engine.stop();
}

auto interface::uci_ucinewgame(tokenizer& toks) -> void {
  m_engine.reset();
}

auto interface::uci_isready(tokenizer& toks) -> void {
  std::println("readyok");
}

}  // namespace surveyor
