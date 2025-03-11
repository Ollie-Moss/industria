# Define the compiler
CC = gcc
CXX = g++

LINK = -lfreetype -lGL -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

# Define compiler flags
CFLAGS = -Wall
CXXFLAGS = -std=c++17 -Wall

# Define the build directory and target executable
BUILD_DIR = build
TARGET = build.exec 

# Create the build directory if it doesn't exist
$(shell mkdir -p $(BUILD_DIR))

# Find all .cpp and .c files in the current directory and subdirectories
SRC_FILES = $(shell find . -type f \( -name "*.cpp" -o -name "*.c" \))

OBJ_FILES = $(SRC_FILES:%.cpp=$(BUILD_DIR)/%.o)
OBJ_FILES := $(OBJ_FILES:%.c=$(BUILD_DIR)/%.o)

OBJ_FILE_NAMES = $(foreach obj,$(OBJ_FILES),$(BUILD_DIR)/$(notdir $(obj)))

# Rule to create the final target (executable)
$(TARGET): clean $(OBJ_FILES)
	$(CXX) $(BUILD_DIR)/*.o $(LINK) -o $(TARGET)
	./$(TARGET)

# Rule to compile each .cpp file into .o files inside the build directory
$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)

# Rule to compile each .c file into .o files inside the build directory
$(BUILD_DIR)/%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)

# Clean rule to remove the build directory and executable
clean:
	rm -rf $(BUILD_DIR)/* $(TARGET)
