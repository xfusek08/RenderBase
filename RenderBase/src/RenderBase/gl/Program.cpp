
#define NO_DEBUG_LOG

#include <RenderBase/gl/Program.h>
#include <RenderBase/logging.h>
#include <RenderBase/asserts.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace std;
using namespace glm;
using namespace rb::gl;

#ifndef NO_ASSERT
    #define ASSERT_GL_ERRORS() \
        GLint status; \
        glGetProgramiv(glId, GL_LINK_STATUS, &status); \
        if (status != GL_TRUE) { \
            GLint errLen = 0; \
            glGetProgramiv(glId, GL_INFO_LOG_LENGTH, &errLen); \
            auto errorMessage = std::string(" ", errLen); \
            glGetProgramInfoLog(glId, errorMessage.size(), &errLen, (char*)errorMessage.data()); \
            RB_ASSERT_MSG(false, "Program error:\n" + errorMessage); \
        }
#else
    #define ASSERT_GL_ERRORS()
#endif


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
    glLinkProgram(glId);
    ASSERT_GL_ERRORS();
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
    ASSERT_GL_ERRORS();
}

// setting various uniforms

#define CHECK_LOCATION(name) \
    auto location = glGetUniformLocation(glId, name); \
    if (location == -1) { \
        RB_WARNING("Uniform \"" << name << "\" is not used in any shader for program " << glId); \
        return; \
    }

void Program::uniform(const char* name, int32 value)
{
    CHECK_LOCATION(name);
    glProgramUniform1i(glId, location, value);
    ASSERT_GL_ERRORS();
    RB_DEBUG("Uniform \"" << name << "\" set to: " << value);
}

void Program::uniform(const char* name, uint32 value)
{
    CHECK_LOCATION(name);
    glProgramUniform1ui(glId, location, value);
    ASSERT_GL_ERRORS();
    RB_DEBUG("Uniform \"" << name << "\" set to: " << value);
}

void Program::uniform(const char* name, float32 value)
{
    CHECK_LOCATION(name);
    glProgramUniform1f(glId, location, value);
    ASSERT_GL_ERRORS();
    RB_DEBUG("Uniform \"" << name << "\" set to: " << value);
}

void Program::uniform(const char* name, glm::uvec2 value)
{
    CHECK_LOCATION(name);
    glProgramUniform2uiv(glId, location, 1, glm::value_ptr(value));
    ASSERT_GL_ERRORS();
    RB_DEBUG("Uniform \"" << name << "\" set to: " << glm::to_string(value));
}

void Program::uniform(const char* name, glm::vec3 value)
{
    CHECK_LOCATION(name);
    glProgramUniform3fv(glId, location, 1, glm::value_ptr(value));
    ASSERT_GL_ERRORS();
    RB_DEBUG("Uniform \"" << name << "\" set to: " << glm::to_string(value));
}

void Program::uniform(const char* name, glm::vec4 value)
{
    CHECK_LOCATION(name);
    glProgramUniform4fv(glId, location, 1, glm::value_ptr(value));
    ASSERT_GL_ERRORS();
    RB_DEBUG("Uniform \"" << name << "\" set to: " << glm::to_string(value));
}

void Program::uniform(const char* name, glm::mat3 value)
{
    CHECK_LOCATION(name);
    glProgramUniformMatrix3fv(glId, location, 1, GL_FALSE, glm::value_ptr(value));
    ASSERT_GL_ERRORS();
    RB_DEBUG("Uniform \"" << name << "\" set to: " << glm::to_string(value));
}

void Program::uniform(const char* name, glm::mat4 value)
{
    CHECK_LOCATION(name);
    glProgramUniformMatrix4fv(glId, location, 1, GL_FALSE, glm::value_ptr(value));
    ASSERT_GL_ERRORS();
    RB_DEBUG("Uniform \"" << name << "\" set to: " << glm::to_string(value));
}

void Program::uniform(const char* name, GLuint textureUintId, const Texture3D& texture)
{
    CHECK_LOCATION(name);
    glBindTextureUnit(textureUintId, texture.getGlID());
    glProgramUniform1i(glId, location, textureUintId);
    ASSERT_GL_ERRORS();
    RB_DEBUG("Uniform \"" << name << "\" set with 3D texture.");
}

void Program::loadStandardCamera(const Camera& camera)
{
    uniform("cameraPosition",  camera.getPosition());
    uniform("cameraDirection", camera.getDirection());
    uniform("cameraUp",        camera.getUpVector());
    uniform("mvp",             camera.getMVPMatrix());
}
