#pragma once

#include <memory>

#include <RenderBase/graphics/Program.h>
#include <RenderBase/platform/graphics/OpenGL/Shader.h>
#include <RenderBase/platform/graphics/OpenGL/BaseGLObject.h>

namespace rb {
    namespace opengl {

        class Program : public BaseGLObject, public rb::Program
        {

            public:
                Program(ShaderArray shaders = {});

                template <typename... ARGS>
                Program(ARGS... shaders) : Program(ShaderArray({shaders...})) {}

                ~Program();

                void use();

                void uniform(const std::string& name, int value);
                void uniform(const std::string& name, uint32_t value);
                void uniform(const std::string& name, float value);
                void uniform(const std::string& name, glm::uvec2 value);
                void uniform(const std::string& name, glm::vec3 value);
                void uniform(const std::string& name, glm::vec4 value);
                void uniform(const std::string& name, glm::mat3 value);
                void uniform(const std::string& name, glm::mat4 value);
                // void uniform(const std::string& name, const UniformBuffer& value, GLuint bindingPointIndex = 0);

            private:
                std::vector<std::shared_ptr<opengl::Shader>> attachedShaders = {};
        };

    }
}
