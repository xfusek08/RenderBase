
#pragma once

#include <RenderBase/events.h>
#include <RenderBase/defaults.h>
#include <RenderBase/defines.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>

namespace rb::window {
    
    struct Config {
        const char* title  = DEFAULT_WINDOW_TITLE;
        uint32 width       = DEFAULT_WINDOW_WIDTH;
        uint32 height      = DEFAULT_WINDOW_HEIGHT;
        bool vSynchEnabled = DEFAULT_VSYNCH_ENABLED;
    };
    
    /**
     * This class represent a window, which uses givent event dispatcher to fire input events and window related events
     */
    class Window
    {
        public:
            // lifetime
            Window(Config config, rb::events::EventDispatcher& eventDispatcher);
            ~Window();
            
            bool show();
            bool close();
            
            // setters
            void setVSynch(bool enabled);
            void resize(uint32 newWidth, uint32 newHeight);

            // getters
            bool        isOpen()    const;
            bool        getVSynch() const;
            uint32      getWidth()  const;
            uint32      getHeight() const;
            GLFWwindow* getGLFWHandle() const;
            
            // runtime
            void swapFrames();
            void fireEvents();
            
        private:
            struct State;
            std::unique_ptr<State> state;
    };
    
    void* getGLFunctionTablePointer();
}
