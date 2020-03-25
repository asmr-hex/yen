#include "yen/io/io.hpp"


IO::IO(std::shared_ptr<Config> config,
       std::shared_ptr<MidiDeviceFactory> midi_device_factory,
       std::shared_ptr<State> state)
{
  audio = std::make_shared<Audio>(config, state);
  midi  = std::make_shared<Midi>(config, midi_device_factory);
}

void IO::connect() {
  midi_events = midi->connect();

  audio->connect();
}
