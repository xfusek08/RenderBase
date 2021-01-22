#pragma once

#include <RenderBase/graphics/GraphicsContext.h>
#include <glad/glad.h>

namespace rb {
    namespace opengl {

        class GraphicsContext : public rb::GraphicsContext
        {
            public:
                GraphicsContext(void* GLProcTable);
        };

    }
}
