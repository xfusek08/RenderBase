#pragma once

#include <RenderBase/core/graphics/GraphicsBaseObject.h>

namespace rb {

    /**
     * see: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBufferData.xhtml
     */
    class Buffer : public GraphicsBaseObject
    {
        public:

            /**
             * @brief Generic OpenGLBuffer Wrapper
             *
             * @param type
             *   * GL_ARRAY_BUFFER
             *   * GL_ATOMIC_COUNTER_BUFFER
             *   * GL_COPY_READ_BUFFER
             *   * GL_COPY_WRITE_BUFFER
             *   * GL_DISPATCH_INDIRECT_BUFFER
             *   * GL_DRAW_INDIRECT_BUFFER
             *   * GL_ELEMENT_ARRAY_BUFFER
             *   * GL_PIXEL_PACK_BUFFER
             *   * GL_PIXEL_UNPACK_BUFFER
             *   * GL_QUERY_BUFFER
             *   * GL_SHADER_STORAGE_BUFFER
             *   * GL_TEXTURE_BUFFER
             *   * GL_TRANSFORM_FEEDBACK_BUFFER
             *   * GL_UNIFORM_BUFFER
             *
             * @param usage
             *   * GL_STREAM_DRAW
             *   * GL_STREAM_READ
             *   * GL_STREAM_COPY
             *   * GL_STATIC_DRAW
             *   * GL_STATIC_READ
             *   * GL_STATIC_COPY
             *   * GL_DYNAMIC_DRAW
             *   * GL_DYNAMIC_READ
             *   * GL_DYNAMIC_COPY
             *
             *   see: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBufferData.xhtml
             */
            Buffer(GLenum type = GL_ARRAY_BUFFER, GLenum usage = GL_DYNAMIC_DRAW);

            ~Buffer();

            void bind();
            void unBind();

            // void *mapData();
            // void *umapData();

            template<typename T>
            inline void load(std::vector<T>& data) { load(sizeof(T) * data.size(), data.data()); }

            void load(size_t size, void *data);

        protected:
            GLenum type;
            GLenum usage;
    };

    class UniformBuffer : public Buffer
    {
        public:
            UniformBuffer(GLenum usage = GL_STATIC_DRAW) :
                Buffer(GL_UNIFORM_BUFFER, usage) {}
    };
}

// // ho to create buffer object in opengl:
// GLuint ubo = 0;
// glGenBuffers(1, &ubo);
// glBindBuffer(GL_UNIFORM_BUFFER, ubo);
// glBufferData(GL_UNIFORM_BUFFER, sizeof(shader_data), &shader_data, GL_DYNAMIC_DRAW);
// glBindBuffer(GL_UNIFORM_BUFFER, 0);


// glBindBuffer(GL_UNIFORM_BUFFER, gbo);
// GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
// memcpy(p, &shader_data, sizeof(shader_data))
// glUnmapBuffer(GL_UNIFORM_BUFFER);