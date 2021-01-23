
#include <glm/gtc/type_ptr.hpp>
#include <RenderBase/tools/logging.h>

#include <RenderBase/platform/graphics/OpenGL/Program.h>


using namespace std;
using namespace glm;
using namespace rb::opengl;
using ShaderType = rb::ShaderType;

Program::Program(ShaderArray shaders) {

    // create program
    glId = glCreateProgram();

    // attach shaders
    for (auto shader : shaders) {
        auto glShader = static_pointer_cast<opengl::Shader>(shader);
        if (!glShader->isOk()) {
            fail("A shader was not compiled properly and cannot be attached to program:\n" + shader->getErrorMessage() + "\n");
            break;
        }
        glAttachShader(glId, glShader->getGlID());
        attachedShaders.push_back(glShader);
    }

    if (isOk()) {
        // link program
        GLint status;
        glLinkProgram(glId);
        glGetProgramiv(glId, GL_LINK_STATUS, &status);
        if (status != GL_TRUE) {
            GLint errLen = 0;
            glGetProgramiv(glId, GL_INFO_LOG_LENGTH, &errLen);
            auto errorMessage = std::string(" ", errLen);
            glGetProgramInfoLog(glId, errorMessage.size(), &errLen, (char*)errorMessage.data());
            fail(errorMessage);
        }
        RB_DEBUG("Program created");
    }
}

Program::~Program() {
    // detach shaders
    for (auto shader : attachedShaders) {
        glDetachShader(glId, shader->getGlID());
    }
    glDeleteProgram(glId);
    RB_DEBUG("Program deleted.");
}

void Program::use() {
    glUseProgram(glId);
}

void Program::uniform(const std::string& name, int value) {
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniform1i(glId, location, value);
}

void Program::uniform(const std::string& name, uint32_t value) {
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniform1ui(glId, location, value);
}

void Program::uniform(const std::string& name, float value) {
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniform1f(glId, location, value);
}

void Program::uniform(const std::string& name, glm::uvec2 value) {
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniform2uiv(glId, location, 1, glm::value_ptr(value));
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

// void Program::uniform(const std::string& name, const UniformBuffer& value, GLuint bindingPointIndex) {
//     GLuint blockIndex = glGetUniformBlockIndex(glId, name.data());
//     glBindBufferBase(GL_UNIFORM_BUFFER, bindingPointIndex, value.getGlId());
//     glUniformBlockBinding(glId, blockIndex, bindingPointIndex);
// }
