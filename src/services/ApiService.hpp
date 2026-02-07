#pragma once

#include "AIProvider.hpp"
#include <string>
#include <unordered_map>

class ApiService {
public:
  static void requestAiReview(AIProvider provider, std::string prompt); 

private:
  static const std::unordered_map<AIProvider, std::string> apiProviderToKeyMap; 

  static std::string getApiTokenFromEnv(AIProvider provider);
};
