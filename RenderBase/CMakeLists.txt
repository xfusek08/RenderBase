cmake_minimum_required (VERSION 3.18.1)
project(RenderBase)

include(../CmakeUtils/ListUtils.cmake)

set(CMAKE_CXX_STANDARD 17)

# resolve window library usage
# tuples inspired by: https://cmake.org/pipermail/cmake/2011-November/047833.html
# <option name>;<package name>;<link target names>
set(SUPPORTED_WINDW_LIBS
    "glfw\;glfw3\;glfw"
    "sdl\;SDL2\;SDL2::SDL2main SDL2::SDL2-static"
)

list_column(0 SUPPORTED_WINDW_LIBS swl_names)

set(WINDOW_PLATFORM "auto" CACHE STRING "Window library to use (default: \"auto\")")
set_property(CACHE WINDOW_PLATFORM PROPERTY STRINGS "auto" ${swl_names})

foreach(lib_tuple ${SUPPORTED_WINDW_LIBS})
    list(GET lib_tuple 0 lib_name)
    list(GET lib_tuple 1 package_name)
    list(GET lib_tuple 2 targets)

    if (${lib_name} STREQUAL ${WINDOW_PLATFORM} OR ${WINDOW_PLATFORM} STREQUAL "auto")
        find_package(${package_name} QUIET)
        if (${${package_name}_FOUND} OR ${lib_name} STREQUAL ${WINDOW_PLATFORM})
            message("Using ${package_name} package as winidow library ${lib_name} with targets: ${targets}")
            set(window_lib_package ${package_name})
            string(REPLACE " " "\;" window_lib_targets ${targets})
            break()
        endif()
    endif()
endforeach()

if (NOT DEFINED window_lib_package)
    list_column(1 SUPPORTED_WINDW_LIBS package_directories)
    list_format(package_directories "    [var]_DIR" package_directories)
    list(JOIN package_directories ",\n" package_directories)
    message(FATAL_ERROR "No window library can be found automaticaly, please define any of following directories:\n${package_directories}")
endif()

find_package(${window_lib_package} REQUIRED)
find_package(glm REQUIRED)
add_subdirectory(vendor/glad)

set(SOURCES
    src/RenderBase/graphics.h
    src/RenderBase/event.h
    src/RenderBase/application.h src/RenderBase/application.cpp
    src/RenderBase/window.h      src/RenderBase/window.cpp
    src/RenderBase/performance.h src/RenderBase/performance.cpp

    # platform
        src/RenderBase/platform/graphicsPlatform.h
        src/RenderBase/platform/platformWindow.h src/RenderBase/platform/platformWindow.cpp

        # window libs
        src/RenderBase/platform/window/glfw/glfw.h  src/RenderBase/platform/window/glfw/glfw.cpp
        src/RenderBase/platform/window/SDL2/sdl.h   src/RenderBase/platform/window/SDL2/sdl.cpp

        # graphics API - OpenGL
        src/RenderBase/platform/graphics/OpenGL/GLGraphicsContext.h src/RenderBase/platform/graphics/OpenGL/GLGraphicsContext.cpp

        src/RenderBase/platform/graphics/OpenGL/BaseGLObject.h
        # src/RenderBase/platform/graphics/OpenGL/Buffer.h      src/RenderBase/platform/graphics/OpenGL/Buffer.cpp
        src/RenderBase/platform/graphics/OpenGL/Program.h     src/RenderBase/platform/graphics/OpenGL/Program.cpp
        src/RenderBase/platform/graphics/OpenGL/Shader.h      src/RenderBase/platform/graphics/OpenGL/Shader.cpp

    # tools
        src/RenderBase/tools/entryPoint.h
        src/RenderBase/tools/logging.h
        src/RenderBase/tools/macroUtils.h
        src/RenderBase/tools/utils.h        src/RenderBase/tools/utils.cpp
        src/RenderBase/tools/camera.h       src/RenderBase/tools/camera.cpp

    # graphics.h module components
        src/RenderBase/graphics/GraphicsContext.h
        src/RenderBase/graphics/GraphicsObject.h   src/RenderBase/graphics/GraphicsObject.cpp
        src/RenderBase/graphics/Program.h          src/RenderBase/graphics/Program.cpp
        src/RenderBase/graphics/Shader.h           src/RenderBase/graphics/Shader.cpp
        # src/RenderBase/graphics/Buffer.h           src/RenderBase/graphics/Buffer.h
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

add_library(${PROJECT_NAME}
     ${SOURCES}
    # ${IMGUI_HEADERS}
    # ${IMGUI_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC  glm::glm
    PUBLIC  glad
    PRIVATE ${window_lib_targets}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
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
