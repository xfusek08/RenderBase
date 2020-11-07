#pragma once

#include <engine/Window.h>
#include <SDL.h>

namespace engine {
    namespace platform {
        namespace sdl {

            class SDLWindow : public engine::Window
            {
                public:
                    SDLWindow(const std::string &title, uint32_t width, uint32_t height);
                    std::string getTitle() const override;
                    int showVirtual() override;

                protected:
                    void onEventVirtual(const engine::eventCallback_t& callback) override;
                    void onDrawVirtual(const engine::drawCallback_t& callback) override;

                    engine::eventCallback_t eventCallback = nullptr;
                    engine::drawCallback_t  drawCallback  = nullptr;
                    SDL_Window*             sdlWindow     = nullptr;
                    SDL_GLContext           sdlGlContext  = nullptr;
            };

        }
    }
}