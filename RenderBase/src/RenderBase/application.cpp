
#include <RenderBase/application.h>
#include <RenderBase/logging.h>
#include <RenderBase/asserts.h>
#include <glad/glad.h>

using namespace std;
using namespace rb;
using namespace rb::app;

bool initInternal(Application& app)
{
    app.eventDispatcher = make_unique<events::EventDispatcher>();
    
    // create window
    auto config = window::Config();
    config.width = app.config.windowWidth;
    config.height = app.config.windowHeight;
    app.window = make_unique<window::Window>(config, *app.eventDispatcher);
    
    // Define basic events
    app.eventDispatcher->subscribeToEvent(events::EVENT_CODE_APPLICATION_QUIT, &app, [&app](events::Event) {
        app.status = Status::Exited;
        return true;
    });
        
    return true;
}

// API implementation

BasicOpenGLApplication::BasicOpenGLApplication(Configuration config)
{
    state.config = config;
}

bool BasicOpenGLApplication::run()
{
    // init application when uninitialized
    if (state.status == Status::Uninitialized) {
        RB_DEBUG("Application is inicializing ... ");
        
        if (!(initInternal(state) && init())) {
            RB_FATAL("Failed to inicialize application");
            return false;
        }
        
        state.status = Status::Initialized;
        RB_DEBUG("Application is succesfuly inicialized ... ");
    }
    
    // open window and run
    state.window->show();
    state.status = Status::Running;
    while (state.status == Status::Running) {
        draw();
        state.window->swapFrames();
        state.window->fireEvents();
    }
    return true;
}

Configuration rb::app::loadDefaultConfigFromArguments(int argCount, char** arguments)
{
    // TODO parse command line argumets using arumet parser module.
    
    return Configuration(); // use default values for now
}
