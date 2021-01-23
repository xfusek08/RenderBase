#pragma once

#include <RenderBase/graphics/GraphicsContext.h>
#include <glad/glad.h>

namespace rb {
    namespace opengl {

        class GLGraphicsContext : public rb::GraphicsContext
        {
            public:
                GLGraphicsContext(void* GLProcTable);

                void cleanColor(glm::vec3 color) override;
        };

    }
}
