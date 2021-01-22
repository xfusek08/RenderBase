
#include <RenderBase/platform/platformWindow.h>

#include <memory>
#include <iostream>

#include <RenderBase/tools/logging.h>

#if defined PLATFORM_WINDOW_GLFW
    #include <RenderBase/platform/window/GLFW/glfw.h>
#elif defined PLATFORM_WINDOW_SDL
    #include <RenderBase/platform/window/SDL2/sdl.h>
#endif

using namespace std;
using namespace rb;

// #########################################################################
// Module interface functions
// #########################################################################

shared_ptr<rb::Window> platform::createWindow(const string& title, uint32_t width, uint32_t height) {
    #if defined PLATFORM_WINDOW_GLFW
        RB_DEBUG("Using GLFW as a window platform");
        return make_shared<platform::glfw::Window>(title, width, height);
    #elif defined PLATFORM_WINDOW_SDL
        RB_DEBUG("Using SDL2 as window platform");
        return make_shared<platform::sdl::Window>(title, width, height);
    #endif // try another window lib
    return nullptr;
}

shared_ptr<PerformenceAnalyzer> platform::createPerformanceAnalyzer() {
    #if defined PLATFORM_WINDOW_GLFW
        return make_shared<platform::glfw::PerformenceAnalyzer>();
    #elif defined PLATFORM_WINDOW_SDL
        return make_shared<platform::sdl::PerformenceAnalyzer>();
    #endif
    return nullptr;
}
