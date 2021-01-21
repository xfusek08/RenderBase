
#include <RenderBase/platform/window/GLFW/glfw.h>
#ifdef PLATFORM_WINDOW_GLFW

using namespace std;
using namespace rb::platform::glfw;

// #########################################################################
// Window implementation
// #########################################################################

Window::Window(const string &title, uint32_t width, uint32_t height) {

}

string Window::getTitle() const {
    return "";
}

int Window::showVirtual() {
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