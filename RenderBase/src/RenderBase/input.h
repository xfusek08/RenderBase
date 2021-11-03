
#pragma once

#include <RenderBase/defines.h>
#include <RenderBase/events.h>
#include <RenderBase/window.h>
#include <RenderBase/timing.h>

#include <glm/glm.hpp>

namespace rb::input {
    
    using KeyCode   = uint16;
    using MouseCode = uint16;
    
    struct InputState {
        InputState(
            window::Window& window,
            glm::vec2       scroll        = {0, 0},
            glm::vec2       mousePosition = {0, 0},
            glm::vec2       delta         = {0, 0}
        ) : window(&window), scroll(scroll), mousePosition(mousePosition), delta(delta) {}
        
        inline glm::vec2 getScroll() const { return scroll; }
        inline glm::vec2 getMousePosition() const { return mousePosition; }
        inline glm::vec2 getMouseDelta() const { return delta; }
        
        bool isKeyPressed(KeyCode key) const;
        bool isMouseButtonPressed(MouseCode button) const;
        
        private:
            glm::vec2 scroll = {0, 0};
            glm::vec2 mousePosition = {0, 0};
            glm::vec2 delta = {0, 0};
            window::Window* window;
    };
    
    using InputChangeCallBack = std::function<bool(const InputState&)>;
    
    class InputHandler
    {
        public:
            InputHandler(window::Window& window, events::EventDispatcher& eventDispatcher) :
                window(window),
                eventDispatcher(eventDispatcher),
                actInputState(window) {}
                
            void setInputChangeCallback(InputChangeCallBack callback);
            void onTick(const timing::TimeStep& tick);
            
            inline const InputState& getCurrentState() const { return actInputState; }
            
        private:
            InputChangeCallBack onChangeCallback;
            InputState actInputState;
            
            // reference to other sub-systems this subsystem is using
            events::EventDispatcher& eventDispatcher;
            window::Window& window;
    };
}
