
#include <RenderBase/core/graphics/Buffer.h>

using namespace rb;

Buffer::Buffer(GLenum type, GLenum usage) : type(type), usage(usage) {
    glGenBuffers(1, &glId);
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &glId);
}

void Buffer::bind() {
    glBindBuffer(type, glId);
}

void Buffer::unBind() {
    glBindBuffer(type, 0);
}

void Buffer::load(size_t size, void *data) {
    bind();
    glBufferData(type, size, data, usage);
    // todo handle errors
    unBind();
}
