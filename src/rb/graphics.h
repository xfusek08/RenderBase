#pragma once

#include <string>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <rb/platform/platform.h>

namespace rb {

    class Graphics
    {
        public:
            Graphics();

            GLuint createShader(GLenum type, std::string const& src);
            GLuint createProgram(std::vector<GLuint> shaders);

            template <typename... ARGS>
            GLuint createProgram(ARGS const&... ids);
    };

}

template <typename... ARGS>
GLuint rb::Graphics::createProgram(ARGS const&... ids) {
    return createProgram({ids...});
}
