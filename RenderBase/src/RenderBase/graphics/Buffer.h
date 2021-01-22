#pragma once

#include <vector>
#include <memory>

#include <RenderBase/graphics/GraphicsObject.h>

namespace rb {

    class Buffer : public GraphicsObject
    {
        public:
            static std::shared_ptr<Buffer> create();

            void bind();
            void unBind();

            virtual void load(size_t size, void *data) = 0;

            template<typename T>
            inline void load(std::vector<T>& data) { load(sizeof(T) * data.size(), data.data()); }
    };
}