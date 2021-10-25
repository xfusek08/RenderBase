#pragma once

#include <RenderBase/defines.h>
#include <RenderBase/gl/BaseGLObject.h>

#include <glm/glm.hpp>

namespace rb::gl {
    class Texture3D : public BaseGLObject
    {
        public:
            Texture3D(uint32 width, uint32 height, uint32 depth);
            ~Texture3D();
            void loadData(GLenum format, GLenum type, void *data);
        private:
            uint32 width;
            uint32 height;
            uint32 depth;
    };
}
