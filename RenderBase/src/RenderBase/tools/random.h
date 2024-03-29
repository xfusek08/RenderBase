
#pragma once

#include <RenderBase/defines.h>

#include <glm/glm.hpp>

// #include <cfloat>

namespace rb::random {
    float32 randomFloat(float32 min = FLT_MIN, float32 max = FLT_MIN);

    inline glm::vec3 randomVec3(glm::vec3 min, glm::vec3 max)
    {
        return {
            randomFloat(min.x, max.x),
            randomFloat(min.y, max.y),
            randomFloat(min.z, max.z)
        };
    }
}