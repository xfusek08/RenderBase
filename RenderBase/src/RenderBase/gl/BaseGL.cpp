
#include <vector>

#include <RenderBase/logging.h>
#include <RenderBase/asserts.h>

#include <RenderBase/gl/BaseGL.h>

#ifndef NO_ASSERT
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
#endif

/**
 * @brief detetermines if flags are mutable
 *
 * @param flags flags
 *
 * @return true if flags are combination of GL_{STATIC|STREAM|DYNAMIC}_{DRAW_COPY_READ}
 */
bool rb::gl::areBufferFlagsMutable(GLbitfield flags){
  return flags == GL_STATIC_DRAW
      || flags == GL_STATIC_COPY
      || flags == GL_STATIC_READ
      || flags == GL_STREAM_DRAW
      || flags == GL_STREAM_COPY
      || flags == GL_STREAM_READ
      || flags == GL_DYNAMIC_DRAW
      || flags == GL_DYNAMIC_COPY
      || flags == GL_DYNAMIC_READ;
}
