/**
 * @file   controllers/controllers.hpp
 * @brief  Aggregation of Controllers
 * @author coco
 * @date   2020-02-19
 *************************************************/


#ifndef YEN_CONTROLLERS_CONTROLLERS_H
#define YEN_CONTROLLERS_CONTROLLERS_H

#include <memory>

#include "yen/io.hpp"
#include "yen/state.hpp"

#include "yen/controllers/midi.hpp"


/// @brief An aggregation of all controllers which respond to i/o events.
///
class Controllers {
public:
  Controllers(std::shared_ptr<IO>, std::shared_ptr<State>);

  /// @brief this method instantiates all controller classes and connects them to
  /// IO and State.
  ///
  /// @remark
  /// Instead of instantiating all controllers within the constructor, i'm choosing
  /// to do it within this method s.t. the calling code can initialize the controllers
  /// when everything else is being initialized, and then connect the controllers after
  /// IO has been connected. It is important to instantiate all controllers after IO has
  /// connected since the observables exposed in IO will not be instantiated until after
  /// IO has connected.
  /// While i could have just instantiated this controllers container after the IO connection,
  /// i chose to introduce this connect method s.t. it is semantically well-ordered in the calling
  /// code (i.e. only "connecting" happens in the "connecting" phase of spinning up the application).
  ///
  void connect();
  
private:
  std::shared_ptr<IO> io;
  std::shared_ptr<State> state;

  std::unique_ptr<MidiController>       midi;
};

#endif
