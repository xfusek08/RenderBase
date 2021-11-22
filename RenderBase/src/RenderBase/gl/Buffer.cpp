/**
 * This file was inspired by implementation of Buffer object from
 * open-sourcelibrary geGL: https://github.com/dormon/geGL
 */
#include <RenderBase/gl/Buffer.h>

#include <RenderBase/logging.h>

using namespace rb::gl;

Buffer::Buffer(uint32 size, GLvoid const* data, GLbitfield flags)
{
    glCreateBuffers(1, &glId);
    RB_INFO("Buffer " << glId << " created.");
    newBufferData(size, data, flags);
}

Buffer::~Buffer()
{
    RB_INFO("Deleting buffer " << glId << " ...");
    glDeleteBuffers(1, &glId);
    RB_INFO("Buffer " << glId << " deleted.");
}

void Buffer::newBufferData(uint32 size, GLvoid const* data, GLbitfield flags)
{
    if (areBufferFlagsMutable(flags)) {
        glNamedBufferData(glId, size, data, flags);
    } else {
        glNamedBufferStorage(glId, size, data, flags);
    }
}

void Buffer::bind(GLenum target) const
{
    glBindBuffer(target, glId);
}
            
void Buffer::bindBase(GLenum target, GLuint index) const
{
    glBindBufferBase(target, index, glId);
}

void Buffer::updateSubData(const GLvoid* data, GLsizeiptr size, GLintptr offset) const
{
    const auto bufferSize = getSize();
    if (size == 0 || size + offset > bufferSize) {
        // No size means copy everything from data from offset which can fit into the bufffer
        // Or if size exceeding buffer size then copy only what can be fitted into the buffer
        size = bufferSize - offset;
    }
    glNamedBufferSubData(glId, offset, size, data);
}

void Buffer::setData(const GLvoid* data, GLsizeiptr size)
{
    const auto bufferSize = getSize();
    if (size > bufferSize) {
        newBufferData(size, data, getFlags());
    } else {
        updateSubData(data, size);
    }
}

GLsizeiptr Buffer::getSize() const
{
    GLsizeiptr sizeVal;
    glGetNamedBufferParameteri64v(glId, GL_BUFFER_SIZE, &sizeVal);
    return sizeVal;
}

GLbitfield Buffer::getFlags() const
{
    GLint flags;
    glGetNamedBufferParameteriv(glId, GL_BUFFER_USAGE, &flags);
    return static_cast<GLenum>(flags);
}

void Buffer::getData(GLvoid* data, GLsizeiptr size, GLintptr offset) const
{
    auto const bufferSize = getSize();
    if (size == 0 || size + offset > bufferSize) {
        size = bufferSize - offset;
    }
    glGetNamedBufferSubData(glId, offset, size, data);
}

void Buffer::resize(GLsizeiptr size)
{
    auto flags = getFlags();
    Buffer temp = Buffer(size, nullptr, flags);
    temp.copyFrom(*this);
    newBufferData(size, nullptr, flags);
    copyFrom(temp);
}

void Buffer::copyFrom(Buffer& dataSourceBuffer)
{
    GLsizeiptr size = glm::min(getSize(), dataSourceBuffer.getSize());
    glCopyNamedBufferSubData(dataSourceBuffer.getGlID(), glId, 0, 0, size);
}
