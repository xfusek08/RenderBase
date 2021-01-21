#pragma once

#include <RenderBase/graphics/GraphicsBaseObject.h>

namespace rb {

    class Shader : public GraphicsBaseObject
    {
        public:
            Shader(GLenum type, const std::string& src);
            ~Shader();
    };
}
