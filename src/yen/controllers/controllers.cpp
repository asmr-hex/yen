#include <spdlog/spdlog.h>

#include "yen/controllers/controllers.hpp"


Controllers::Controllers(std::shared_ptr<IO> io,
                         std::shared_ptr<State> state)
  : io(io), state(state)
{}

void Controllers::connect() {
  midi          = std::make_unique<MidiController>(io, state);

  spdlog::info("  connected -> controllers");
}
