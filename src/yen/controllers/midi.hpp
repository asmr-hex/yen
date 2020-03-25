/**
 * @file   controllers/shift.hpp
 * @brief  Shift Controller
 * @author coco
 * @date   2020-02-19
 *************************************************/


#ifndef YEN_CONTROLLERS_MIDI_H
#define YEN_CONTROLLERS_MIDI_H

#include <memory>

#include "yen/rx.hpp"
#include "yen/io.hpp"
#include "yen/types.hpp"
#include "yen/state.hpp"


/// @brief An controller for toggling the shift button.
///
class MidiController {
public:
  MidiController(std::shared_ptr<IO>, std::shared_ptr<State>);
};

#endif
