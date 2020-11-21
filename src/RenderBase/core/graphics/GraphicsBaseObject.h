#pragma once

#include <RenderBase/platform/platform.h>

#include <glm/glm.hpp>

#include <string>

namespace rb {

    class GraphicsBaseObject {
        public:
            inline       GLuint        getGlId()         const { return glId; }
            inline const std::string&  getErrorMessage() const { return errorMessage; }
        protected:
            GLuint glId = 0;
            std::string errorMessage = "";
    };

}
