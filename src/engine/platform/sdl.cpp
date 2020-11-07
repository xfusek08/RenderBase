
#include <engine/platform/sdl.h>

#include <engine/event.h>

using namespace std;
using namespace engine::platform::sdl;

// #########################################################################
// Helper functions
// #########################################################################
void parseEvent(const SDL_Event &sdlEvent, engine::Event *event) {
    // transform sdl event to engine event
}

tuple<int, int> getScreenSize() {
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    return {DM.w, DM.h};
}

// #########################################################################
// SDLWindow implementation
// #########################################################################

SDLWindow::SDLWindow(const string &title, uint32_t width, uint32_t height) {
    SDL_Init(SDL_INIT_EVERYTHING);

    // create window in the centre of the screen
    auto [screenW, screenH] = getScreenSize();
    sdlWindow = SDL_CreateWindow(
        title.c_str(),
        screenW / 2 - width / 2,
        screenH / 2 - height / 2,
        width,
        height,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
    );

    // init opengl context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    sdlGlContext = SDL_GL_CreateContext(sdlWindow);
}

string SDLWindow::getTitle() const {
    return SDL_GetWindowTitle(sdlWindow);
}

int SDLWindow::showVirtual() {
    // run main loop
    bool open = true;

    while (open) {
        SDL_Event sdlEvent;
        if (SDL_PollEvent(&sdlEvent)) {
            if (sdlEvent.type == SDL_QUIT) {
                open = false;
            }
            auto event = Event();
            parseEvent(sdlEvent, &event);
            eventCallback(event);
        }
        drawCallback();
        SDL_GL_SwapWindow(sdlWindow);
    }

    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
    return 0;
}

void SDLWindow::onEventVirtual(const eventCallback_t& callback) {
    eventCallback = callback;
}

void SDLWindow::onDrawVirtual(const drawCallback_t& callback) {
    drawCallback = callback;
}
