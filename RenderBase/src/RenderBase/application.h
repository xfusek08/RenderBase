
#pragma once

#include <RenderBase/defines.h>
#include <RenderBase/defaults.h>
#include <RenderBase/events.h>
#include <RenderBase/window.h>

#include <memory>

// modules namespace
namespace rb::app {
        
    /**
     * Configuration data structure for specifiing properties of created application.
     */
    struct Configuration {
        uint32 windowWidth  = DEFAULT_WINDOW_WIDTH;
        uint32 windowHeight = DEFAULT_WINDOW_HEIGHT;
        uint32 fpsCap       = DEFAULT_FPS_CAP;
    };
    
    enum class Status {
        Uninitialized,
        Initialized,
        Running,
        Stopped,
        Exited,
    };
    
    /**
     * Application state holding all needed data including subsystems etc.
     */
    struct Application {
        Configuration config = {}; // this is used only during app initialization process
        Status        status = Status::Uninitialized;
        
        // application sub-systems
        std::unique_ptr<rb::events::EventDispatcher> eventDispatcher;
        std::unique_ptr<rb::window::Window>          window;
    };
    
    /**
     * Class serving as simple API for quick creating an windowed application based on Given standardized configuration.
     */
    class BasicOpenGLApplication
    {
        public:
            BasicOpenGLApplication(Configuration config);
            
            bool run();
            
        protected:
            virtual bool init()   = 0;
            virtual bool deinit() = 0;
            virtual void draw()   = 0;
            
            Application state = {};
    };
    
    /**
     * Function to load configuration from command line argumets in standartized format
     */
    Configuration loadDefaultConfigFromArguments(int32 argCount, char** arguments);
}
