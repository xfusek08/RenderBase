#pragma once

#include <glad/glad.h>

namespace rb::gl {
    
    class BaseGLObject {
        public:
            inline GLuint getGlID() const { return glId; }
        protected:
            GLuint glId = 0;
            
            #ifndef NO_ASSERT
                void assertGlErrors();
            #endif
    };
    
    bool areBufferFlagsMutable(GLbitfield flags);
    
    unsigned getTypeSize(GLenum type);
}

#ifndef NO_ASSERT
    #define ASSERT_GL_ERRORS(...) assertGlErrors()
#else
    #define ASSERT_GL_ERRORS(...)
#endif
