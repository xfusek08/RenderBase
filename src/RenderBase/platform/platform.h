#pragma once

#include <memory>
#include <string>

#if __has_include (<glad/glad.h>)
    #include <glad/glad.h>
    #define PLATFORM_GL_GLAD
#endif // else another openGL or migrate to GPUEngine

#if __has_include (<SDL.h>)
    #include <RenderBase/platform/sdl.h>
    #define PLATFORM_WINDOW_SDL
#else
    #include <RenderBase/core/window.h>
#endif // else another window lib

namespace rb {
    namespace platform {
        bool loadOpenGlFunctions();
        std::shared_ptr<rb::Window>          createWindow(const std::string& title, uint32_t width, uint32_t height);
        std::shared_ptr<PerformanceAnalyzer> createPerformanceAnalyzer();
    }
}
