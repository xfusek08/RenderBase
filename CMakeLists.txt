cmake_minimum_required (VERSION 3.18)
project (RenderBase)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)

set(SOURCES
    src/RenderBase/rb.h

    # core
    src/RenderBase/core/graphics.h
    src/RenderBase/core/event.h
    src/RenderBase/core/application.h   src/RenderBase/core/application.cpp
    src/RenderBase/core/window.h        src/RenderBase/core/window.cpp
    src/RenderBase/core/performance.h   src/RenderBase/core/performance.cpp

    # platform
    src/RenderBase/platform/platform.h  src/RenderBase/platform/platform.cpp
    src/RenderBase/platform/sdl.h       src/RenderBase/platform/sdl.cpp

    # tools
    src/RenderBase/tools/logging.h
    src/RenderBase/tools/utils.h        src/RenderBase/tools/utils.cpp
    src/RenderBase/tools/camera.h       src/RenderBase/tools/camera.cpp

    # graphics.h module components
    src/RenderBase/core/graphics/GraphicsBaseObject.h
    src/RenderBase/core/graphics/GraphicsContext.h      src/RenderBase/core/graphics/GraphicsContext.cpp
    src/RenderBase/core/graphics/Program.h              src/RenderBase/core/graphics/Program.cpp
    src/RenderBase/core/graphics/Shader.h               src/RenderBase/core/graphics/Shader.cpp
    src/RenderBase/core/graphics/Buffer.h               src/RenderBase/core/graphics/Buffer.cpp
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

add_subdirectory(vendor/glad)

add_library(${PROJECT_NAME}
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

if (NOT DEFINED COMPILE_DEFINITIONS)
    set(COMPILE_DEFINITIONS
        "PROJECT_NAME=\"${PROJECT_NAME}\""
        "DEBUG"
        # $<$<CONFIG:Debug>:
        #     "DEBUG"
        # >
        # $<$<CONFIG:Release>: >
    )
endif()

message(" ")
message("====== ${PROJECT_NAME} compile definitions =======")
message(${COMPILE_DEFINITIONS})
message("==================================================")
message(" ")
target_compile_definitions(${PROJECT_NAME} PUBLIC ${COMPILE_DEFINITIONS})
