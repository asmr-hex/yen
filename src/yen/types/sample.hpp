/**
 * @file   types/sample.hpp
 * @brief  Sample Type Class
 * @author coco
 * @date   2020-03-25
 *************************************************/

#ifndef TYPES_SAMPLE_H
#define TYPES_SAMPLE_H

#include <memory>

#include <AudioFile.h>


class Sample {
public:
  AudioFile<double> file;

  bool is_playing               = false;
  unsigned int buffer_offset[2] = { 0, 0 };
  
  Sample(std::string file_path);

  double get_frame(unsigned int channel);
};

#endif
