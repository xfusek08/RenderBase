#include <RenderBase/core/graphics.h>
#include <RenderBase/tools/logging.h>

#include <stdexcept>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;
using namespace rb;

//////////////////////////////////////////
// Program class
//////////////////////////////////////////

Program::Program(Program::shaderArray shaders) {

    // create program
    glId = glCreateProgram();

    // attach shaders
    for (auto const& shader : shaders) {
        if (!shader->getErrorMessage().empty()) {
            errorMessage = "A shader was not compiled properly and cannot be attached to program:\n" + shader->getErrorMessage() + "\n";
            break;
        }
        glAttachShader(glId, shader->getGlId());
    }

    attachedShaders = shaders;

    // link program
    GLint status;
    glLinkProgram(glId);
    glGetProgramiv(glId, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        GLint errLen = 0;
        glGetProgramiv(glId, GL_INFO_LOG_LENGTH, &errLen);
        errorMessage = std::string(" ", errLen);
        glGetProgramInfoLog(glId, errorMessage.size(), &errLen, (char*)errorMessage.data());
    }
    LOG_DEBUG("Program created");
}

Program::~Program() {
    // detach shaders
    for (auto const& shader : attachedShaders) {
        glDetachShader(glId, shader->getGlId());
    }
    glDeleteProgram(glId);
    LOG_DEBUG("Program deleted");
}

void Program::use() {
    glUseProgram(glId);
}

void Program::uniform(const std::string& name, int value) {
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniform1i(glId, location, value);
}

void Program::uniform(const std::string& name, float value) {
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniform1f(glId, location, value);
}

void Program::uniform(const std::string& name, glm::vec3 value) {
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniform3fv(glId, location, 1, glm::value_ptr(value));
}

void Program::uniform(const std::string& name, glm::vec4 value) {
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniform4fv(glId, location, 1, glm::value_ptr(value));
}

void Program::uniform(const std::string& name, glm::mat3 value) {
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniformMatrix3fv(glId, location, 1, GL_FALSE, glm::value_ptr(value));
}

void Program::uniform(const std::string& name, glm::mat4 value) {
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniformMatrix4fv(glId, location, 1, GL_FALSE, glm::value_ptr(value));
}

//////////////////////////////////////////
// Shader
//////////////////////////////////////////

Shader::Shader(GLenum type, const std::string& src) : GlObject() {
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

//////////////////////////////////////////
// GraphicsContext
//////////////////////////////////////////

GraphicsContext::GraphicsContext() {
    if (!platform::loadOpenGlFunctions()) {
        throw std::runtime_error("Failed to initialize graphics");
    }
}
