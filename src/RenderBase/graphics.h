#pragma once

#include <string>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <RenderBase/platform/platform.h>

namespace rb {

    class GlObject {
        public:
            inline       GLuint        getGlId()         const { return glId; }
            inline const std::string&  getErrorMessage() const { return errorMessage; }
        protected:
            GLuint glId = 0;
            std::string errorMessage = "";
    };

    class Shader : public GlObject
    {
        public:
            Shader(GLenum type, const std::string& src);
            ~Shader();
    };

    class Program : public  GlObject
    {
        using shaderArray = std::vector<std::shared_ptr<Shader>>;

        public:
            Program(shaderArray shaders = {});
            template <typename... ARGS>
            Program(ARGS... shaders) : Program(shaderArray({shaders...})) {}
            ~Program();

            void use();

            void uniform(const std::string& name, int value);
            void uniform(const std::string& name, float value);
            void uniform(const std::string& name, glm::vec3 value);
            void uniform(const std::string& name, glm::mat3 value);
            void uniform(const std::string& name, glm::mat4 value);

        private:
            shaderArray attachedShaders = {};
    };

    class GraphicsContext
    {
        public:
            GraphicsContext();
    };
}
