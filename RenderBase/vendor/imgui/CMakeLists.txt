cmake_minimum_required(VERSION 3.0)

file(GLOB_RECURSE
    SOURCES
    "*.c"
    "*.hpp"
    "*.cpp"
    "*.h"
)

set(IMGUI_SOURCES ${SOURCES})

project(ImGui)

add_library(ImGui ${IMGUI_SOURCES})
target_include_directories(ImGui PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(ImGui
    glfw
)
