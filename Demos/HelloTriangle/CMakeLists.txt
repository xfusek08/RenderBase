
cmake_minimum_required (VERSION 3.18)

project(HelloTriangle)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/HelloTriangle.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} RenderBase)
