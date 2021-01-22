#pragma once

// detects opengl

#if __has_include (<glad/glad.h>)
    #define PLATFORM_GRAPHICS_OPENGL
#else
    #error "No graphich platform library found"
#endif
