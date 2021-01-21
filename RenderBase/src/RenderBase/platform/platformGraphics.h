#pragma once

#if __has_include (<glad/glad.h>)
    #define PLATFORM_GRAPHICS_OPENGL
    #define PLATFORM_GRAPHICS_OPENGL_LOADER_GLAD
    #include <glad/glad.h>
#endif // else - another openGL loader, directX or GPUEngine?

namespace rb {
    namespace platform {
        bool loadOpenGlFunctions();
    }
}
