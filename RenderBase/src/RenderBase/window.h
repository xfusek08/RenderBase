#pragma once

#include <memory>
#include <functional>

#include <RenderBase/event.h>
#include <RenderBase/performance.h>
#include <RenderBase/graphics/GraphicsContext.h>

namespace rb {

    using eventCallback_t = std::function<bool(const Event&)>;
    using drawCallback_t  = std::function<void()>;

    class Window
    {
        public:
            void onEvent(const eventCallback_t& callback);
            void onDraw(const drawCallback_t& callback);

            inline std::shared_ptr<PerformenceAnalyzer> getPerformanceAnalyzer() const { return analyzer; }
            inline std::shared_ptr<GraphicsContext>     getGraphicsContext()     const { return graphics; }

            void setPerformanceAnalyzer(std::shared_ptr<PerformenceAnalyzer> analyzer) { this->analyzer = analyzer; }

            int show();

            virtual void        close() = 0;
            virtual std::string getTitle()  const = 0;
            virtual uint32_t    getWidth()  const = 0;
            virtual uint32_t    getHeight() const = 0;

        protected:
            std::shared_ptr<PerformenceAnalyzer> analyzer = nullptr;
            std::shared_ptr<GraphicsContext>     graphics = nullptr;

            virtual int  showVirtual() = 0;
            virtual void onEventVirtual(const eventCallback_t& callback) = 0;
            virtual void onDrawVirtual(const drawCallback_t& callback) = 0;
    };
}
