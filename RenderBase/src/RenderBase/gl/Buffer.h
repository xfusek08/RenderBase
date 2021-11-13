#pragma once

#include <RenderBase/defines.h>
#include <RenderBase/gl/BaseGL.h>

#include <glm/glm.hpp>

#include <vector>

namespace rb::gl {
    class Buffer : public BaseGLObject
    {
        public:
            Buffer(uint32 size, GLvoid const* data  = nullptr, GLbitfield flags = GL_STATIC_DRAW);
            
            template <typename T>
            Buffer(const std::vector<T>& data, GLbitfield flags = GL_STATIC_DRAW) :
                Buffer(sizeof(T) * data.size(), data.data(), flags) {}
            
            ~Buffer();
            
            void newBufferData(uint32 size, GLvoid const* data  = nullptr, GLbitfield flags = GL_STATIC_DRAW);
            
            void bind(GLenum target) const;
            void bindBase(GLenum target, GLuint index) const;
            
            void updateSubData(GLvoid const *data, GLsizeiptr size = 0, GLintptr offset = 0) const;
            
            void setData(GLvoid const *data, GLsizeiptr size = 0);
            
            template<typename T>
            void setData(const std::vector<T>& data)
            {
                setData(data.data(), sizeof(T) * data.size());
            }
            
            GLsizeiptr getSize() const;
            
            GLbitfield getFlags() const;
    };
}
