
#ifdef DEBUG
    #define NO_DEBUG_LOG
    #define NO_WARNING_LOG
    #include <glm/gtx/string_cast.hpp>
#endif

#include <RenderBase/gl/Program.h>
#include <RenderBase/logging.h>
#include <RenderBase/asserts.h>

#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include <algorithm>

using namespace std;
using namespace glm;
using namespace rb::gl;

Program::Program(vector<std::shared_ptr<Shader>> shaders)
{
    // create program
    glId = glCreateProgram();
    if (!glId) {
        ASSERT_GL_ERRORS();
    }

    // attach shaders
    for (auto shader : shaders) {
        RB_INFO("Attaching shader " << shader->getGlID() << " to program " << glId);
        glAttachShader(glId, shader->getGlID());
        // ASSERT_GL_ERRORS();
        this->shaders.push_back(shader);
    }
    
    if (!this->shaders.empty()) {
        // link program
        glLinkProgram(glId);
        
        // assert link status
        #ifndef NO_ASSERT
            GLint status;
            glGetProgramiv(glId, GL_LINK_STATUS, &status);
            if (status != GL_TRUE) {
                GLint errLen = 0;
                glGetProgramiv(glId, GL_INFO_LOG_LENGTH, &errLen);
                auto errorMessage = std::string(" ", errLen);
                glGetProgramInfoLog(glId, errorMessage.size(), &errLen, (char*)errorMessage.data());
                RB_ASSERT_MSG(false, "Program error:\n" + errorMessage);
            }
        #endif
    }
    
    RB_INFO("Program " << glId << " created");
}


Program::~Program()
{
    // detach shaders
    for (auto shader : shaders) {
        glDetachShader(glId, shader->getGlID());
    }
    
    glDeleteProgram(glId);
    RB_INFO("Program " << glId << " deleted.");
}

void Program::use()
{
    glUseProgram(glId);
}

// setting various uniforms

#define FIND_LOCATION(name) \
    auto location = glGetUniformLocation(glId, name); \
    if (location == -1) { \
        RB_WARNING("Uniform \"" << name << "\" is not used in any shader for program " << glId); \
        return; \
    }

void Program::uniform(const char* name, int32 value)
{
    FIND_LOCATION(name);
    glProgramUniform1i(glId, location, value);
    RB_DEBUG("Uniform \"" << name << "\" set to: " << value);
}

void Program::uniform(const char* name, uint32 value)
{
    FIND_LOCATION(name);
    glProgramUniform1ui(glId, location, value);
    RB_DEBUG("Uniform \"" << name << "\" set to: " << value);
}

void Program::uniform(const char* name, float32 value)
{
    FIND_LOCATION(name);
    glProgramUniform1f(glId, location, value);
    RB_DEBUG("Uniform \"" << name << "\" set to: " << value);
}

void Program::uniform(const char* name, glm::uvec2 value)
{
    FIND_LOCATION(name);
    glProgramUniform2uiv(glId, location, 1, glm::value_ptr(value));
    RB_DEBUG("Uniform \"" << name << "\" set to: " << glm::to_string(value));
}

void Program::uniform(const char* name, glm::vec3 value)
{
    FIND_LOCATION(name);
    glProgramUniform3fv(glId, location, 1, glm::value_ptr(value));
    RB_DEBUG("Uniform \"" << name << "\" set to: " << glm::to_string(value));
}

void Program::uniform(const char* name, glm::vec4 value)
{
    FIND_LOCATION(name);
    glProgramUniform4fv(glId, location, 1, glm::value_ptr(value));
    RB_DEBUG("Uniform \"" << name << "\" set to: " << glm::to_string(value));
}

void Program::uniform(const char* name, glm::mat3 value)
{
    FIND_LOCATION(name);
    glProgramUniformMatrix3fv(glId, location, 1, GL_FALSE, glm::value_ptr(value));
    RB_DEBUG("Uniform \"" << name << "\" set to: " << glm::to_string(value));
}

void Program::uniform(const char* name, glm::mat4 value)
{
    FIND_LOCATION(name);
    glProgramUniformMatrix4fv(glId, location, 1, GL_FALSE, glm::value_ptr(value));
    RB_DEBUG("Uniform \"" << name << "\" set to: " << glm::to_string(value));
}

void Program::uniform(const char* name, GLuint textureUintId, const Texture3D& texture)
{
    FIND_LOCATION(name);
    glBindTextureUnit(textureUintId, texture.getGlID());
    glProgramUniform1i(glId, location, textureUintId);
    RB_DEBUG("Uniform \"" << name << "\" set with 3D texture.");
}

void Program::loadStandardCamera(const Camera& camera)
{
    uniform("cameraPosition",  camera.getPosition());
    uniform("cameraDirection", camera.getDirection());
    uniform("cameraUp",        camera.getUpVector());
    uniform("viewProjection",  camera.getVPMatrix());
}
