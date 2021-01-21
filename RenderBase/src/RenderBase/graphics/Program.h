#pragma once

#include <memory>

#include <RenderBase/graphics/GraphicsBaseObject.h>
#include <RenderBase/graphics/Shader.h>
#include <RenderBase/graphics/Buffer.h>

namespace rb {

    class Program : public  GraphicsBaseObject
    {
        using shaderArray = std::vector<std::shared_ptr<Shader>>;

        public:
            Program(shaderArray shaders = {});

            template <typename... ARGS>
            Program(ARGS... shaders) : Program(shaderArray({shaders...})) {}

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
            void uniform(const std::string& name, const UniformBuffer& value, GLuint bindingPointIndex = 0);

        private:
            shaderArray attachedShaders = {};
    };

}
