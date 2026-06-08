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

#include "../evaluate.hpp"
#include "../position.hpp"
#include "../util/integer.hpp"

#include <cmath>
#include <filesystem>
#include <fstream>
#include <print>
#include <random>
#include <utility>

using namespace surveyor;

namespace surveyor_tuner {

enum class feature_idx {
  pawn_material,
  pawn_psqt,
  knight_material = pawn_psqt + 48,
  knight_psqt,
  bishop_material = knight_psqt + 64,
  bishop_psqt,
  rook_material = bishop_psqt + 64,
  rook_psqt,
  queen_material = rook_psqt + 64,
  queen_psqt,
  king_psqt = queen_psqt + 64,
  nb        = king_psqt + 64,
};

template<typename T>
using weights = std::array<T, static_cast<usize>(feature_idx::nb)>;

struct feature_trace {
  weights<i8> w{};

  static constexpr auto i(color stm) -> i8 {
    return stm == color::white() ? 1 : -1;
  }

  auto trace_pawn_material(color stm) -> void {
    w[static_cast<usize>(feature_idx::pawn_material)] += i(stm);
  }

  auto trace_pawn_psqt(color stm, square sq) -> void {
    w[static_cast<usize>(feature_idx::pawn_psqt) + sq.relative(stm).idx - 8] += i(stm);
  }

  auto trace_knight_material(color stm) -> void {
    w[static_cast<usize>(feature_idx::knight_material)] += i(stm);
  }

  auto trace_knight_psqt(color stm, square sq) -> void {
    w[static_cast<usize>(feature_idx::knight_psqt) + sq.relative(stm).idx] += i(stm);
  }

  auto trace_bishop_material(color stm) -> void {
    w[static_cast<usize>(feature_idx::bishop_material)] += i(stm);
  }

  auto trace_bishop_psqt(color stm, square sq) -> void {
    w[static_cast<usize>(feature_idx::bishop_psqt) + sq.relative(stm).idx] += i(stm);
  }

  auto trace_rook_material(color stm) -> void {
    w[static_cast<usize>(feature_idx::rook_material)] += i(stm);
  }

  auto trace_rook_psqt(color stm, square sq) -> void {
    w[static_cast<usize>(feature_idx::rook_psqt) + sq.relative(stm).idx] += i(stm);
  }

  auto trace_queen_material(color stm) -> void {
    w[static_cast<usize>(feature_idx::queen_material)] += i(stm);
  }

  auto trace_queen_psqt(color stm, square sq) -> void {
    w[static_cast<usize>(feature_idx::queen_psqt) + sq.relative(stm).idx] += i(stm);
  }

  auto trace_king_psqt(color stm, square sq) -> void {
    w[static_cast<usize>(feature_idx::king_psqt) + sq.relative(stm).idx] += i(stm);
  }
};

struct dataset_entry {
  enum result {
    black,
    white,
    draw,
  };

  std::string fen;
  result      r{};
};

auto load_dataset(const std::filesystem::path& path) -> std::vector<dataset_entry> {
  std::ifstream              file(path);
  std::string                line, tok;
  std::vector<dataset_entry> dataset;
  dataset.reserve(1'000'000);

  while (std::getline(file, line)) {
    dataset_entry      entry;
    std::istringstream ss(line);

    while (ss >> tok) {
      if (tok == "[0.0]") {
        entry.r = dataset_entry::black;
      } else if (tok == "[0.5]") {
        entry.r = dataset_entry::draw;
      } else if (tok == "[1.0]") {
        entry.r = dataset_entry::white;
      } else {
        entry.fen += tok + " ";
      }
    }

    dataset.emplace_back(entry);
  }

  return std::move(dataset);
}

auto tune(std::vector<dataset_entry>& ds,
          i32                         epochs,
          f64                         lr,
          f64                         beta_1,
          f64                         beta_2,
          f64                         eps,
          f64                         lambda,
          i32                         batch_size) -> void {
  constexpr i32 result_scale = 300;
  weights<f64>  w_mg;
  weights<f64>  w_eg;
  weights<f64>  grad_mg;
  weights<f64>  grad_eg;
  feature_trace xi;
  weights<f64>  w_mg_prev;
  weights<f64>  w_eg_prev;
  weights<f64>  m_mg;
  weights<f64>  m_eg;
  weights<f64>  v_mg;
  weights<f64>  v_eg;

  time::time_point start_time = time::clock::now();

  i32 t      = 0;
  f64 bias   = 0.0;
  i32 T      = 20;
  f64 lr_min = 0.0001;
  f64 lr_max = 0.001;
  i32 tc     = 0;

  for (i32 epoch = 0; epoch < epochs; ++epoch) {
    if (tc == T) {
      T *= 2;
      tc = 0;
      lr_max *= 0.8;
      lr_min *= 0.8;
    }

    f64 local_lr = lr_min + 0.5 * (lr_max - lr_min) * (1 + std::cos(std::numbers::pi * tc / T));

    std::shuffle(ds.begin(), ds.end(), std::random_device{});

    grad_mg = {};
    grad_eg = {};

    i32 batch_pos = 0;

    f64 ge_mean_mg = 0.0;
    f64 ge_mean_eg = 0.0;

    for (i32 k = 0; k < ds.size(); ++k) {
      xi = {};

      dataset_entry e = ds[k];

      const position pos = position::parse(e.fen);
      trace_eval(pos, xi);

      f64 phase = static_cast<f64>(pos.phase()) / static_cast<f64>(position::max_phase);

      f64 dot_mg = 0, dot_eg = 0;

      for (i32 i = 0; i < static_cast<usize>(feature_idx::nb); ++i) {
        dot_mg += w_mg[i] * xi.w[i];
        dot_eg += w_eg[i] * xi.w[i];
      }

      f64 eval = phase * dot_mg + (1 - phase) * dot_eg;
      f64 p    = 1.0 / (1.0 + std::exp(-eval));

      f64 diff = [&] {
        f64 result;
        switch (e.r) {
        case dataset_entry::black:
          result = 0.0;
          break;
        case dataset_entry::draw:
          result = 0.5;
          break;
        case dataset_entry::white:
          result = 1.0;
          break;
        default:
          std::unreachable();
        }

        return p - result;
      }();

      for (i32 i = 0; i < static_cast<usize>(feature_idx::nb); ++i) {
        grad_mg[i] += diff * phase * xi.w[i];
        grad_eg[i] += diff * (1.0 - phase) * xi.w[i];
      }

      ++batch_pos;

      if (batch_pos == batch_size || k == ds.size() - 1) {
        t += 1;
        f64 b_corr_1 = std::pow(beta_1, t);
        f64 b_corr_2 = std::pow(beta_2, t);
        f64 inv_bs   = 1.0 / static_cast<f64>(batch_pos);

        for (i32 i = 0; i < static_cast<usize>(feature_idx::nb); ++i) {
          f64 g_mg = grad_mg[i] * inv_bs;
          f64 g_eg = grad_eg[i] * inv_bs;

          m_mg[i] = beta_1 * m_mg[i] + (1.0 - beta_1) * g_mg;
          v_mg[i] = beta_2 * v_mg[i] + (1.0 - beta_2) * (g_mg * g_mg);

          f64 mcorr_mg = m_mg[i] / (1.0 - b_corr_1);
          f64 vcorr_mg = v_mg[i] / (1.0 - b_corr_2);

          w_mg[i] -= local_lr * (mcorr_mg / (sqrt(vcorr_mg) + eps) + lambda * w_mg[i]);

          m_eg[i] = beta_1 * m_eg[i] + (1.0 - beta_1) * g_eg;
          v_eg[i] = beta_2 * v_eg[i] + (1.0 - beta_2) * (g_eg * g_eg);

          f64 mcorr_eg = m_eg[i] / (1.0 - b_corr_1);
          f64 vcorr_eg = v_eg[i] / (1.0 - b_corr_2);

          w_eg[i] -= local_lr * (mcorr_eg / (sqrt(vcorr_eg) + eps) + lambda * w_eg[i]);
        }

        grad_mg   = {};
        grad_eg   = {};
        batch_pos = 0;
      }
    }

    f64 delta_sum = 0.0;
    f64 magnitude = 0.0;

    for (i32 i = 0; i < static_cast<usize>(feature_idx::nb); ++i) {
      f64 dmg = std::abs(w_mg[i] - w_mg_prev[i]);
      f64 deg = std::abs(w_eg[i] - w_eg_prev[i]);

      delta_sum += dmg + deg;
      magnitude += std::abs(w_mg[i]) + std::abs(w_eg[i]);
    }

    f64 d_mean = delta_sum / static_cast<f64>(feature_idx::nb);

    std::println("Delta sum epoch {}: {:4f} Delta mean {:4f} Magnitude {:4f} Mean {:4f}", epoch,
                 delta_sum, d_mean, magnitude, magnitude / static_cast<usize>(feature_idx::nb));

    w_mg_prev = w_mg;
    w_eg_prev = w_eg;
  }

  auto scale = [](f64 n) {
    return static_cast<i32>(n * result_scale);
  };

  auto print_feature = [&](std::string name, feature_idx feature) {
    const f64 mg = w_mg[static_cast<usize>(feature)];
    const f64 eg = w_eg[static_cast<usize>(feature)];
    std::println("constexpr std::pair<score, score> {} = {{{}, {}}}", name, scale(mg), scale(eg));
  };

  auto print_psqt = [&](std::string name, feature_idx feature, usize nb) {
    std::println("constexpr std::array<std::pair<score, score>, {}> {} = {{", nb, name);
    for (i32 i = 0; i < nb; ++i) {
      const f64 mg = w_mg[static_cast<usize>(feature) + i];
      const f64 eg = w_eg[static_cast<usize>(feature) + i];

      std::print("{{{}, {}}}, ", scale(mg), scale(eg));

      if (i != 0 && i % 8 == 0) {
        std::print("//\n");
      }
    }
    std::println("}}");
  };

  print_feature("pawn_material", feature_idx::pawn_material);
  print_feature("knight_material", feature_idx::knight_material);
  print_feature("bishop_material", feature_idx::bishop_material);
  print_feature("rook_material", feature_idx::rook_material);
  print_feature("queen_material", feature_idx::queen_material);
  std::println();
  print_psqt("pawn_psqt", feature_idx::pawn_psqt, 48);
  std::println();
  print_psqt("knight_psqt", feature_idx::knight_psqt, 64);
  std::println();
  print_psqt("bishop_psqt", feature_idx::bishop_psqt, 64);
  std::println();
  print_psqt("rook_psqt", feature_idx::rook_psqt, 64);
  std::println();
  print_psqt("queen_psqt", feature_idx::queen_psqt, 64);
  std::println();
  print_psqt("king_psqt", feature_idx::king_psqt, 64);
}

}  // namespace surveyor_tuner

using namespace surveyor_tuner;

auto main(int argc, char** argv) -> int {
  std::filesystem::path dataset_path = argv[1];

  std::vector<dataset_entry> dataset = load_dataset(dataset_path);

  tune(dataset, 30, 0.001, 0.9, 0.999, 1e-7, 0.004, 6432);
}
