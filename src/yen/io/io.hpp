/**
 * @file   io/io.hpp
 * @brief  I/O Context Class
 * @author coco
 * @date   2020-01-15
 *************************************************/


#ifndef IO_H
#define IO_H

#include <string>
#include <memory>

#include "yen/rx.hpp"
#include "yen/state.hpp"

#include "yen/io/audio/audio.hpp"

#include "yen/io/midi/midi.hpp"
#include "yen/io/midi/device/factory.hpp"


/// @brief Class for consolidating all I/O devices.
class IO {
public:
  /// @brief Constructs & configures an IO context object.
  ///
  /// @pre pointers to configuration and devices must already exist.
  ///
  /// @param config        pointer to a configuration object
  /// @param grid_device   pointer to a grid device object
  /// @param midi_device   pointer to a midi device object
  /// @param state         pointer to the state
  ///
  /// @details
  /// Constructs Grid and Midi objects (which wrap their respective device objects
  /// providing a higher level of abstraction) which are publicly exposed IO members.
  ///
  IO(std::shared_ptr<Config>,
     std::shared_ptr<MidiDeviceFactory> midi_device_factory,
     std::shared_ptr<State>);

  /// @brief Connects Midi objects to their ports.
  void connect();

  std::shared_ptr<Audio> audio;
  std::shared_ptr<Midi>  midi;

  /// @brief observable stream of midi events
  rx::observable<midi_event_t> midi_events;
};

#endif
