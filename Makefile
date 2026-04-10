# Compiler and flags
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# Directories
SRC_DIR  = src
OBJ_DIR  = obj

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Output binary
TARGET = hotel_management

# Default target
all: dirs $(TARGET)

# Create required directories
dirs:
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	if not exist data mkdir data

# Link object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp to a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove build artefacts
clean:
	del /Q $(OBJ_DIR)\*.o $(TARGET).exe 2>nul || true

.PHONY: all clean dirs
