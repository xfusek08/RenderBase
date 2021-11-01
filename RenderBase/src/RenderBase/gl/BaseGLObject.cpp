
#include <vector>

#include <RenderBase/logging.h>
#include <RenderBase/asserts.h>

#include <RenderBase/gl/BaseGLObject.h>

void rb::gl::BaseGLObject::assertGlErrors()
{
    std::vector<GLenum> errs;
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR) {
        RB_FATAL("Openg GL error: " << err);
        errs.push_back(err);
    }
    
    RB_ASSERT_MSG(errs.empty(), "There were " << errs.size() << " errors in OpenGL");
}
