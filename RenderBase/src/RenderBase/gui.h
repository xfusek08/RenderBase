
#pragma once

#include <RenderBase/input.h>
#include <RenderBase/timing.h>
#include <RenderBase/window.h>

namespace rb::gui {
    
    struct GuiState
    {
        template<typename T>
        T getValue(const char* identifier) const { return T(); };
    };
    
    class Gui
    {
        public:
            
            Gui(const window::Window& window); // init gui system
            ~Gui(); // destryo gui system
            
            void update(const input::InputState& inputState, const timing::TimeStep& tick);
            void draw();
            
            inline bool cleanState() { return  stateDirtyFlag = false; }
            
            inline const GuiState& getState() const { return state; }
            inline bool isStateDirty() const { return  stateDirtyFlag; }
            
        private:
            GuiState state;
            bool stateDirtyFlag = false;
    };
}
