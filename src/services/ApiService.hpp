#pragma once

#include "AIProvider.hpp"
#include <string>
#include <unordered_map>
#include "Review.hpp"
#include <vector>


class ApiService {
public:
  static std::vector<Review> requestAiReview(AIProvider provider, std::string prompt); 

private:
  static const std::unordered_map<AIProvider, std::string> apiProviderToKeyMap; 

  static std::string getApiTokenFromEnv(AIProvider provider);
};
