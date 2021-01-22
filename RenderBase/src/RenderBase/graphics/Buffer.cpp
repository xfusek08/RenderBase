
#include <RenderBase/graphics/Buffer.h>
#include <RenderBase/platform/graphicsPlatform.h>

#ifdef PLATFORM_GRAPHICS_OPENGL
    #include <RenderBase/platform/graphics/OpenGL/Buffer.h>
#endif

using namespace std;
using namespace rb;

shared_ptr<Buffer> Buffer::create() {
    #ifdef PLATFORM_GRAPHICS_OPENGL
        return make_shared<opengl::Buffer>();
    #else
        return nullptr;
    #endif
}
