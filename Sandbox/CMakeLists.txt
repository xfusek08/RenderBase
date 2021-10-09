cmake_minimum_required (VERSION 3.18)

project(Sandbox)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE
    SOURCES
    RELATIVE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
    "*.cpp"
    "*.h"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    RenderBase
)

target_include_directories(${PROJECT_NAME}
    PUBLIC .
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    $<$<CONFIG:DEBUG>:
        "DEBUG"
    >
    $<$<CONFIG:RELEASE>:
        "RELEASE"
    >
)
