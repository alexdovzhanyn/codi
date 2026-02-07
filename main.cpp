#include "AIProvider.hpp"
#include "services/ApiService.hpp"
#include <iostream>

int main() {
  std::string prompt = R"(
    You are a Senior software engineer with a plethora of experience across many different programming languages and
    frameworks. You are a stickler for clean, maintainable code, and have an eye for catching potential edge cases.

    Provide a code review for the following Git diff. Your review must be formatted as a valid JSON string, matching the following
    schema:

    Diff {
      filename: string
      before: string
      after: string
    }

    Review {
      comment: string
      diffs: Diff[]
    }

    Response {
      comments: Review[] 
    }

    Each review comment can reference multiple diff lines, if necessary.

    DO NOT RETURN ANYTHING EXCEPT THE RESPONSE JSON.

    Diff:
  )";

  std::string dummyDiff = R"(
diff --git a/Makefile b/Makefile
index 3320e20..f750e0e 100644
--- a/Makefile
+++ b/Makefile
@@ -1,9 +1,32 @@
-TARGET = codi
+CXX := clang++
+CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -g -Isrc -Ideps -DCPPHTTPLIB_OPENSSL_SUPPORT
+
+OPENSSL_PREFIX := $(shell brew --prefix openssl@3)
+
+CXXFLAGS += -I$(OPENSSL_PREFIX)/include
+LDFLAGS  += -L$(OPENSSL_PREFIX)/lib
+LDLIBS   += -lssl -lcrypto
+
+SRC_DIR := src
+BUILD_DIR := build
+TARGET := codi
+
+SRC := $(shell find $(SRC_DIR) -name "*.cpp")
+OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC)) \
+       $(BUILD_DIR)/main.o

 all: $(TARGET)

-$(TARGET): main.cpp
-       g++ main.cpp -o $(TARGET)
+$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
+       @mkdir -p $(dir $@)
+       $(CXX) $(CXXFLAGS) -c $< -o $@
+
+$(BUILD_DIR)/main.o: main.cpp
+       @mkdir -p $(BUILD_DIR)
+       $(CXX) $(CXXFLAGS) -c main.cpp -o $@
+
+$(TARGET): $(OBJ)
+       $(CXX) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

 clean:
-       rm -f $(TARGET)
+       rm -rf $(BUILD_DIR) $(TARGET)
  )";

  ApiService::requestAiReview(AIProvider::OPENAI, prompt + dummyDiff);

  return 0;
}
