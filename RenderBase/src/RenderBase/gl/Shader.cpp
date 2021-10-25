
#include <RenderBase/gl/Shader.h>
#include <RenderBase/logging.h>
#include <RenderBase/asserts.h>

#include <fstream>
#include <iterator>

using namespace std;
using namespace rb::gl;


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

Shader::Shader(GLenum type, std::string source)
{
    this->type = type;
    source = resolveSourceCode(source);

    // Compile
    glId = glCreateShader(this->type);
    char const* rawSource = source.c_str();
    glShaderSource(glId, 1, &rawSource, nullptr);
    glCompileShader(glId);
    
    // assert failed compilation
    #ifndef NO_ASSERT
        GLint status;
        glGetShaderiv(glId, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE) {
            GLint errLen = 0;
            glGetShaderiv(glId, GL_INFO_LOG_LENGTH, &errLen);
            auto errorMessage = std::string(" ", errLen);
            glGetShaderInfoLog(glId, errorMessage.size(), &errLen, (char*)errorMessage.data());
            RB_ASSERT_MSG(false, "Shader compilation error:\n" + errorMessage);
        }
    #endif
    
    RB_DEBUG("Shader " << glId << " created.");
}

Shader::~Shader()
{
    glDeleteShader(glId);
    RB_DEBUG("Shader " << glId << " deleted.");
}
