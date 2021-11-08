#pragma once

#include <RenderBase/gl/BaseGL.h>

#include <string>

namespace rb::gl {

    class Shader : public BaseGLObject
    {
        public:
            Shader(GLenum type, std::string source);
            ~Shader();
            
            inline GLenum getType() const { return type; }
            
        protected:
            GLenum type;
    };
}
