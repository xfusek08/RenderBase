#pragma once

#include <glm/glm.hpp>

namespace rb {

    class GraphicsContext {
        public:
            virtual void cleanColor(glm::vec3 color) = 0;
    };

}
