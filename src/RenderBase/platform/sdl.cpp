
#include <RenderBase/platform/sdl.h>

#include <RenderBase/core/event.h>

using namespace std;
using namespace rb::platform::sdl;

// #########################################################################
// Helper functions
// #########################################################################

tuple<int, int> getScreenSize() {
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    return {DM.w, DM.h};
}

rb::MouseButtons mouseButtonsFromSdlState(uint32_t state) {
    return rb::MouseButtons{
        bool(state & SDL_BUTTON(SDL_BUTTON_LEFT)),
        bool(state & SDL_BUTTON(SDL_BUTTON_RIGHT)),
        bool(state & SDL_BUTTON(SDL_BUTTON_MIDDLE)),
    };
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
            rb::Event event;
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

uint32_t SDLWindow::getWidth() const {
    int w,h;
    SDL_GetWindowSize(this->sdlWindow, &w, &h);
    return w;
}

uint32_t SDLWindow::getHeight() const {
    int w,h;
    SDL_GetWindowSize(this->sdlWindow, &w, &h);
    return h;
}

void SDLWindow::parseEvent(const SDL_Event &sdlEvent, rb::Event *event) {
    auto w = float(getWidth());
    auto h = float(getHeight());

    switch (sdlEvent.type)
    {
        case SDL_MOUSEMOTION: {
            event->mouseMoveData = {
                EventType::MouseMove,
                float(sdlEvent.motion.x)    / w,
                float(sdlEvent.motion.y)    / h,
                float(sdlEvent.motion.xrel) / w,
                float(sdlEvent.motion.yrel) / h,
                mouseButtonsFromSdlState(sdlEvent.motion.state),
            };
        } break;

        case SDL_MOUSEWHEEL: {
            event->mouseWheelData = {
                EventType::MouseWheel,
                float(sdlEvent.wheel.y),
            };
        } break;

        default: {
            event->type = EventType::Unknown;
        } break;
    }
}

// #########################################################################
// SDLPerformenceAnalyzer implementation
// #########################################################################

void SDLPerformenceAnalyzer::delay(chrono::microseconds usDelay) {
    SDL_Delay(chrono::duration_cast<chrono::microseconds>(usDelay).count() / 1000);
}
