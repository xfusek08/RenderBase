#pragma once

#include <string>
#include <glm/glm.hpp>
#include <RenderBase/platform/platformGraphics.h>

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
