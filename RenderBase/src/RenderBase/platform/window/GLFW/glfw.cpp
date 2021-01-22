
#include <RenderBase/platform/window/GLFW/glfw.h>
#ifdef PLATFORM_WINDOW_GLFW

#include <RenderBase/platform/graphics/OpenGL/GLGraphicsContext.h>
#include <RenderBase/tools/logging.h>

using namespace std;
using namespace rb::platform::glfw;

// #########################################################################
// Internal module function
// #########################################################################

static uint8_t static_GLFWWindowCount = 0;

static void GLFWErrorCallback(int error, const char* description) {
    RB_DEBUG_F("GLFW Error (%d): %s\n", error, description);
}

// #########################################################################
// Window implementation
// #########################################################################

Window::Window(const string &title, uint32_t width, uint32_t height) {

    if (static_GLFWWindowCount == 0) {
        // init glfw - this should be done only once, but this class could be created multiple times.
        auto success = glfwInit();
        RB_ASSERT(success, "Failed to initialize GLFW window library");
        glfwSetErrorCallback(GLFWErrorCallback);
        #if defined DEBUG and defined PLATFORM_GRAPHICS_OPENGL
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
        #endif
    }

    windowHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    ++static_GLFWWindowCount;

    // this is used to be able to access m_data in glfw callbacks: https://discourse.glfw.org/t/what-is-a-possible-use-of-glfwgetwindowuserpointer/1294/2
    // uncomment if needed:
    // glfwSetWindowUserPointer(m_Window, &m_Data);
    // SetVSync(true);

    // opengl only:

    // create graphics context for the window
    glfwMakeContextCurrent(windowHandle);
    graphics = make_unique<GLGraphicsContext>(glfwGetProcAddress);



}

string Window::getTitle() const {
    return "";
}

int Window::showVirtual() {
    while (!glfwWindowShouldClose(windowHandle)) {
        drawCallback();
        glfwSwapBuffers(windowHandle);
        glfwPollEvents();
    }
    glfwDestroyWindow(windowHandle);
    return 0;
}

void Window::onEventVirtual(const eventCallback_t& callback) {
    eventCallback = callback;
}

void Window::onDrawVirtual(const drawCallback_t& callback) {
    drawCallback = callback;
}

void Window::close() {
    open = false;
}

uint32_t Window::getWidth() const {
    return 0;
}

uint32_t Window::getHeight() const {
    return 0;
}

// #########################################################################
// GLFWPerformenceAnalyzer implementation
// #########################################################################

#endif