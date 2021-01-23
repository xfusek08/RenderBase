#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include <RenderBase/FailableObject.h>

namespace rb {

    class Shader;

    using ShaderArray = std::vector<std::shared_ptr<Shader>>;

    class Program : public FailableObject
    {
        public:
            static std::shared_ptr<Program> create(ShaderArray shaders = {});

            template <typename... ARGS>
            static std::shared_ptr<Program> create(ARGS... shaders) { return create(ShaderArray({shaders...})); }

            virtual void use() = 0;
            virtual void uniform(const std::string& name, int value) = 0;
            virtual void uniform(const std::string& name, uint32_t value) = 0;
            virtual void uniform(const std::string& name, float value) = 0;
            virtual void uniform(const std::string& name, glm::uvec2 value) = 0;
            virtual void uniform(const std::string& name, glm::vec3 value) = 0;
            virtual void uniform(const std::string& name, glm::vec4 value) = 0;
            virtual void uniform(const std::string& name, glm::mat3 value) = 0;
            virtual void uniform(const std::string& name, glm::mat4 value) = 0;
            // virtual void uniform(const std::string& name, const UniformBuffer& value) = 0;
    };

}
