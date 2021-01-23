
#include <RenderBase/platform/graphics/OpenGL/Shader.h>

#include <fstream>

#include <RenderBase/tools/logging.h>

using namespace std;
using namespace rb::opengl;
using ShaderType = rb::ShaderType;

// #########################################################################
// Internal module function
// #########################################################################

string resolveSourceCode(string source) {
    string sourceCode = "";
    std::ifstream stream(source);
    if (stream.good()) {
        sourceCode = string(
            std::istream_iterator<char>(stream >> std::noskipws),
            std::istream_iterator<char>()
        );
    } else {
        sourceCode = source;
    }
    return sourceCode;
}

// #########################################################################
// Shader implementation
// #########################################################################

Shader::Shader(ShaderType type, std::string source) {
    this->type = type;
    source = resolveSourceCode(source);

    // Compile
    glId = glCreateShader(getGLType());
    char const* rawSource = source.c_str();
    glShaderSource(glId, 1, &rawSource, nullptr);
    glCompileShader(glId);

    // Get status and possible errors
    GLint status;
    glGetShaderiv(glId, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        GLint errLen = 0;
        glGetShaderiv(glId, GL_INFO_LOG_LENGTH, &errLen);
        auto errorMessage = std::string(" ", errLen);
        glGetShaderInfoLog(glId, errorMessage.size(), &errLen, (char*)errorMessage.data());
        fail("Shader compile error:\n"  + errorMessage);
    }
    RB_DEBUG("Shader created.");
}

Shader::~Shader() {
    glDeleteShader(glId);
    RB_DEBUG("Shader deleted.");
}

GLenum Shader::getGLType() const {
    switch (type)
    {
        case ShaderType::Vertex: return GL_VERTEX_SHADER;
        case ShaderType::Fragment: return GL_FRAGMENT_SHADER;
        default: return GL_NONE;
    }
}
