#include <stdexcept>

#include <RenderBase/tools/logging.h>
#include <RenderBase/graphics/GraphicsContext.h>
#include <RenderBase/platform/platformGraphics.h>

using namespace rb;

#ifdef DEBUG
    void glDebugMessage(
        GLenum        source,
        GLenum        type,
        GLuint        /*id*/,
        GLenum        severity,
        GLsizei       /*length*/,
        const GLchar *message,
        void*         /*userParam*/
    ) {
        LOG_DEBUG(message);
    }
#endif

GraphicsContext::GraphicsContext() {
    if (!platform::loadOpenGlFunctions()) {
        throw std::runtime_error("Failed to initialize graphics");
    }

    // todo abstract with graphics API
    #ifdef DEBUG
        // init gl error callback
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback((GLDEBUGPROC)glDebugMessage, nullptr);
    #endif
}
