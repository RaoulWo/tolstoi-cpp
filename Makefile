# Compiler
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -g

# Directories
SRC_DIR := src
BUILD_DIR := bin

# Files
SOURCES := $(wildcard $(SRC_DIR)/*.cc)
OBJECTS := $(patsubst $(SRC_DIR)/%.cc, $(BUILD_DIR)/%.o, $(SOURCES))
EXECUTABLE := $(BUILD_DIR)/tolstoy

all:	build $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)	
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

$(OBJECTS): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.cc	
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	@mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) $(BUILD_DIR)