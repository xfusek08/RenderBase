cmake_minimum_required (VERSION 3.18)
project (RenderBase)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)

set(SOURCES
    src/main.cpp

    # namespace engine
    src/engine/engine.h
    src/engine/event.h
    src/engine/scene.h
    src/engine/window.h             src/engine/window.cpp
    src/engine/application.h        src/engine/application.cpp
    src/engine/graphics.h           src/engine/graphics.cpp

    # namespace platform
    src/engine/platform/platform.h  src/engine/platform/platform.cpp
    src/engine/platform/sdl.h       src/engine/platform/sdl.cpp
)

# # find imgui sources
# FILE(GLOB IMGUI_SOURCES ${IMGUI_DIR}/*.cpp)
# FILE(GLOB IMGUI_HEADERS ${IMGUI_DIR}/*.h)

# list(APPEND IMGUI_HEADERS
#     ${IMGUI_DIR}/examples/imgui_impl_sdl.h
#     ${IMGUI_DIR}/examples/imgui_impl_opengl3.h
# )

# list(APPEND IMGUI_SOURCES
#     ${IMGUI_DIR}/examples/imgui_impl_sdl.cpp
#     ${IMGUI_DIR}/examples/imgui_impl_opengl3.cpp
# )

add_subdirectory(src/vendor/glad)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    # ${IMGUI_HEADERS}
    # ${IMGUI_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2-static
    SDL2::SDL2main
    glad
    glm::glm
)

target_include_directories(${PROJECT_NAME} PUBLIC
    src
    # ${IMGUI_DIR}
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    "PROJECT_NAME=\"${PROJECT_NAME}\""
    $<$<CONFIG:DEBUG>:
        "DEBUG"
    >
    $<$<CONFIG:RELEASE>: >
)
