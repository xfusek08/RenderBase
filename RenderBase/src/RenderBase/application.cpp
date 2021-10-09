
#include <RenderBase/application.h>
#include <RenderBase/logging.h>

using namespace std;
using namespace rb;
using namespace rb::app;

bool inicializeInternal(Application& app)
{
    app.eventDispatcher = make_unique<events::EventDispatcher>();
    
    // create window
    auto config = window::Config();
    config.width = app.config.windowWidth;
    config.height = app.config.windowHeight;
    app.window = make_unique<window::Window>(config, *app.eventDispatcher);
    
    // exit on close event
    app.eventDispatcher->subscribeToEvent(events::EVENT_CODE_APPLICATION_QUIT, &app, [&app](events::Event) {
        app.status = Status::Exited;
        return true;
    });
    
    return true;
}

// API implementation

BasicOpengGLApplication::BasicOpengGLApplication(Configuration config)
{
    state.config = config;
}

bool BasicOpengGLApplication::run()
{
    // init application when uninitialized
    if (state.status == Status::Uninitialized) {
        RB_DEBUG("Application is inicializing ... ");
        
        if (!(inicializeInternal(state) && init())) {
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

Configuration rb::app::loadDefaultConfigFromArgumets(int argCount, char** arguments)
{
    // TODO parse command line argumets using arumet parser module.
    
    return Configuration(); // use default values for now
}
