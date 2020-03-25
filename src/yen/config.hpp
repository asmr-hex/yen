/**
 * @file   config.hpp
 * @brief  Yen Configuration
 * @author coco
 * @date   2020-02-19
 *************************************************/


#ifndef YEN_CONFIG_H
#define YEN_CONFIG_H

#include <string>

#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>


/// @brief configuration for anemone.
///
/// @details TODO write up examples.
///
class Config {
public:
  /// @brief path to yaml configuration file
  std::string path;

  /// @brief parsed YAML node.
  YAML::Node yml;

  /// @brief constructs a Config given a filepath to a YAML config file.
  ///
  /// @param file_path   a string of the file path to the configuration file.
  ///
  Config(std::string path)
    : path(path),
      yml(YAML::LoadFile(path)) {};

  /// @brief constructs a Config from a previously parsed YAML node and the path
  /// to the configuration file it is contained within. This is usually used to
  /// extract a sub-tree from a larger config.
  ///
  /// @param yml_node    a YAML::Node representation of a config.
  /// @param file_path   a string of the file path this config object is contained within.
  ///
  Config(YAML::Node yml, std::string path)
    : path(path),
      yml(yml) {};

    // when accessing a Base config using the [] operator, we directly
    // access the YAML root node of this object. Additionally, we will
    // check to see whether the accessed field has its contents within
    // another yaml file and if so read in that file as a new Base config
    // object.

  /// @brief gets a sub-tree of a parsed yaml config and returns a new Config object.
  ///
  /// @param field   a string representation of the field we wish to select.
  Config operator[](std::string field) {
      // check to see if the field with "_file" exists.
      auto field_file = field + "_file";

      // if the field has it's own dedicated file, read the file and return the
      // parsed YAML node from that file.
      if (yml[field_file]) {
        auto file_path = get_parent_dir(path) + yml[field_file].as<std::string>();

        return Config(file_path);
      }

      return Config(yml[field], path);
  };

  /// @brief similar to the [] operator, but works with pointers to configs.
  ///
  /// @param field   a string representation of a field.
  ///
  Config at(std::string field) {
    return (*this)[field];
  };
    // wrap the YAML::Node::as method so that we are able to perform the
    // same type conversions.

  /// @brief allows a config to perform type conversions on fields.
  ///
  /// @remark since we aren't inheriting from a YAML::Node, but we still want to
  /// expose its type conversion capabilities, we are just implementing a wrapper
  /// over the YAML::Node::as method. there is probably a better way to do this.
  ///
  template<typename T>
  T as() {
    return yml.as<T>();
  };
  
  /// @brief helper function for navigation up directories.
  ///
  /// @param file_path   the string of a file path to get the parent directory of.
  ///
  std::string get_parent_dir(std::string file_path) {
    // get last "/" position
    std::size_t sep_pos = file_path.rfind("/");

    return file_path.substr(0, sep_pos + 1);
  };
};

#endif
