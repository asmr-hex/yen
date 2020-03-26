/**
 * @file   effects/filter/bandpass.hpp
 * @brief  BandPass Filter Processor Class
 * @author coco
 * @date   2020-03-25
 *************************************************/

#ifndef EFFECTS_FILTER_BANDPASS_H
#define EFFECTS_FILTER_BANDPASS_H


class BandPassFilter {
public:  
  double kf = 0;
  double kq = -1.0;

  double r0 = 0;
  double r1 = 0;

  BandPassFilter();
  
  double compute(double);
};

#endif
