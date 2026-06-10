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
#include "history.hpp"
#include "position.hpp"
#include "repetition_table.hpp"
#include "score.hpp"
#include "search_controls.hpp"
#include "transposition_table.hpp"
#include "util/static_vector.hpp"

#include <thread>

namespace surveyor {

using line = static_vector<move, 512>;

struct search_limits {
  std::optional<time::milliseconds> wtime      = std::nullopt;
  std::optional<time::milliseconds> btime      = std::nullopt;
  std::optional<time::milliseconds> winc       = std::nullopt;
  std::optional<time::milliseconds> binc       = std::nullopt;
  std::optional<i32>                depth      = std::nullopt;
  std::optional<nodes>              node_limit = std::nullopt;
  bool                              infinite   = false;
};

class search_manager;

struct search_data {
  piece_to_history piece_to;
};

class searcher_base {
public:
  virtual ~searcher_base()                = default;
  virtual auto begin() -> void            = 0;
  virtual auto get_nodes() const -> nodes = 0;
  virtual auto get_depth() const -> i32   = 0;
};

template<search_controls Ctrls>
class searcher : public searcher_base {
public:
  template<typename... CtrlArgs>
  searcher(search_manager* shared, search_data& sd, CtrlArgs... ctrl_args)
      : m_ctrls(std::forward<CtrlArgs>(ctrl_args)...)
      , m_shared(shared)
      , m_sd(sd) {
  }

  auto begin() -> void final;

  auto get_nodes() const -> nodes final {
    return m_nodes;
  }

  auto get_depth() const -> i32 final {
    return m_depth;
  }

private:
  auto iterative_deepening() -> void;

  auto search(
    node_type expected, const position& pos, line& pv, score alpha, score beta, i32 depth, i32 ply)
    -> score;

  auto quiesce(node_type expected, const position& pos, line& pv, score alpha, score beta, i32 ply)
    -> score;

  auto make_move(const position& pos, move mv, i32 ply) -> position;

  auto make_null_move(const position& pos, i32 ply) -> position;

  auto unmake_move() -> void;

  Ctrls              m_ctrls;
  search_manager*    m_shared;
  nodes              m_nodes    = 0;
  i32                m_depth    = 0;
  i32                m_seldepth = 0;

  repetition_table m_repetition_table = {};

  search_data& m_sd;
};

class search_manager {
public:
  auto go(search_limits limits) -> void;

  auto resize_tt(usize mb) -> void {
    m_tt = tt::transposition_table(mb);
  }

  auto new_game() -> void {
    m_tt.clear();
    m_sd = {};
  }

  auto set_position(position pos, repetition_table) -> void;

  auto stop() -> void {
    m_stopped = true;
  }

  [[nodiscard]] auto stats() const -> search_stats {
    return {
      .node_limit   = m_searcher->get_nodes(),
      .current_time = time::clock::now(),
      .depth        = m_searcher->get_depth(),
    };
  }

  [[nodiscard]] auto get_nodes() const -> nodes {
    return m_searcher->get_nodes();
  }

  [[nodiscard]] auto stopped() const -> bool {
    return m_stopped;
  }

  [[nodiscard]] auto root() const -> std::tuple<position, repetition_table> {
    return {m_pos, m_repetitions};
  }

  [[nodiscard]] auto tt() -> tt::transposition_table& {
    return m_tt;
  }

  auto wait() -> void {
    if (m_thread.joinable()) {
      m_thread.join();
    }
  }

private:
  volatile std::atomic_bool m_stopped = false;

  std::jthread m_thread;
  search_data  m_sd;

  tt::transposition_table m_tt{16};

  std::unique_ptr<searcher_base> m_searcher = nullptr;
  position m_pos = position::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  repetition_table m_repetitions = {};
};

}  // namespace surveyor
