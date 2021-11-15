#pragma once

#include <RenderBase/gl/BaseGL.h>

#include <vector>
#include <string>

#ifdef DEBUG
    #define DEFAULT_SHADER_DEFINES ShaderDefines{"DEBUG"}
#else
    #define DEFAULT_SHADER_DEFINES ShaderDefines{"RELEASE"}
#endif

namespace rb::gl {
    
    using ShaderDefines = std::initializer_list<std::string>;
    
    class Shader : public BaseGLObject
    {
        public:
            Shader(GLenum type, std::string source, const std::vector<std::string>& defines = DEFAULT_SHADER_DEFINES);
            ~Shader();
            
            inline GLenum getType() const { return type; }
            
        protected:
            GLenum type;
    };
}
