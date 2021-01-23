#include <stdexcept>

#include <RenderBase/platform/graphics/OpenGL/GLGraphicsContext.h>
#include <RenderBase/tools/logging.h>

using namespace rb::opengl;
using namespace glm;

// #ifdef DEBUG
//     static void glDebugMessage(
//         GLenum        source,
//         GLenum        type,
//         GLuint        /*id*/,
//         GLenum        severity,
//         GLsizei       /*length*/,
//         const GLchar *message,
//         void*         /*userParam*/
//     ) {
//         RB_DEBUG(message);
//     }
// #endif

GLGraphicsContext::GLGraphicsContext(void* GLProcTable) : rb::GraphicsContext() {

    // init glad
    if (!gladLoadGLLoader((GLADloadproc)GLProcTable)) {
        RB_ASSERT(false, "Failed to initialize GLAD");
        throw std::runtime_error("Failed to initialize graphics");
    }

    RB_DEBUG("GLAD successfully initialized");

    // // todo abstract with graphics API
    // #ifdef DEBUG
    //     // init gl error callback
    //     glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    //     glDebugMessageCallback((GLDEBUGPROC)glDebugMessage, nullptr);
    // #endif
}

void GLGraphicsContext::cleanColor(vec3 color) {
    glClearColor(color.x, color.y, color.z, 1);
}
