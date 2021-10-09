
#pragma once

#include <RenderBase/events.h>
#include <RenderBase/defaults.h>
#include <RenderBase/defines.h>

#include <memory>

namespace rb::window {
    
    struct Config {
        const char* title  = DEFAULT_WINDOW_TITLE;
        uint32 width       = DEFAULT_WINDOW_WIDTH;
        uint32 height      = DEFAULT_WINDOW_HEIGHT;
        bool vSynchEnabled = DEFAULT_VSYNCH_ENABLED;
    };
    
    struct Window
    {
        // lifetime
        Window(Config config, rb::events::EventDispatcher& eventDispatcher);
        ~Window();
        
        bool show();
        bool close();
        
        // setters
        void setVSynch(bool enabled);

        // getters
        bool isOpen() const;
        bool getVSynch() const;
        
        // runtime
        void swapFrames();
        void fireEvents();
        
        // OpenGL
        bool makeGLContextCurrent();
        
        private:
            struct State;
            std::unique_ptr<State> state;
    };
    
    void* getGLFunctionTablePointer();
}
