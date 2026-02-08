#pragma once

#include <iostream>
#include <json.hpp>
#include "Diff.hpp"
#include "vector"

struct Review {
  std::string comment;
  std::vector<Diff> diffs;

  static Review fromJSON(nlohmann::json &j) {
    std::vector<Diff> diffs;

    for (auto &diffJson : j["diffs"]) diffs.push_back(Diff::fromJSON(diffJson));

    return {
      .comment = j["comment"],
      .diffs = diffs
    };
  }
};
