#include <stdexcept>
#include <fstream>

#include <rb/graphics.h>
#include <rb/platform/platform.h>

using namespace std;
using namespace glm;
using namespace rb;

Graphics::Graphics() {
    if (!platform::loadOpenGlFunctions()) {
        throw std::runtime_error("Failed to initialize graphics");
    }
}

GLuint Graphics::createShader(GLenum type, string const& src) {
    string source = "";
    std::ifstream stream(src);
    if (stream.good()) {
        source = string(
            std::istream_iterator<char>(stream >> std::noskipws),
            std::istream_iterator<char>()
        );
    } else {
        source = src;
    }

    auto id = glCreateShader(type);
    char const* srcs[] = { source.data() };
    glShaderSource(id, 1, srcs, nullptr);
    glCompileShader(id);
    GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        GLint errLen = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &errLen);
        auto buf = std::string(" ", errLen);
        glGetShaderInfoLog(id, buf.size(), &errLen, (char*)buf.data());
        throw std::runtime_error("Compilation failed: " + buf);
    }
    return id;
}

GLuint Graphics::createProgram(vector<GLuint> shaders) {
    GLint status;
    auto id = glCreateProgram();

    for (auto shader : shaders) {
        glAttachShader(id, shader);
    }
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        GLint errLen = 0;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &errLen);
        auto buf = std::string(" ", errLen);
        glGetProgramInfoLog(id, buf.size(), &errLen, (char*)buf.data());
        throw std::runtime_error("Linking failed: " + buf);
    }
    return id;
}