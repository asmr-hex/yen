#include "yen/state/samples.hpp"


Samples::Samples(std::shared_ptr<Config> config) {
  auto sample_dir = config->at("samples")["dir"].as<std::string>();
  auto file_names = config->at("samples")["files"].as< std::vector<std::string> >();

  for (auto file_name : file_names) {
    auto sample = std::make_shared<Sample>(sample_dir + "/" + file_name);

    samples.push_back(sample);
  }
}
