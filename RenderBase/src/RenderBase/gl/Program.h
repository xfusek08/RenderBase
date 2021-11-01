#pragma once

#include <RenderBase/defines.h>
#include <RenderBase/gl/BaseGLObject.h>
#include <RenderBase/gl/Shader.h>
#include <RenderBase/gl/Texture3D.h>

#include <RenderBase/tools/camera.h>

#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace rb::gl {
    
    class Program : public BaseGLObject
    {
        public:
            Program(std::vector<Shader*> shaders = {});

            // template <typename... ARGS>
            // Program(ARGS... shaders) : Program(std::vector<Shader*>({shaders...})) {}

            ~Program();

            void use();
            
            void uniform(const char* name, int32 value);
            void uniform(const char* name, uint32 value);
            void uniform(const char* name, float32 value);
            void uniform(const char* name, glm::uvec2 value);
            void uniform(const char* name, glm::vec3 value);
            void uniform(const char* name, glm::vec4 value);
            void uniform(const char* name, glm::mat3 value);
            void uniform(const char* name, glm::mat4 value);
            void uniform(const char* name, GLuint textureUintId, const Texture3D& texture);
            
            void loadStandardCamera(const Camera& camera);
            
        private:
            std::vector<std::unique_ptr<Shader>> shaders = {};
    };
    
}
