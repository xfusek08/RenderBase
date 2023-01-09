
#include <RenderBase/core/graphics/Shader.h>
#include <RenderBase/tools/logging.h>

#include <string>
#include <iterator>
#include <fstream>

using namespace std;
using namespace glm;
using namespace rb;

Shader::Shader(GLenum type, const std::string& src) : GraphicsBaseObject() {
    // Source loading - from file or src is actual source code
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

    // Compile
    glId = glCreateShader(type);
    char const* rawSource = source.c_str();
    glShaderSource(glId, 1, &rawSource, nullptr);
    glCompileShader(glId);

    // Get status and possible errors
    GLint status;
    glGetShaderiv(glId, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        GLint errLen = 0;
        glGetShaderiv(glId, GL_INFO_LOG_LENGTH, &errLen);
        errorMessage = std::string(" ", errLen);
        glGetShaderInfoLog(glId, errorMessage.size(), &errLen, (char*)errorMessage.data());
        errorMessage = "Shader error: " + errorMessage;
    }
    LOG_DEBUG("Shader created");
}

Shader::~Shader() {
    glDeleteShader(glId);
    LOG_DEBUG("shader deleted");
}
