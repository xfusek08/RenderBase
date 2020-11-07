#pragma once

#include <memory>
#include <functional>
#include <chrono>

namespace rb {

    class Event;

    struct FrameStat
    {
        std::chrono::steady_clock::time_point startTime;
        std::chrono::microseconds duration;
        uint32_t frames = 0;
        bool isFinished  = false;
    };

    using eventCallback_t    = std::function<bool(const Event&)>;
    using drawCallback_t     = std::function<void()>;
    using fpsCountCallback_t = std::function<void(FrameStat)>;

    class Window
    {
        public:
            void onEvent(const eventCallback_t& callback);
            void onDraw(const drawCallback_t& callback);
            void onFPSCount(const fpsCountCallback_t& callback);
            int  show();

            virtual std::string getTitle() const = 0;

        protected:
            virtual int  showVirtual() = 0;
            virtual void onEventVirtual(const eventCallback_t& callback) = 0;
            virtual void onDrawVirtual(const drawCallback_t& callback) = 0;

            FrameStat frame();
            void      resetFrameCounter();

            fpsCountCallback_t callbackFPSCount = nullptr;
            FrameStat actFrameStat = {};
    };
}
