#include "yen/effects/filter/bandpass.hpp"

BandPassFilter::BandPassFilter() {
  kf = 0;
  kq = -1;
}
  
double BandPassFilter::compute(double input) {
  r0 = (r0 + (( input + (r0 * kq) - ( (r0 * kf) + r1 ) ) * kf));
  r1 = r0 * kf + r1;

  return r0;
}
