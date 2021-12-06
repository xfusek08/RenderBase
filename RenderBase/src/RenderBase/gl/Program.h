#pragma once

#include <RenderBase/defines.h>

#include <RenderBase/gl/BaseGL.h>
#include <RenderBase/gl/Shader.h>
#include <RenderBase/gl/Buffer.h>
#include <RenderBase/gl/Texture3D.h>

#include <RenderBase/tools/camera.h>

#include <glm/glm.hpp>

#include <memory>
#include <vector>

namespace rb::gl {
    
    using ShaderArray = std::vector<std::shared_ptr<Shader>>;
    
    class Program : public BaseGLObject
    {
        public:
            Program(ShaderArray shaders = {});

            template <typename... ARGS>
            Program(ARGS... shaders) : Program(ShaderArray{shaders...}) {}

            ~Program();

            void use() const;
            
            void uniform(const char* name, const int32 value) const;
            void uniform(const char* name, const uint32 value) const;
            void uniform(const char* name, const float32 value) const;
            void uniform(const char* name, const glm::uvec2 value) const;
            void uniform(const char* name, const glm::vec3 value) const;
            void uniform(const char* name, const glm::vec4 value) const;
            void uniform(const char* name, const glm::mat3 value) const;
            void uniform(const char* name, const glm::mat4 value) const;
            void uniform(const char* name, const Buffer& value, GLuint bindingPoint) const;
            void uniform(const char* name, const GLuint textureUintId, const Texture3D& texture) const;
            
            void loadStandardCamera(const Camera& camera);
            
        private:
            ShaderArray shaders = {};
    };
    
}
