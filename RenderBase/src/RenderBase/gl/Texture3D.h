#pragma once

#include <RenderBase/defines.h>
#include <RenderBase/gl/BaseGL.h>

#include <glm/glm.hpp>

namespace rb::gl {
    class Texture3D : public BaseGLObject
    {
        public:
            Texture3D();
            ~Texture3D();
    };
}
