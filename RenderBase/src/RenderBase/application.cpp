
#include <RenderBase/application.h>
#include <RenderBase/logging.h>
#include <RenderBase/asserts.h>
#include <glad/glad.h>

using namespace std;
using namespace rb;
using namespace rb::app;

BasicOpenGLApplication::BasicOpenGLApplication(Configuration config)
{
    state.config = config;
}

bool BasicOpenGLApplication::run()
{
    state.status = Status::Uninitialized;
    
    RB_DEBUG("Application is initializing ... ");

    state.eventDispatcher = make_unique<events::EventDispatcher>();
    
    // create window
    auto config   = window::Config();
    config.width  = state.config.windowWidth;
    config.height = state.config.windowHeight;
    
    state.window  = make_unique<window::Window>(config, *state.eventDispatcher);
    
    // Define basic events
    state.eventDispatcher->subscribeToEvent(events::EVENT_CODE_APPLICATION_QUIT, this, [&](events::Event) {
        state.status = Status::Exited;
        return true;
    });

    // prepare window -> creates opengl context
    state.window->show();
    
    state.status = Status::Initialized;
    
    if (!init()) {
        RB_ERROR("User initialization failed.");
        return false;
    }
    
    // run main window loop
    state.status = Status::Running;
    while (state.status == Status::Running) {
        draw();
        state.window->swapFrames();
        state.window->fireEvents();
    }
    
    if (!finalize()) {
        RB_ERROR("User initialization failed.");
        return false;
    }
    
    return true;
}

Configuration rb::app::loadDefaultConfigFromArguments(int argCount, char** arguments)
{
    // TODO parse command line arguments using arumet parser module.
    return Configuration(); // use default values for now
}
