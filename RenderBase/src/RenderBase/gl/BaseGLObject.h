#pragma once

#include <string>
#include <glad/glad.h>

namespace rb::gl {
    class BaseGLObject {
        public:
            inline GLuint getGlID() const { return glId; }
            void failWithErrorMessage();

        protected:
            GLuint glId = 0;
    };
}