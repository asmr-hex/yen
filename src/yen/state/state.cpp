#include <spdlog/spdlog.h>

#include "yen/state/state.hpp"


State::State(std::shared_ptr<Config> config)
  : controls(std::make_shared<GlobalControls>(config)),
    samples(std::make_shared<Samples>(config))
{}

void State::connect() {
  spdlog::info("  connected -> state");
}
