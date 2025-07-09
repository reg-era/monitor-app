# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic

# SDL2 flags
SDL2_CFLAGS := $(shell sdl2-config --cflags)
SDL2_LIBS := $(shell sdl2-config --libs)

# OpenGL libs
OPENGL_LIBS := -lGL

# Include directories
INCLUDES = -Iinclude -Iinclude/models -Iimgui/lib -Iimgui/lib/backend -Iimgui/lib/gl3w -I/usr/include/SDL2

# Source files
SRC = src/main.cpp \
      src/gui/mem_sec.cpp  src/gui/net_sec.cpp  src/gui/sys_sec.cpp  src/gui/task_sec.cpp  src/gui/therm_sec.cpp \
      imgui/lib/imgui.cpp imgui/lib/imgui_draw.cpp imgui/lib/imgui_widgets.cpp imgui/lib/imgui_tables.cpp imgui/lib/imgui_demo.cpp \
      imgui/lib/backend/imgui_impl_sdl.cpp imgui/lib/backend/imgui_impl_opengl3.cpp \
      imgui/lib/gl3w/GL/gl3w.c

# Object files (mapped to build/ directory)
OBJ = $(patsubst %.cpp,build/%.o,$(filter %.cpp,$(SRC))) \
      $(patsubst %.c,build/%.o,$(filter %.c,$(SRC)))

# Target executable
TARGET = bin/monitor-app

# Ensure build and bin directories exist
BUILD_DIR = build
BIN_DIR = bin

# Default target
all: $(TARGET)

# Link object files to create the target executable
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)  # Make sure the bin/ directory exists
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SDL2_LIBS) $(OPENGL_LIBS) -ldl

# Compile C++ files
build/%.o: %.cpp
	@mkdir -p $(dir $@)  # Make sure the build/ directory exists
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) $(INCLUDES) -c $< -o $@

# Compile C files
build/%.o: %.c
	@mkdir -p $(dir $@)  # Make sure the build/ directory exists
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) $(INCLUDES) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up generated files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)


.PHONY: all clean run