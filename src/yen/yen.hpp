/**
 * @file   yen.hpp
 * @brief  Entrypoint Class for Yen Sampler
 * @author coco
 * @date   2020-03-25
 *************************************************/


#ifndef YEN_H
#define YEN_H

#include <string>
#include <memory>


#include "yen/io.hpp"
#include "yen/types.hpp"
#include "yen/config.hpp"
#include "yen/state.hpp"
#include "yen/controllers.hpp"


class Yen {
public:
  Yen(std::string config_path,
      std::shared_ptr<MidiDeviceFactory>);
  
  void run();

  std::shared_ptr<Config>        config;
  std::shared_ptr<IO>            io;
  std::shared_ptr<State>         state;
  std::shared_ptr<Controllers>   controllers;
};

#endif
