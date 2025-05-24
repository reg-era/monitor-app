cmake_minimum_required(VERSION 3.10)
project(monitor-app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2
find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
    message(FATAL_ERROR "SDL2 not found!")
endif()

# Find OpenGL
find_package(OpenGL REQUIRED)

# ImGui sources
set(IMGUI_SOURCES
    imgui/lib/imgui.cpp
    imgui/lib/imgui_draw.cpp
    imgui/lib/imgui_widgets.cpp
    imgui/lib/imgui_tables.cpp
    imgui/lib/imgui_demo.cpp
    imgui/lib/backend/imgui_impl_sdl.cpp
    imgui/lib/backend/imgui_impl_opengl3.cpp
    imgui/lib/gl3w/GL/gl3w.c
)

# Include dirs
include_directories(
    imgui/lib
    imgui/lib/backend
    imgui/lib/gl3w
    ${SDL2_INCLUDE_DIRS}
)

add_executable(monitor-app
    src/main.cpp
    src/gui/navigation.cpp
    src/gui/section.cpp
    src/models/cpu.cpp
    src/models/memory.cpp
    ${IMGUI_SOURCES}
)

target_link_libraries(monitor-app
    ${SDL2_LIBRARIES}
    OpenGL::GL
    dl
)

# If you want to add compiler warnings and optimizations (optional)
target_compile_options(monitor-app PRIVATE -Wall -Wextra -Wpedantic)
