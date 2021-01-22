
#include <RenderBase/graphics/Shader.h>
#include <RenderBase/platform/graphicsPlatform.h>

#ifdef PLATFORM_GRAPHICS_OPENGL
    #include <RenderBase/platform/graphics/OpenGL/Shader.h>
#endif

using namespace std;
using namespace rb;

shared_ptr<Shader> Shader::create(ShaderType type, std::string source) {
    #ifdef PLATFORM_GRAPHICS_OPENGL
        return make_shared<opengl::Shader>(type, source);
    #else
        return nullptr;
    #endif
}
