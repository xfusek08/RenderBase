cmake_minimum_required(VERSION 3.0)

file(GLOB_RECURSE
    SOURCES
    "*.c"
    "*.hpp"
    "*.cpp"
    "*.h"
)

set(IMGUI_SOURCES ${SOURCES} PARENT_SCOPE)

set(IMGUI_INCLUDES
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}
    PARENT_SCOPE
)
