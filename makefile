# Compiler and flags
CXX = g++
CXXFLAGS = -Iinclude -Wall -g
LDFLAGS = 

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Source files for main executable
MAIN_SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/Customer.cpp $(SRC_DIR)/Register.cpp $(SRC_DIR)/Simulation.cpp
MAIN_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(MAIN_SOURCES))

# Source files for test executable
TEST_SOURCES = $(SRC_DIR)/test.cpp $(SRC_DIR)/Customer.cpp $(SRC_DIR)/Register.cpp $(SRC_DIR)/Simulation.cpp
TEST_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TEST_SOURCES))

# Executables
MAIN_EXECUTABLE = $(BUILD_DIR)/main.exe
TEST_EXECUTABLE = $(BUILD_DIR)/test.exe

# Default target builds both executables
all: $(MAIN_EXECUTABLE) $(TEST_EXECUTABLE)

# Rule for linking the main executable
$(MAIN_EXECUTABLE): $(MAIN_OBJECTS)
	$(CXX) $(MAIN_OBJECTS) -o $@ $(LDFLAGS)

# Rule for linking the test executable
$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CXX) $(TEST_OBJECTS) -o $@ $(LDFLAGS)

# Rule for compiling source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up the build directory
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean
