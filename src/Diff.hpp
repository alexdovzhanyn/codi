#pragma once

#include <json.hpp>
#include <iostream>

struct Diff {
  std::string fileName;
  std::string before;
  std::string after;

  static Diff fromJSON(nlohmann::json &j) {
    return {
      .fileName = j["filename"],
      .before = j["before"],
      .after = j["after"]
    };
  }
};
