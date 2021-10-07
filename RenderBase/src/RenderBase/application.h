
#pragma once

#include <RenderBase/defines.h>
#include <RenderBase/events.h>
#include <RenderBase/window.h>

#include <memory>

// modules namespace
namespace rb::app {
        
    /**
     * Configuration data structure for specifiing properties of created application.
     */
    struct Configuration {
        uint32 windowWidth;
        uint32 windowHeight;
    };
    
    enum class Status {
        Uninitialized,
        Initialized,
        Running,
        Halted,
        Exited,
    };
    
    /**
     * Applicattion state holding all needed data including subsystems etc.
     */
    struct Application {
        Configuration config = {};
        Status        status = Status::Uninitialized;
        
        // aplication sub-systems
        std::unique_ptr<rb::events::EventDispatcher> eventDispatcher;
        std::unique_ptr<rb::window::Window>          window;
    };
    
    /**
     * Class serving as simple API for quick creating an windowed aplication based on Given standardized configuration.
     */
    class BasicOpengGLApplication
    {
        public:
            BasicOpengGLApplication(Configuration config);
            
            bool run();
            
        protected:
            virtual bool init() = 0;
            virtual void draw() = 0;
            
        private:
            Application appState = {};
    };
    
    /**
     * Function to load configuration from command line argumets in standartized format
     */
    Configuration loadDefaultConfigFromArgumets(int32 argCount, char** arguments);
}
