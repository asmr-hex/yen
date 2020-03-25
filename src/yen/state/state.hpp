/**
 * @file   state/state.hpp
 * @brief  Aggregate State Class
 * @author coco
 * @date   2020-02-19
 *************************************************/

#ifndef STATE_STATE_H
#define STATE_STATE_H

#include <memory>

#include "yen/config.hpp"

#include "yen/state/samples.hpp"
#include "yen/state/controls/controls.hpp"


class State : public std::enable_shared_from_this<State> {
public:
  std::shared_ptr<GlobalControls> controls;
  std::shared_ptr<Samples> samples;
  
  State(std::shared_ptr<Config>);

  /// @brief allows particular parts of the state to subscribe to the
  /// state itself.
  void connect();
};

#endif
