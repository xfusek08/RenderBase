
#include <RenderBase/application.h>
#include <RenderBase/logging.h>
#include <RenderBase/asserts.h>
#include <glad/glad.h>

using namespace std;
using namespace rb;
using namespace rb::app;

#ifdef DEBUG
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

    // Prepare needed subsystems and event reactions
    // ---------------------------------------------
    
    // Prepare event dispatcher
    eventDispatcher = make_unique<events::EventDispatcher>();

    // Prepare window
    auto windowConfig   = window::Config();
    windowConfig.width  = config.windowWidth;
    windowConfig.height = config.windowHeight;
    window = make_unique<window::Window>(windowConfig, *eventDispatcher);
    
    // Basic exit event
    eventDispatcher->subscribeToEvent(events::EVENT_CODE_APPLICATION_QUIT, this, [&](events::Event) {
        status = Status::Exited;
        return true;
    });
    
    // resize event
    eventDispatcher->subscribeToEvent(events::EVENT_CODE_RESIZED, this, [this](events::Event event) {
        return onResize(event.data.u16[0], event.data.u16[1]);
    });
    
    // system for translating inputs to easy and managable API
    inputHandler = make_unique<input::InputHandler>(*window, *eventDispatcher);
    inputHandler->setInputChangeCallback(bind(&BasicOpenGLApplication::onInputChangeInternal, this, placeholders::_1));

    // system for time stepping
    timer = make_unique<timing::Timer>();
    timer->setOnTickCallback(bind(&BasicOpenGLApplication::onTickInternal, this, placeholders::_1));

    // Display main window and initiate render loop
    // --------------------------------------------
    
    // show window
    window->show(); // from now opengl context exists
    status = Status::Initialized;
    
    // prepare opengl debugging
    #ifdef DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(GLDdebugCallback, nullptr);
    #endif
    
    // let user run its initiation procedure
    if (!init()) {
        RB_ERROR("User initialization failed.");
        return false;
    }
    
    // run main window loop
    status = Status::Running;
    while (status == Status::Running) {
        draw();
        window->fireEvents();
        timer->checkTick();
        window->swapFrames();
    }
    
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

bool BasicOpenGLApplication::onTickInternal(const timing::TimeStep tick)
{
    inputHandler->onTick(tick);
    return onTick(inputHandler->getCurrentState(), tick);
}

void BasicOpenGLApplication::exit() {
    status = Status::Exited;
}
