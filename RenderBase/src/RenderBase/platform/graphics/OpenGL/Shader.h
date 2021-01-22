#pragma once

#include <RenderBase/graphics/Shader.h>
#include <RenderBase/platform/graphics/OpenGL/BaseGLObject.h>

namespace rb {
    namespace opengl {

        class Shader : public BaseGLObject, public rb::Shader
        {
            public:
                Shader(ShaderType type, std::string source);
                ~Shader();

                GLenum getGLType() const;
        };

    }
}
