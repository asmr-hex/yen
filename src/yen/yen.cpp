#include "yen/yen.hpp"

#include <spdlog/spdlog.h>


Yen::Yen(std::string config_path,
         std::shared_ptr<MidiDeviceFactory> midi_device_factory)
{
  spdlog::set_level(spdlog::level::info);
  spdlog::set_pattern("[%H:%M:%S:%e] [thread %t] %^[%l]%$ %v");

  spdlog::info("============= initialization ============");
  
  // initialize configuration
  spdlog::info("  initializing \tconfiguration");
  config = std::make_shared<Config>(config_path);

  // initialize state
  spdlog::info("  initializing \tstate");
  state = std::make_shared<State>(config);
  
  // initialize io
  spdlog::info("  initializing \tio");
  io = std::make_shared<IO>(IO(config, midi_device_factory, state));

  // initialize controllers
  spdlog::info("  initializing \tcontrollers");
  controllers = std::make_shared<Controllers>(Controllers(io, state));

}

void Yen::run() {
  spdlog::info("============= connecting ================");

  state->connect();
  
  io->connect();

  controllers->connect();
  
  // TODO deal with threads....
  while (true) {
    std::this_thread::sleep_for(std::chrono::minutes(5));
  }
}
