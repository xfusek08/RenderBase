#pragma once

#include <memory>
#include <functional>

#include <RenderBase/core/event.h>
#include <RenderBase/core/performance.h>

namespace rb {

    using eventCallback_t = std::function<bool(const Event&)>;
    using drawCallback_t  = std::function<void()>;

    class Window
    {
        public:
            void onEvent(const eventCallback_t& callback);
            void onDraw(const drawCallback_t& callback);

            void setPerformanceAnalyzer(std::shared_ptr<PerformanceAnalyzer> analyzer) { this->analyzer = analyzer; }
            inline std::shared_ptr<PerformanceAnalyzer> getPerformanceAnalyzer() const { return analyzer; }

            int  show();

            virtual void close() = 0;
            virtual std::string getTitle()  const = 0;
            virtual uint32_t    getWidth()  const = 0;
            virtual uint32_t    getHeight() const = 0;

        protected:
            std::shared_ptr<PerformanceAnalyzer> analyzer = nullptr;

            virtual int  showVirtual() = 0;
            virtual void onEventVirtual(const eventCallback_t& callback) = 0;
            virtual void onDrawVirtual(const drawCallback_t& callback) = 0;
    };
}
