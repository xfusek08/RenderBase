#pragma once

#include <RenderBase/defines.h>
#include <RenderBase/gl/BaseGL.h>

namespace rb::gl {
    
    class Buffer;
    
    class VertexArray : public BaseGLObject
    {
        public:
            enum AttribPointerType { NONE, I, L };
            
            VertexArray();
            ~VertexArray();
            
            void addAttrib(
                const Buffer&     buffer,
                GLuint            index,
                GLint             nofComponents,
                GLenum            type,
                GLsizei           stride            = 0,
                GLintptr          offset            = 0,
                GLboolean         normalized        = GL_FALSE,
                GLuint            divisor           = 0,
                AttribPointerType attribPointerType = NONE
            );
            
            void removeAttrib(GLuint index);
            
            void bind() const;
            
            void addElementBuffer(const Buffer& buffer);
    };
}
