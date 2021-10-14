#include <RenderBase/gl/BaseGLObject.h>
#include <RenderBase/asserts.h>

void rb::gl::BaseGLObject::failWithErrorMessage()
{
    GLint errLen = 0;
    glGetProgramiv(glId, GL_INFO_LOG_LENGTH, &errLen);
    auto errorMessage = std::string(" ", errLen);
    glGetProgramInfoLog(glId, errorMessage.size(), &errLen, (char*)errorMessage.data());
    RB_ASSERT_MSG(false, errorMessage);

}