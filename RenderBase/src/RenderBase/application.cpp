#ifdef DEBUG
    // uncomment for verbose gl debug info
    // #define LOG_GL_DEBUG
#endif

#include <RenderBase/application.h>
#include <RenderBase/logging.h>
#include <RenderBase/asserts.h>
#include <glad/glad.h>

using namespace std;
using namespace rb;
using namespace rb::app;

#ifdef LOG_GL_DEBUG
    void GLDdebugCallback(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar *message,
        const void *userParam
    ) {
        RB_DEBUG(
            "OpenGL debug info: \n"
            "Source:   " << source << "\n" <<
            "type:     " << type << "\n" <<
            "id:       " << id << "\n" <<
            "severity: " << severity << "\n" <<
            "message:\n" << message
        );
    }
#endif


Configuration rb::app::loadDefaultConfigFromArguments(int argCount, char** arguments)
{
    // TODO parse command line arguments using arumet parser module.
    return Configuration(); // use default values for now
}

// BasicOpenGLApplication implementation
// -------------------------------------

BasicOpenGLApplication::BasicOpenGLApplication(Configuration config)
{
    config = config;
}

bool BasicOpenGLApplication::run()
{
    status = Status::Uninitialized;
    
    RB_DEBUG("Application is initializing ... ");
    
    // Event dispatcher Sub-System
    // ----------------------------
    eventDispatcher = make_unique<events::EventDispatcher>();
    eventDispatcher->subscribeToEvent(events::EVENT_CODE_APPLICATION_QUIT, this, [&](events::Event) {
        // close
        status = Status::Exited;
        return true;
    });
    eventDispatcher->subscribeToEvent(events::EVENT_CODE_RESIZED, this, [this](events::Event event) {
        // resize
        return onResize(event.data.u16[0], event.data.u16[1]);
    });


    // Windowing Sub-System
    // ---------------------
    auto windowConfig   = window::Config();
    windowConfig.width  = config.windowWidth;
    windowConfig.height = config.windowHeight;
    window = make_unique<window::Window>(windowConfig, *eventDispatcher);
    window->show(); // opengl context is initiated now
    #ifdef LOG_GL_DEBUG // prepare opengl debugging
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(GLDdebugCallback, nullptr);
    #endif

    
    // Input Sub-System
    // -------------
    inputHandler = make_unique<input::InputHandler>(*window, *eventDispatcher);
    inputHandler->setInputChangeCallback(bind(&BasicOpenGLApplication::onInputChangeInternal, this, placeholders::_1));


    // Timer ticking Sub-System
    // -------------------------
    timer = make_unique<timing::Timer>();
    timer->setOnTickCallback(bind(&BasicOpenGLApplication::onTickInternal, this, placeholders::_1));
        
    
    // GUI Sub-System
    // --------------
    gui = make_unique<gui::Gui>(*window);
    
    
    // User initiation
    // ---------------
    if (!init()) {
        RB_ERROR("User initialization failed.");
        return false;
    }
    
    // Main app loop (single-threaded for now)
    // ---------------------------------------
    status = Status::Running;
    while (status == Status::Running) {
        // state modification
        
        // fire input events
        window->fireEvents();
        
        // fire regular tick events
        timer->checkTick();
        
        // // GUI update and react to its changes
        // gui->update(inputHandler->getCurrentState(), timer->getCurrentTimeStep());
        // if (gui->isStateDirty()) {
        //     onGuiChangedInternal(gui->getState());
        //     gui->cleanState();
        // }
        
        // state is fixed
        draw();
        // gui->draw();
        window->swapFrames();
    }
    
    // User define finalization steps
    // -------------------------------
    if (!finalize()) {
        RB_ERROR("User initialization failed.");
        return false;
    }
    
    return true;
}

bool BasicOpenGLApplication::onInputChangeInternal(const input::InputState& inputState)
{
    return onInputChange(inputState, timer->getCurrentTimeStep());
}

bool BasicOpenGLApplication::onTickInternal(const timing::TimeStep& tick)
{
    inputHandler->onTick(tick);
    return onTick(inputHandler->getCurrentState(), tick);
}

bool BasicOpenGLApplication::onGuiChangedInternal(const gui::GuiState& guiState)
{
    return onGuiChanged(guiState);
}

void BasicOpenGLApplication::exit() {
    status = Status::Exited;
}
