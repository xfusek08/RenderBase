
// #include <RenderBase/platform/graphics/OpenGL/BaseGLObject.h>

// using namespace rb::opengl;

// Buffer::Buffer(GLenum type, GLenum usage) : type(type), usage(usage) {
//     glGenBuffers(1, &id);
// }

// Buffer::~Buffer() {
//     glDeleteBuffers(1, &id);
// }

// void Buffer::bind() {
//     glBindBuffer(type, id);
// }

// void Buffer::unBind() {
//     glBindBuffer(type, 0);
// }

// void Buffer::load(size_t size, void *data) {
//     bind();
//     glBufferData(type, size, data, usage);
//     // todo handle errors
//     unBind();
// }
