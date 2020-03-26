/**
 * @file   effects/envelope/amplitude.hpp
 * @brief  Amplitude Envelope Class
 * @author coco
 * @date   2020-03-26
 *************************************************/

#ifndef EFFECTS_ENVELOPE_AMPLITUDE_H
#define EFFECTS_ENVELOPE_AMPLITUDE_H

#include <map>
#include <cmath>
#include <memory>
#include <chrono>


class AmplitudeEnvelope {
public:
  /// @brief envelope stages.
  enum Stage {
              Off = 0,
              Attack,
              Decay,
              Sustain,
              Release,
              NumStages
  };

  AmplitudeEnvelope();

  double compute(double);

  void off();
  void attack();
  void release();
  void set_sample_rate(double new_sample_rate);

private:
  const double minimum_level = 0.0001;
  double current_level       = minimum_level;
  
  double multiplier          = 1.0;
  
  double sample_rate         = 44100.0;

  Stage              current_stage       = Stage::Off;
  unsigned long long current_stage_index = 0;
  unsigned long long next_stage_index    = 0;
  
  std::map<Stage, std::chrono::milliseconds> stage_duration;
  std::map<Stage, double>                    stage_level;
  
  void enter_stage(Stage next_stage);

  double compute_multiplier(double start_level, double end_level, unsigned long long length);
};

#endif
