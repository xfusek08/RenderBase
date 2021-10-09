cmake_minimum_required (VERSION 3.18)

project(RenderBase)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw/glfw)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp", "src/*.h")

message (SOURCES)
add_library(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    glad
    glfw
)

target_include_directories(${PROJECT_NAME} src)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    $<$<CONFIG:DEBUG>:
        "DEBUG"
    >
    $<$<CONFIG:RELEASE>:
        "RELEASE"
    >
)
