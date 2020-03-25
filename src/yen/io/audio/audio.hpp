/**
 * @file   io/midi/midi.hpp
 * @brief  Midi Router Class
 * @author coco
 * @date   2020-01-25
 *************************************************/


#ifndef YEN_IO_AUDIO_H
#define YEN_IO_AUDIO_H

#include <memory>

// TODO eventually move to devices
#include <RtAudio.h>

#include "yen/config.hpp"
#include "yen/state.hpp"


class Audio {
public:
  Audio(std::shared_ptr<Config>, std::shared_ptr<State>);

  // TODO eventually output an observable? for incoming audio???
  void connect();
  
private:
  /// @brief the state.
  std::shared_ptr<State> state;
  
  /// @brief dac for audio output. TODO eventuallt move this to be encapsulated within RTAudio device.
  RtAudio dac;

  /// @brief dac parameters // TODO eventually move this to be encapsulated within RTAudio device.
  RtAudio::StreamParameters parameters;

  unsigned int sampleRate = 44100;
  unsigned int bufferFrames = 256; // 256 sample frames
  
  /// @brief audio device factory
  // TODO make device factory
  // std::shared_ptr<AudioDeviceFactory> device_factory;

  /// @brief audio callback
  static int callback(void *, void *, unsigned int, double, RtAudioStreamStatus, void *);
};

#endif
