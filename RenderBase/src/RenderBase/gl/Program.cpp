
#include <glm/gtc/type_ptr.hpp>

#include <RenderBase/gl/Program.h>
#include <RenderBase/logging.h>
#include <RenderBase/asserts.h>

using namespace std;
using namespace glm;
using namespace rb::gl;

Program::Program(std::vector<Shader*> shaders)
{
    // create program
    glId = glCreateProgram();

    // attach shaders
    for (Shader* shader : shaders) {
        glAttachShader(glId, shader->getGlID());
        this->shaders.push_back(unique_ptr<Shader>(shader));
    }

    // link program
    GLint status;
    glLinkProgram(glId);
    glGetProgramiv(glId, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        failWithErrorMessage();
    }
    RB_DEBUG("Program " << glId << " created");
}

Program::~Program()
{
    // detach shaders
    for (auto& shader : shaders) {
        glDetachShader(glId, shader->getGlID());
    }
    glDeleteProgram(glId);
    RB_DEBUG("Program " << glId << " deleted.");
}

void Program::use()
{
    glUseProgram(glId);
}

void Program::uniform(const std::string& name, int value)
{
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniform1i(glId, location, value);
}

void Program::uniform(const std::string& name, uint32_t value)
{
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniform1ui(glId, location, value);
}

void Program::uniform(const std::string& name, float value)
{
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniform1f(glId, location, value);
}

void Program::uniform(const std::string& name, glm::uvec2 value)
{
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniform2uiv(glId, location, 1, glm::value_ptr(value));
}

void Program::uniform(const std::string& name, glm::vec3 value)
{
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniform3fv(glId, location, 1, glm::value_ptr(value));
}

void Program::uniform(const std::string& name, glm::vec4 value)
{
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniform4fv(glId, location, 1, glm::value_ptr(value));
}

void Program::uniform(const std::string& name, glm::mat3 value)
{
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniformMatrix3fv(glId, location, 1, GL_FALSE, glm::value_ptr(value));
}

void Program::uniform(const std::string& name, glm::mat4 value)
{
    GLuint location = glGetUniformLocation(glId, name.data());
    glProgramUniformMatrix4fv(glId, location, 1, GL_FALSE, glm::value_ptr(value));
}
