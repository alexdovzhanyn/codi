#include <iostream>
#include "Diff.hpp"
#include "vector"

struct Review {
    std::string comment;
    std::vector<Diff> diffs;
};