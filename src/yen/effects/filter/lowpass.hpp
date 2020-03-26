/**
 * @file   effects/filter/lowpass.hpp
 * @brief  LowPass Filter Processor Class
 * @author coco
 * @date   2020-03-25
 *************************************************/

#ifndef EFFECTS_FILTER_LOWPASS_H
#define EFFECTS_FILTER_LOWPASS_H

#include <memory>


class LowPassFilter {
public:  
  double k2 = 0;
  double previous = 0;

  LowPassFilter();
  
  double compute(double);
};

#endif
