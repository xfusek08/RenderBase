
#include <application.h>
#include <RenderBase/rb.h>

static App::State state;

App::Config App::configure(int argc, char** argv) {
    return {};
}

bool App::run(const Config& config) {
    RB_DEBUG("Application Running");
    state.actConfig = config;
    rb::initialize();
    RB_DEBUG("Application Succesfully initialized");
    
    rb::destroy();
    return true;
}
