CXX := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -g -Isrc -Ideps -DCPPHTTPLIB_OPENSSL_SUPPORT

OPENSSL_PREFIX := $(shell brew --prefix openssl@3)

CXXFLAGS += -I$(OPENSSL_PREFIX)/include
LDFLAGS  += -L$(OPENSSL_PREFIX)/lib
LDLIBS   += -lssl -lcrypto

SRC_DIR := src
BUILD_DIR := build
TARGET := codi

SRC := $(shell find $(SRC_DIR) -name "*.cpp")
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC)) \
       $(BUILD_DIR)/main.o

all: $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: main.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c main.cpp -o $@

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
