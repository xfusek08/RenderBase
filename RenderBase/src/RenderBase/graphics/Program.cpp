
#include <RenderBase/graphics/Program.h>
#include <RenderBase/platform/graphicsPlatform.h>

#ifdef PLATFORM_GRAPHICS_OPENGL
    #include <RenderBase/platform/graphics/OpenGL/Program.h>
#endif

using namespace std;
using namespace rb;

shared_ptr<Program> Program::create(ShaderArray shaders) {
    #ifdef PLATFORM_GRAPHICS_OPENGL
        return make_shared<opengl::Program>(shaders);
    #else
        return nullptr;
    #endif
}
