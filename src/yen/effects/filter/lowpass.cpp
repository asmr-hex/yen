#include "yen/effects/filter/lowpass.hpp"

LowPassFilter::LowPassFilter() {
  k2 = 0.2;
};
  
double LowPassFilter::compute(double sample) {
  previous = ((sample - previous) * k2) + previous;

  return previous;
};
