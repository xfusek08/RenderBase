
#include <RenderBase/gl/VertexArray.h>
#include <RenderBase/gl/Buffer.h>

using namespace rb::gl;

VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &glId);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &glId);
}

void VertexArray::addAttrib(
    const Buffer&     buffer,
    GLuint            index,
    GLint             nofComponents,
    GLenum            type,
    GLsizei           stride,
    GLintptr          offset,
    GLboolean         normalized,
    GLuint            divisor,
    AttribPointerType attribPointerType
) {
    removeAttrib(index);
    
    if (type == GL_UNSIGNED_INT || type == GL_INT) {
        attribPointerType = VertexArray::AttribPointerType::I;
    }
    
    if (stride == 0) {
        stride = getTypeSize(type) * nofComponents;
    } else {
        stride *= getTypeSize(type); // stride by components
    }
    
    glVertexArrayAttribBinding(glId, index, index);
    glEnableVertexArrayAttrib(glId, index);

    if (attribPointerType == VertexArray::AttribPointerType::NONE) {
        glVertexArrayAttribFormat(glId, index, nofComponents, type, normalized, 0);
    } else if (attribPointerType == VertexArray::AttribPointerType::I) {
        glVertexArrayAttribIFormat(glId, index, nofComponents, type, 0);
    } else if (attribPointerType == VertexArray::AttribPointerType::L) {
        glVertexArrayAttribLFormat(glId, index, nofComponents, type,0);
    }
    
    glVertexArrayVertexBuffer(glId, index, buffer.getGlID(), offset, stride);
    glVertexArrayBindingDivisor(glId, index, divisor);
}

void VertexArray::removeAttrib(GLuint index)
{
    glVertexArrayVertexBuffer(glId, index, 0, 0, 0);
}

void VertexArray::bind() const
{
    glBindVertexArray(glId);
}

void rb::gl::VertexArray::addElementBuffer(const Buffer& buffer)
{
    glVertexArrayElementBuffer(glId, buffer.getGlID());
}
