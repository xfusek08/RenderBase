
#include <RenderBase/application.h>
#include <RenderBase/logging.h>

using namespace std;
using namespace rb;
using namespace rb::app;

// internal declarations
bool inicializeInternal(Application& app);

// API implementation

BasicOpengGLApplication::BasicOpengGLApplication(Configuration config)
{
    appState.config = config;
}

bool BasicOpengGLApplication::run()
{
    if (appState.status == Status::Uninitialized) {
        RB_DEBUG("Application is inicializing ... ");
        
        if (!(inicializeInternal(appState) && init())) {
            RB_FATAL("Failed to inicialize application");
            return false;
        }
        
        appState.status = Status::Initialized;
    }
    
    appState.status = Status::Running;
    while (appState.status == Status::Running) {
        draw();
        appState.window->swapFrames();
        appState.window->fireEvents();
    }
    return true;
}

Configuration rb::app::loadDefaultConfigFromArgumets(int argCount, char** arguments)
{
    // TODO parse command line argumets using arumet parser module.
    return {};
}

// internal implementation

bool inicializeInternal(Application& app)
{
    app.eventDispatcher = make_unique<events::EventDispatcher>();
    app.window          = make_unique<window::Window>(*app.eventDispatcher);
    
    app.eventDispatcher->subscribeToEvent(events::EVENT_CODE_APPLICATION_QUIT, nullptr, [&](events::Event) {
        app.status == Status::Exited;
        return true;
    });
    
    
    // register app events
    
    
    return true;
}