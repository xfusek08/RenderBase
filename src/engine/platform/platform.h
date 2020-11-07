#pragma once

#include <memory>
#include <string>

#if __has_include (<glad/glad.h>)
    #include <glad/glad.h>
    #define PLATFORM_GL_GLAD
#endif // else another openGL or migrate to GPUEngine

#if __has_include (<SDL.h>)
    #include <engine/platform/sdl.h>
    #define PLATFORM_WINDOW_SDL
#else
    #include <engine/window.h>
#endif // else another window lib

namespace engine {
    namespace platform {
        std::unique_ptr<engine::Window> createWindow(const std::string& title, uint32_t width, uint32_t height);
        bool loadOpenGlFunctions();
    }
}
