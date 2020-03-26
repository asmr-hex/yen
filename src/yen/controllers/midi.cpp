#include <spdlog/spdlog.h>

#include "yen/controllers/midi.hpp"


MidiController::MidiController(std::shared_ptr<IO> io, std::shared_ptr<State> state) {
  auto midi_on_events = io->midi_events
    | rx::filter([] (midi_event_t event) {
                   return (unsigned int)event.data[0] == 145;
                 });

  auto midi_off_events = io->midi_events
    | rx::filter([] (midi_event_t event) {
                   return (unsigned int)event.data[0] == 129;
                 });

  midi_on_events
    .subscribe([state] (midi_event_t event) {
                 state->samples->samples[0]->is_playing = true;
                 state->samples->samples[0]->buffer_offset[0] = 0;
                 state->samples->samples[0]->buffer_offset[1] = 0;

                 spdlog::info("midi on");
               });

  midi_off_events
    .subscribe([state] (midi_event_t event) {
                 state->samples->samples[0]->is_playing = false;
                 state->samples->samples[0]->buffer_offset[0] = 0;
                 state->samples->samples[0]->buffer_offset[1] = 0;

                 spdlog::info("midi off");
               });

  // control effects
  auto knobs_cc_events = io->midi_events
    | rx::filter([] (midi_event_t midi_event) {
                   return
                     midi_event.source                  == "Midi Fighter Twister" &&
                     ((unsigned int)midi_event.data[0]) == 176 &&  // cc + channel 1
                     ((unsigned int)midi_event.data[1]) == 16; // control 16
                 });

  knobs_cc_events
    .subscribe([io, state] (midi_event_t midi_event) {
                 state->samples->samples[0]->bandpass_filter.kf = (double)midi_event.data[2] / 127;
               });
}
