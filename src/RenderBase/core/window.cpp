
#include <RenderBase/core/window.h>

using namespace std;
using namespace rb;
using namespace std::chrono;

int Window::show() {
    return showVirtual();
}

void Window::onEvent(const eventCallback_t& callback) {
    onEventVirtual(callback);
}

void Window::onDraw(const drawCallback_t& callback) {
    onDrawVirtual([this, callback]() {
        callback();
        if (analyzer != nullptr) {
            auto frameStat = this->analyzer->frame();
        }
    });
}
