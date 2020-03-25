/**
 * @file   state/samples.hpp
 * @brief  Samples Container Class
 * @author coco
 * @date   2020-03-25
 *************************************************/

#ifndef STATE_SAMPLES_H
#define STATE_SAMPLES_H

#include <memory>


#include "yen/config.hpp"
#include "yen/types.hpp"


class Samples {
public:
  std::vector< std::shared_ptr<Sample> > samples;
  
  Samples(std::shared_ptr<Config>);
};

#endif
