
#pragma once

#include <RenderBase/events.h>

namespace rb::window {
    
    class Window
    {
        public:
            Window(rb::events::EventDispatcher& eventDispatcher) : eventDispatcher(eventDispatcher) {}
            void swapFrames();
            void fireEvents();
            
        private:
            rb::events::EventDispatcher& eventDispatcher;
    };
    
}