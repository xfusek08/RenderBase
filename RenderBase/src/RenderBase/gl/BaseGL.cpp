
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

bool rb::gl::areBufferFlagsMutable(GLbitfield flags)
{
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

unsigned rb::gl::getTypeSize(GLenum type)
{
    switch(type) {
        case GL_BYTE:           return sizeof(GLbyte);
        case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);
        case GL_SHORT:          return sizeof(GLshort);
        case GL_UNSIGNED_SHORT: return sizeof(GLushort);
        case GL_INT:            return sizeof(GLint);
        case GL_UNSIGNED_INT:   return sizeof(GLuint);
        case GL_FLOAT:          return sizeof(GLfloat);
        case GL_HALF_FLOAT:     return sizeof(GLhalf);
        case GL_DOUBLE:         return sizeof(GLdouble);
        default:                return sizeof(GLbyte);
    }
}
