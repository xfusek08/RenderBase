#pragma once

#include <string>
#include <glad/glad.h>

namespace rb {
    namespace opengl {

        class BaseGLObject {
            public:
                inline GLuint getGlID() const { return glId; }

            protected:
                GLuint glId = 0;
                std::string errorMessage = "";
        };

    }
}
