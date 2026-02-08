#include "ApiService.hpp"
#include "AIProvider.hpp"
#include "Spinner.hpp"
#include <httplib.h>
#include <json.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

const std::unordered_map<AIProvider, std::string> ApiService::apiProviderToKeyMap = {
  { AIProvider::OPENAI, "OPENAI_API_KEY" }
};

std::vector<Review> ApiService::requestAiReview(AIProvider provider, std::string prompt) {
  std::string apiToken = getApiTokenFromEnv(provider); 

  httplib::SSLClient client = httplib::SSLClient("api.openai.com");

  nlohmann::json body;
  body["model"] = "gpt-5-mini";
  body["input"] = prompt;

  std::ostringstream connectMessage; 
  connectMessage << "Connecting to OpenAI, using model " << body["model"];
  Spinner spinner(connectMessage.str());

  auto res = client.Post(
    "/v1/responses",
    {{ "Authorization", "Bearer " + apiToken }},
    body.dump(),
    "application/json"
  );

  spinner.stop();

  if (!res || res->status != 200) {
    std::cout << " \e[0;31m✗\e[0m" << std::endl;
    std::cerr << "Error: " << (res ? std::to_string(res->status) : "No response") << std::endl;
    throw new std::runtime_error("ERR_RESPONSE_FAILED");
  }

  std::cout << " \e[0;32m✓\e[0m" << std::endl;
  nlohmann::json responseJson = nlohmann::json::parse(res->body);

  std::string finalizedResponseJson;
  for (auto &outObj : responseJson["output"]) {
    if (!outObj.contains("content")) continue;

    for (auto &contentChunk : outObj["content"]) {
      if (!contentChunk.contains("text")) continue;

      finalizedResponseJson += contentChunk["text"];
    }
  }

  nlohmann::json aiResponseJson = nlohmann::json::parse(finalizedResponseJson);
  
  std::vector<Review> reviews;
  for (auto &reviewJson : aiResponseJson["comments"]) reviews.push_back(Review::fromJSON(reviewJson));

  return reviews;
}

std::string ApiService::getApiTokenFromEnv(AIProvider provider) {
  std::ifstream envFile(".env");

  if (!envFile.is_open()) {
    std::cerr << "ERROR: Unable to load api keys from env file!" << std::endl;
    throw new std::runtime_error("ERR_ENV_FILEREAD");
  }

  auto it = apiProviderToKeyMap.find(provider);
  if (it == apiProviderToKeyMap.end()) {
    std::cerr << "ERROR: Unkown provider type!" << std::endl;
    throw new std::runtime_error("ERR_INVALID_PROVIDER");
  }

  std::string providerApiKeyName = it->second;
  std::string providerApiKey = "";

  std::string line;
  while (std::getline(envFile, line)) {
    if (line.empty() || line[0] == '#') continue;

    std::istringstream iss(line);
    std::string segment;
    std::vector<std::string> kvEntry;

    while (std::getline(iss, segment, '=')) kvEntry.push_back(segment);

    if (kvEntry[0] != providerApiKeyName) continue;

    providerApiKey = kvEntry[1];
  }

  if (providerApiKey == "") {
    std::cerr << "ERROR: No API key provided for requested AI provider. Please make sure it exists in .env" << std::endl;
    throw new std::runtime_error("ERR_MISSING_API_KEY");
  }

  return providerApiKey;
}
