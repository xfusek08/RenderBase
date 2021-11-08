cmake_minimum_required(VERSION 3.0)

set(IMGU_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imconfig.h
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui.h
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_internal.h
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imstb_rectpack.h
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imstb_textedit.h
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imstb_truetype.h

    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_impl_opengl3.h
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_impl_opengl3_loader.h

    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_impl_glfw.h
)

set(IMGU_INCLUDES
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}
)
