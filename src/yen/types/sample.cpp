#include "yen/types/sample.hpp"

Sample::Sample(std::string file_path) {
  file.load(file_path);
}

double Sample::get_frame(unsigned int channel) {
  double value = file.samples[channel][buffer_offset[channel]];

  // increment buffer offset or loop back to 0 and stop playback
  buffer_offset[channel]++;
  if (buffer_offset[channel] >= file.getNumSamplesPerChannel()) {
    is_playing = false;
    buffer_offset[channel] = 0;
  }

  value = bandpass_filter.compute(value);
  
  return value;
}
