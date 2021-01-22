#pragma once

#include <memory>
#include <string>

#include <RenderBase/graphics/GraphicsObject.h>

namespace rb {

    enum class ShaderType {
        Unknown,
        Vertex,
        Fragment
    };

    class Shader : public GraphicsObject
    {
        public:
            static std::shared_ptr<Shader> create(ShaderType type, std::string source);

            inline ShaderType getType() const { return type; }

        protected:
            ShaderType type = ShaderType::Unknown;
    };
}
