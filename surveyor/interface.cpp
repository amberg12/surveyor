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

#include "bench_output.h"
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
  } else if (cmd == "bench") {
    uci_bench(toks);
  } else if (cmd == "setoption") {
    uci_setoption(toks);
  } else {
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
  bool         is_ctrls_set = false;

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

    if (name == "depth") {
      if (!is_ctrls_set) {
        c.emplace<ctrls::depth>();
        is_ctrls_set = true;
      }

      if (!std::holds_alternative<ctrls::depth>(c)) {
        uci_print_error("go", "depth is incompatible with the other arguments");
        return;
      }

      std::get<ctrls::depth>(c).soft_depth = parsed_number;
      continue;
    }

    if (name == "harddepth") {
      if (!is_ctrls_set) {
        c.emplace<ctrls::depth>();
        is_ctrls_set = true;
      }

      if (!std::holds_alternative<ctrls::depth>(c)) {
        uci_print_error("go", "harddepth is incompatible with the other arguments");
        return;
      }

      std::get<ctrls::depth>(c).hard_depth = parsed_number;
      continue;
    }

    if (name == "wtime") {
      if (!is_ctrls_set) {
        c.emplace<ctrls::clock>();
        is_ctrls_set = true;
      }

      if (!std::holds_alternative<ctrls::clock>(c)) {
        uci_print_error("go", "wtime is incompatible with the other arguments");
        return;
      }

      if (m_game.root().stm() != color::white()) {
        continue;
      }

      std::get<ctrls::clock>(c).t = time::milliseconds{parsed_number};
      continue;
    }

    if (name == "btime") {
      if (!is_ctrls_set) {
        c.emplace<ctrls::clock>();
        is_ctrls_set = true;
      }

      if (!std::holds_alternative<ctrls::clock>(c)) {
        uci_print_error("go", "btime is incompatible with the other arguments");
        return;
      }

      if (m_game.root().stm() != color::black()) {
        continue;
      }

      std::get<ctrls::clock>(c).t = time::milliseconds{parsed_number};
      continue;
    }

    if (name == "winc") {
      if (!is_ctrls_set) {
        c.emplace<ctrls::clock>();
        is_ctrls_set = true;
      }

      if (!std::holds_alternative<ctrls::clock>(c)) {
        uci_print_error("go", "winc is incompatible with the other arguments");
        return;
      }

      if (m_game.root().stm() != color::white()) {
        continue;
      }

      std::get<ctrls::clock>(c).i = time::milliseconds{parsed_number};
      continue;
    }

    if (name == "binc") {
      if (!is_ctrls_set) {
        c.emplace<ctrls::clock>();
        is_ctrls_set = true;
      }

      if (!std::holds_alternative<ctrls::clock>(c)) {
        uci_print_error("go", "wtime is incompatible with the other arguments");
        return;
      }

      if (m_game.root().stm() != color::black()) {
        continue;
      }

      std::get<ctrls::clock>(c).i = time::milliseconds{parsed_number};
      continue;
    }

    uci_print_error("go", "{} is an unknown argument", *name);
    return;
  }

  std::visit(
    [&](auto& x) {
      x.start_time = now;
    },
    c);

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

auto interface::uci_bench(tokenizer& toks) -> void {
  const std::array<std::string, 53> fens = {{
    "r3k2r/2pb1ppp/2pp1q2/p7/1nP1B3/1P2P3/P2N1PPP/R2QK2R w KQkq a6 0 14",
    "4rrk1/2p1b1p1/p1p3q1/4p3/2P2n1p/1P1NR2P/PB3PP1/3R1QK1 b - - 2 24",
    "r3qbrk/6p1/2b2pPp/p3pP1Q/PpPpP2P/3P1B2/2PB3K/R5R1 w - - 16 42",
    "6k1/1R3p2/6p1/2Bp3p/3P2q1/P7/1P2rQ1K/5R2 b - - 4 44",
    "8/8/1p2k1p1/3p3p/1p1P1P1P/1P2PK2/8/8 w - - 3 54",
    "7r/2p3k1/1p1p1qp1/1P1Bp3/p1P2r1P/P7/4R3/Q4RK1 w - - 0 36",
    "r1bq1rk1/pp2b1pp/n1pp1n2/3P1p2/2P1p3/2N1P2N/PP2BPPP/R1BQ1RK1 b - - 2 10",
    "3r3k/2r4p/1p1b3q/p4P2/P2Pp3/1B2P3/3BQ1RP/6K1 w - - 3 87",
    "2r4r/1p4k1/1Pnp4/3Qb1pq/8/4BpPp/5P2/2RR1BK1 w - - 0 42",
    "4q1bk/6b1/7p/p1p4p/PNPpP2P/KN4P1/3Q4/4R3 b - - 0 37",
    "2q3r1/1r2pk2/pp3pp1/2pP3p/P1Pb1BbP/1P4Q1/R3NPP1/4R1K1 w - - 2 34",
    "1r2r2k/1b4q1/pp5p/2pPp1p1/P3Pn2/1P1B1Q1P/2R3P1/4BR1K b - - 1 37",
    "r3kbbr/pp1n1p1P/3ppnp1/q5N1/1P1pP3/P1N1B3/2P1QP2/R3KB1R b KQkq b3 0 17",
    "8/6pk/2b1Rp2/3r4/1R1B2PP/P5K1/8/2r5 b - - 16 42",
    "1r4k1/4ppb1/2n1b1qp/pB4p1/1n1BP1P1/7P/2PNQPK1/3RN3 w - - 8 29",
    "8/p2B4/PkP5/4p1pK/4Pb1p/5P2/8/8 w - - 29 68",
    "3r4/ppq1ppkp/4bnp1/2pN4/2P1P3/1P4P1/PQ3PBP/R4K2 b - - 2 20",
    "5rr1/4n2k/4q2P/P1P2n2/3B1p2/4pP2/2N1P3/1RR1K2Q w - - 1 49",
    "1r5k/2pq2p1/3p3p/p1pP4/4QP2/PP1R3P/6PK/8 w - - 1 51",
    "q5k1/5ppp/1r3bn1/1B6/P1N2P2/BQ2P1P1/5K1P/8 b - - 2 34",
    "r1b2k1r/5n2/p4q2/1ppn1Pp1/3pp1p1/NP2P3/P1PPBK2/1RQN2R1 w - - 0 22",
    "r1bqk2r/pppp1ppp/5n2/4b3/4P3/P1N5/1PP2PPP/R1BQKB1R w KQkq - 0 5",
    "r1bqr1k1/pp1p1ppp/2p5/8/3N1Q2/P2BB3/1PP2PPP/R3K2n b Q - 1 12",
    "r1bq2k1/p4r1p/1pp2pp1/3p4/1P1B3Q/P2B1N2/2P3PP/4R1K1 b - - 2 19",
    "r4qk1/6r1/1p4p1/2ppBbN1/1p5Q/P7/2P3PP/5RK1 w - - 2 25",
    "r7/6k1/1p6/2pp1p2/7Q/8/p1P2K1P/8 w - - 0 32",
    "r3k2r/ppp1pp1p/2nqb1pn/3p4/4P3/2PP4/PP1NBPPP/R2QK1NR w KQkq - 1 5",
    "3r1rk1/1pp1pn1p/p1n1q1p1/3p4/Q3P3/2P5/PP1NBPPP/4RRK1 w - - 0 12",
    "5rk1/1pp1pn1p/p3Brp1/8/1n6/5N2/PP3PPP/2R2RK1 w - - 2 20",
    "8/1p2pk1p/p1p1r1p1/3n4/8/5R2/PP3PPP/4R1K1 b - - 3 27",
    "8/4pk2/1p1r2p1/p1p4p/Pn5P/3R4/1P3PP1/4RK2 w - - 1 33",
    "8/5k2/1pnrp1p1/p1p4p/P6P/4R1PK/1P3P2/4R3 b - - 1 38",
    "8/8/1p1kp1p1/p1pr1n1p/P6P/1R4P1/1P3PK1/1R6 b - - 15 45",
    "8/8/1p1k2p1/p1prp2p/P2n3P/6P1/1P1R1PK1/4R3 b - - 5 49",
    "8/8/1p4p1/p1p2k1p/P2npP1P/4K1P1/1P6/3R4 w - - 6 54",
    "8/8/1p4p1/p1p2k1p/P2n1P1P/4K1P1/1P6/6R1 b - - 6 59",
    "8/5k2/1p4p1/p1pK3p/P2n1P1P/6P1/1P6/4R3 b - - 14 63",
    "8/1R6/1p1K1kp1/p6p/P1p2P1P/6P1/1Pn5/8 w - - 0 67",
    "1rb1rn1k/p3q1bp/2p3p1/2p1p3/2P1P2N/PP1RQNP1/1B3P2/4R1K1 b - - 4 23",
    "4rrk1/pp1n1pp1/q5p1/P1pP4/2n3P1/7P/1P3PB1/R1BQ1RK1 w - - 3 22",
    "r2qr1k1/pb1nbppp/1pn1p3/2ppP3/3P4/2PB1NN1/PP3PPP/R1BQR1K1 w - - 4 12",
    "2r2k2/8/4P1R1/1p6/8/P4K1N/7b/2B5 b - - 0 55",
    "6k1/5pp1/8/2bKP2P/2P5/p4PNb/B7/8 b - - 1 44",
    "2rqr1k1/1p3p1p/p2p2p1/P1nPb3/2B1P3/5P2/1PQ2NPP/R1R4K w - - 3 25",
    "r1b2rk1/p1q1ppbp/6p1/2Q5/8/4BP2/PPP3PP/2KR1B1R b - - 2 14",
    "6r1/5k2/p1b1r2p/1pB1p1p1/1Pp3PP/2P1R1K1/2P2P2/3R4 w - - 1 36",
    "rnbqkb1r/pppppppp/5n2/8/2PP4/8/PP2PPPP/RNBQKBNR b KQkq c3 0 2",
    "2rr2k1/1p4bp/p1q1p1p1/4Pp1n/2PB4/1PN3P1/P3Q2P/2RR2K1 w - f6 0 20",
    "3br1k1/p1pn3p/1p3n2/5pNq/2P1p3/1PN3PP/P2Q1PB1/4R1K1 w - - 0 23",
    "2r2b2/5p2/5k2/p1r1pP2/P2pB3/1P3P2/K1P3R1/7R w - - 23 93",
    "q6k/8/5p2/5Q1P/6P1/8/5P1K/8 b - - 0 1",
    "3R4/5k2/7K/7P/8/3b4/8/8 b - - 0 1",
    "2r2n2/8/3k4/8/8/4KN2/8/6R1 w - - 0 1",
  }};

  ctrls::depth depth = {.soft_depth = 13};

  auto output        = std::make_shared<bench_output>();
  output->total_fens = fens.size();
  output->start_time = time::clock::now();

  engine bench_engine;
  bench_engine.set_output(output);

  for (const auto fen : fens) {
    const game g{position::parse(fen)};

    bench_engine.go(g, depth);
    bench_engine.await();
    bench_engine.reset();
  }
}

auto interface::uci_setoption(tokenizer& toks) -> void {
  const auto consume_name = toks.next();

  if (!consume_name.has_value()) {
    uci_print_error("setoption", "missing name");
    return;
  }

  if (consume_name != "name") {
    uci_print_bad_token("setoption", *consume_name);
    return;
  }

  const auto name = toks.next();

  const auto consume_value = toks.next();

  if (!consume_value.has_value()) {
    uci_print_error("setoption", "missing value");
    return;
  }

  if (consume_value != "value") {
    uci_print_bad_token("setoption", *consume_value);
    return;
  }

  const auto value = toks.next();

  if (name == "Hash") {
    if (!value.has_value()) {
      uci_print_error("setoption", "missing hash size");
      return;
    }

    if (!parse_number<u64>(*value)) {
      uci_print_bad_token("setoption", *value);
      return;
    }

    m_engine.resize_hash(*parse_number<u64>(*value));
  } else if (!name.has_value()) {
    uci_print_error("setoption", "missing name");
  } else {
    uci_print_error("setoption", "unknown option: {}", *name);
  }
}

}  // namespace surveyor
