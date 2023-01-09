#pragma once

#include <RenderBase/core/Window.h>
#include <SDL2/include/SDL.h>

namespace rb {
    namespace platform {
        namespace sdl {

            class SDLWindow : public rb::Window
            {
                public:
                    SDLWindow(const std::string &title, uint32_t width, uint32_t height);

                    std::string getTitle()  const override;
                    uint32_t    getWidth()  const override;
                    uint32_t    getHeight() const override;

                    void  close() override;

                protected:
                    rb::eventCallback_t eventCallback = nullptr;
                    rb::drawCallback_t  drawCallback  = nullptr;
                    SDL_Window*         sdlWindow     = nullptr;
                    SDL_GLContext       sdlGlContext  = nullptr;
                    bool                open = false;

                    int  showVirtual() override;
                    void onEventVirtual(const rb::eventCallback_t& callback) override;
                    void onDrawVirtual(const rb::drawCallback_t& callback) override;
                    void parseEvent(const SDL_Event &sdlEvent, rb::Event *event);
            };

            class SDLPerformenceAnalyzer : public PerformenceAnalyzer
            {
                public:
                    using PerformenceAnalyzer::PerformenceAnalyzer;
            };

        }
    }
}