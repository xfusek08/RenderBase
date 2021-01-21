
#include <RenderBase/platform/glfw3.h>

#include <RenderBase/event.h>

using namespace std;
using namespace rb::platform::glfw3;

// #########################################################################
// GLFWWindow implementation
// #########################################################################

GLFWWindow::GLFWWindow(const string &title, uint32_t width, uint32_t height) {

}

string GLFWWindow::getTitle() const {
    return "";
}

int GLFWWindow::showVirtual() {
    return 0;
}

void GLFWWindow::onEventVirtual(const eventCallback_t& callback) {
    eventCallback = callback;
}

void GLFWWindow::onDrawVirtual(const drawCallback_t& callback) {
    drawCallback = callback;
}

void GLFWWindow::close() {
    open = false;
}

uint32_t GLFWWindow::getWidth() const {
    return 0;
}

uint32_t GLFWWindow::getHeight() const {
    return 0;
}

// #########################################################################
// GLFWPerformenceAnalyzer implementation
// #########################################################################
