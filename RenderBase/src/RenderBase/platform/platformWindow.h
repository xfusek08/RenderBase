#pragma once

#include <RenderBase/window.h>

#if __has_include (<glfw3.h>)
    #define PLATFORM_WINDOW_GLFW
#elif __has_include (<SDL.h>)
    #define PLATFORM_WINDOW_SDL
#endif // else another window lib

namespace rb {
    namespace platform {
        std::shared_ptr<rb::Window>          createWindow(const std::string& title, uint32_t width, uint32_t height);
        std::shared_ptr<PerformenceAnalyzer> createPerformanceAnalyzer();
    }
}
