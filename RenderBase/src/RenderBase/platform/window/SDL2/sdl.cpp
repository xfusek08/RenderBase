
#include <RenderBase/platform/window/SDL2/sdl.h>
#ifdef PLATFORM_WINDOW_SDL

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
// Window implementation
// #########################################################################

Window::Window(const string &title, uint32_t width, uint32_t height) {
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

string Window::getTitle() const {
    return SDL_GetWindowTitle(sdlWindow);
}

int Window::showVirtual() {
    // run main loop
    open = true;

    while (open) {
        SDL_Event sdlEvent;
        if (SDL_PollEvent(&sdlEvent)) {
            if (sdlEvent.type == SDL_QUIT) {
                open = false;
            }
            rb::Event event = {};
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

void Window::onEventVirtual(const eventCallback_t& callback) {
    eventCallback = callback;
}

void Window::onDrawVirtual(const drawCallback_t& callback) {
    drawCallback = callback;
}

void Window::close() {
    open = false;
}

uint32_t Window::getWidth() const {
    int w,h;
    SDL_GetWindowSize(this->sdlWindow, &w, &h);
    return w;
}

uint32_t Window::getHeight() const {
    int w,h;
    SDL_GetWindowSize(this->sdlWindow, &w, &h);
    return h;
}

void Window::parseEvent(const SDL_Event &sdlEvent, rb::Event *event) {
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

        case SDL_KEYDOWN: {
            event->keyPressedData = {
                EventType::KeyPressed,
                sdlEvent.key.keysym.sym
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

#endif
