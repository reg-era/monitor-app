# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic

# SDL2 and OpenGL
SDL2_CFLAGS := $(shell sdl2-config --cflags)
SDL2_LIBS := $(shell sdl2-config --libs)
OPENGL_LIBS := -lGL -ldl

INCLUDES = -Iinclude -Iinclude/models -Iimgui/lib -Iimgui/lib/backend -Iimgui/lib/gl3w -I/usr/include/SDL2
SOURCES = $(wildcard src/*.cpp src/gui/*.cpp) $(wildcard imgui/lib/*.cpp imgui/lib/backend/*.cpp) $(wildcard imgui/lib/gl3w/GL/*.c)

TARGET = bin/monitor-app

# Default build
build: clean compile

compile:
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) $(INCLUDES) $(SOURCES) -o $(TARGET) $(SDL2_LIBS) $(OPENGL_LIBS)

run: build
	@./$(TARGET)

clean:
	@rm -rf bin
	@mkdir -p bin
