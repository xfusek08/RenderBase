cmake_minimum_required (VERSION 3.18)

Project(RenderBaseGlobal)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/build)

add_subdirectory(RenderBase)
add_subdirectory(Demos/HelloTriangle)
add_subdirectory(Sandbox)
