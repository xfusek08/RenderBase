
#include <RenderBase/core/window.h>

using namespace std;
using namespace rb;
using namespace std::chrono;

int Window::show() {
    resetFrameCounter();
    return showVirtual();
}

void Window::onEvent(const eventCallback_t& callback) {
    onEventVirtual(callback);
}

void Window::onDraw(const drawCallback_t& callback) {
    onDrawVirtual([this, callback]() {
        auto frameStat = this->frame();

        callback();

        if (frameStat.isFinished && this->callbackFPSCount != nullptr) {
            this->callbackFPSCount(frameStat);
        }
    });
}

void Window::onFPSCount(const fpsCountCallback_t& callback) {
    callbackFPSCount = callback;
}

void Window::resetFrameCounter() {
    actFrameStat.frames = 0;
    actFrameStat.isFinished = false;
    actFrameStat.duration = 0ms;
    actFrameStat.startTime = high_resolution_clock::now();
}

FrameStat Window::frame() {
    auto now = high_resolution_clock::now();
    if (actFrameStat.isFinished) {
        resetFrameCounter();
    }

    actFrameStat.frames++;
    actFrameStat.duration += duration_cast<microseconds>(now - actFrameStat.startTime);

    actFrameStat.startTime  = now;
    actFrameStat.isFinished = actFrameStat.duration >= 1s;

    return actFrameStat;
}
