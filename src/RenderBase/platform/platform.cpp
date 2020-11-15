
#include <memory>
#include <iostream>
#include <RenderBase/platform/platform.h>

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
    #ifdef PLATFORM_GL_GLAD
        auto functionPointer = getGlProcAddressFunction();
        if (functionPointer != nullptr) {
            if (gladLoadGLLoader((GLADloadproc)getGlProcAddressFunction())) {
                return true;
            }
            cout << "Failed to initialize GLAD" << endl; // Todo: use logger
        }
    #endif // else another lib load
    return false;
}

shared_ptr<rb::Window> platform::createWindow(const string& title, uint32_t width, uint32_t height) {
    #ifdef PLATFORM_WINDOW_SDL
        return make_shared<platform::sdl::SDLWindow>(title, width, height);
    #endif // try another window lib
    return nullptr;
}

shared_ptr<PerformenceAnalyzer> platform::createPerformanceAnalyzer() {
    #ifdef PLATFORM_WINDOW_SDL
        return make_shared<platform::sdl::SDLPerformenceAnalyzer>();
    #endif // try another window lib
    return nullptr;
}
