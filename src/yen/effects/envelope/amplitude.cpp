#include "yen/effects/envelope/amplitude.hpp"


AmplitudeEnvelope::AmplitudeEnvelope() {
  stage_duration[Stage::Attack]  = std::chrono::milliseconds(3000);
  stage_duration[Stage::Decay]   = std::chrono::milliseconds(500);
  stage_duration[Stage::Release] = std::chrono::milliseconds(5000);

  stage_level[Stage::Off]     = 0.0;
  stage_level[Stage::Sustain] = 1.0;
}

double AmplitudeEnvelope::compute(double input) {
  // only perform computation if we are in the Attack, Decay, or Release stages
  // i.e. off and sustain stages are constant.
  if (current_stage != Stage::Off && current_stage != Stage::Sustain) {
    // check to see if we need to enter a new stage.
    if (current_stage_index >= next_stage_index) {
      auto new_stage = static_cast<Stage>( (current_stage + 1) % Stage::NumStages);
      enter_stage(new_stage);
    }

    // apply envelope multiplier to input
    current_level *= multiplier;
    current_stage_index++;
  }

  return input * current_level;
}

void AmplitudeEnvelope::off() {
  enter_stage(Stage::Off);
}

void AmplitudeEnvelope::attack() {
  enter_stage(Stage::Attack);
}

void AmplitudeEnvelope::release() {
  enter_stage(Stage::Release);
}

void AmplitudeEnvelope::set_sample_rate(double new_sample_rate) {
  sample_rate = new_sample_rate;
}

void AmplitudeEnvelope::enter_stage(Stage next_stage) {
  current_stage = next_stage;
  current_stage_index = 0;
  if (current_stage == Stage::Off || current_stage == Stage::Sustain) { next_stage_index = 0; }
  else { next_stage_index = (stage_duration[current_stage].count() / 1000) * sample_rate; }

  switch (current_stage) {
  case Stage::Off:
    current_level = 0.0;
    multiplier    = 1.0;
    break;
  case Stage::Attack:
    current_level = minimum_level;
    multiplier    = compute_multiplier(current_level, 1.0, next_stage_index);
    break;
  case Stage::Decay:
    current_level = 1.0;
    multiplier    = compute_multiplier(current_level,
                                       std::fmax(stage_level[Stage::Sustain], minimum_level),
                                       next_stage_index);
    break;
  case Stage::Sustain:
    current_level = stage_level[Stage::Sustain];
    multiplier    = 1.0;
    break;
  case Stage::Release:
    multiplier = compute_multiplier(current_level, minimum_level, next_stage_index);
    break;
  default:
    break;
  }
}

double AmplitudeEnvelope::compute_multiplier(double start_level, double end_level, unsigned long long length) {
  return 1.0 + (std::log(end_level) - std::log(start_level)) / (length);
}
