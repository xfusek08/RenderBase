
#pragma once

#include <RenderBase/defines.h>
#include <RenderBase/defaults.h>
#include <RenderBase/events.h>
#include <RenderBase/window.h>
#include <RenderBase/input.h>
#include <RenderBase/timing.h>

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
     * Class serving as simple API for quick creating an windowed application based on Given standardized configuration.
     */
    class BasicOpenGLApplication
    {
        public:
            BasicOpenGLApplication(Configuration config);
            
            bool run();
            
        protected:
            void exit();
            
            virtual bool init() = 0;
            virtual void draw() = 0;
            virtual bool onResize(uint32 newWidth, uint32 newHeight) { return false; }
            virtual bool onInputChange(const input::InputState& inputState, const timing::TimeStep& tick) { return false; };
            virtual bool onTick(const input::InputState& inputState, const timing::TimeStep& tick) { return false; };
            virtual bool finalize() { return true; };
        
            Configuration config = {}; // this is used only during app initialization process
            Status        status = Status::Uninitialized;
            
            // application sub-systems
            std::unique_ptr<rb::events::EventDispatcher> eventDispatcher;
            std::unique_ptr<rb::window::Window>          window;
            std::unique_ptr<rb::input::InputHandler>     inputHandler;
            std::unique_ptr<rb::timing::Timer>           timer;
            
        private:
            bool onInputChangeInternal(const input::InputState& inputState);
            bool onTickInternal(const timing::TimeStep tick);
    };
    
    /**
     * Function to load configuration from command line arguments in standardized format
     */
    Configuration loadDefaultConfigFromArguments(int32 argCount, char** arguments);
}
