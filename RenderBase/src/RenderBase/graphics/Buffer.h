#pragma once

#include <vector>
#include <memory>

#include <RenderBase/FailableObject.h>

namespace rb {

    class Buffer : public FailableObject
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