
#include <memory>
#include <iostream>
#include <RenderBase/tools/logging.h>
#include <RenderBase/platform/platformGraphics.h>
#include <RenderBase/platform/platformWindow.h>

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

void *getGlProcAddressFunction() {
    #ifdef PLATFORM_WINDOW_SDL
        return SDL_GL_GetProcAddress;
    #endif // try another window lib
    return nullptr;
}

bool rb::platform::loadOpenGlFunctions() {
    #ifdef PLATFORM_GRAPHICS_OPENGL
        #ifdef PLATFORM_GRAPHICS_OPENGL_LOADER_GLAD
            LOG_DEBUG("Useing GLAD as graphics API platform");
            auto functionPointer = getGlProcAddressFunction();
            if (functionPointer != nullptr) {
                if (gladLoadGLLoader((GLADloadproc)getGlProcAddressFunction())) {
                    return true;
                }
                ASSERT_DEBUG(false, "Failed to initialize GLAD");
            }
        #endif
    #endif // else another lib load
    return false;
}

shared_ptr<rb::Window> platform::createWindow(const string& title, uint32_t width, uint32_t height) {
    #if defined PLATFORM_WINDOW_GLFW
        LOG_DEBUG("Using GLFW as a window platform");
        return make_shared<platform::glfw::GLFWWindow>(title, width, height);
    #elif defined PLATFORM_WINDOW_SDL
        LOG_DEBUG("Using SDL2 as window platform");
        return make_shared<platform::sdl::SDLWindow>(title, width, height);
    #endif // try another window lib
    return nullptr;
}

shared_ptr<PerformenceAnalyzer> platform::createPerformanceAnalyzer() {
    #if defined PLATFORM_WINDOW_GLFW
        return make_shared<platform::glfw::GLFWPerformenceAnalyzer>();
    #elif defined PLATFORM_WINDOW_SDL
        return make_shared<platform::sdl::SDLPerformenceAnalyzer>();
    #endif
    return nullptr;
}
