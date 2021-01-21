cmake_minimum_required (VERSION 3.18)

option(RB_BUILD_DEMOS "Build demo projects" ON)

add_subdirectory(RenderBase)

if(${DILIGENT_BUILD_DEMOS})
    add_subdirectory(Demos)
endif()
