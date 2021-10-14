#pragma once

#include <RenderBase/defines.h>
#include <RenderBase/gl/BaseGLObject.h>
#include <RenderBase/gl/Shader.h>

#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace rb::gl {
    
    class Program : public BaseGLObject
    {
        public:
            Program(std::vector<Shader*> shaders);

            template <typename... ARGS>
            Program(ARGS... shaders) : Program(std::vector<Shader*>({shaders...})) {}

            ~Program();

            void use();

            void uniform(const std::string& name, int value);
            void uniform(const std::string& name, uint32 value);
            void uniform(const std::string& name, float value);
            void uniform(const std::string& name, glm::uvec2 value);
            void uniform(const std::string& name, glm::vec3 value);
            void uniform(const std::string& name, glm::vec4 value);
            void uniform(const std::string& name, glm::mat3 value);
            void uniform(const std::string& name, glm::mat4 value);
            
        private:
            std::vector<std::unique_ptr<Shader>> shaders = {};
    };
    
}
