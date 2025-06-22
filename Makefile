TARGET = arkanoid

CXX = g++
CXX_FLAGS = -Wall -pedantic -Wextra -std=c++14 -g -I $(SOURCE_DIR)
LINKER_FLAGS = -lSDL2 -lSDL2_ttf

MKDIR = mkdir -p

SOURCE_DIR = src
BUILD_DIR = build

# Find all .cpp files recursively
SOURCES = $(shell find $(SOURCE_DIR) -name "*.cpp")
HEADERS = $(shell find $(SOURCE_DIR) -name "*.h")

# Convert source paths to object paths while keeping the directory structure
OBJECTS = $(SOURCES:$(SOURCE_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Dependency files (one .d file for each .cpp file)
DEPS = $(OBJECTS:.o=.d)

.PHONY: compile
compile: $(TARGET)
	@echo "Compiled."

.PHONY: run
run: $(TARGET)
	@echo "Running..."
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $^ $(LINKER_FLAGS) -o $@

# Pattern rule for object files - creates directory structure and dependency files
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@$(MKDIR) $(dir $@)
	$(CXX) $(CXX_FLAGS) -MMD -MP -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET) $(BUILD_DIR)/ 2>/dev/null

# Include auto-generated dependency files (if they exist)
-include $(DEPS)
