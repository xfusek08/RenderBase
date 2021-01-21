#pragma once

#include <RenderBase/platform/platformWindow.h>
#ifdef PLATFORM_WINDOW_GLFW

namespace rb {
    namespace platform {
        namespace glfw {

            class GLFWWindow : public rb::Window
            {
                public:
                    GLFWWindow(const std::string &title, uint32_t width, uint32_t height);

                    std::string getTitle()  const override;
                    uint32_t    getWidth()  const override;
                    uint32_t    getHeight() const override;

                    void  close() override;

                protected:
                    rb::eventCallback_t eventCallback = nullptr;
                    rb::drawCallback_t  drawCallback  = nullptr;
                    bool                open = false;

                    int  showVirtual() override;
                    void onEventVirtual(const rb::eventCallback_t& callback) override;
                    void onDrawVirtual(const rb::drawCallback_t& callback) override;
            };

            class GLFWPerformenceAnalyzer : public PerformenceAnalyzer
            {
                public:
                    using PerformenceAnalyzer::PerformenceAnalyzer;
            };

        }
    }
}

#endif
