#include "uci.hpp"

#include <memory>

using namespace surveyor;

auto main() -> int {
  auto uci_state = std::make_unique<uci>();

  uci_state->loop();
}
