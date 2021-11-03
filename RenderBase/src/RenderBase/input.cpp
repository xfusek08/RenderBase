
#include <RenderBase/input.h>

using namespace std;
using namespace rb;
using namespace rb::input;

bool InputState::isKeyPressed(KeyCode key) const
{
    return glfwGetKey(window->getGLFWHandle(), key) == GLFW_PRESS;
}

bool InputState::isMouseButtonPressed(MouseCode button) const
{
    return glfwGetMouseButton(window->getGLFWHandle(), button) == GLFW_PRESS;
}

void InputHandler::setInputChangeCallback(InputChangeCallBack callback)
{
    onChangeCallback = callback;
    
    eventDispatcher.subscribeToEvent(events::EVENT_CODE_KEY_PRESSED, this, [this](events::Event event) {
        actInputState = InputState(
            window,
            { 0, 0 },
            actInputState.getMousePosition(),
            { 0, 0 }
        );
        return onChangeCallback(actInputState);
    });
    
    eventDispatcher.subscribeToEvent(events::EVENT_CODE_KEY_RELEASED, this, [this](events::Event event) {
        actInputState = InputState(
            window,
            { 0, 0 },
            actInputState.getMousePosition(),
            { 0, 0 }
        );
        return onChangeCallback(actInputState);
    });
    
    eventDispatcher.subscribeToEvent(events::EVENT_CODE_SCROLLED, this, [this](events::Event event) {
        actInputState = InputState(
            window,
            { event.data.f32[0], event.data.f32[1] },
            actInputState.getMousePosition(),
            { 0, 0 }
        );
        return onChangeCallback(actInputState);
    });
    
    eventDispatcher.subscribeToEvent(events::EVENT_CODE_MOUSE_MOVED, this, [this](events::Event event) {
        glm::vec2 newPos = { event.data.f32[0], event.data.f32[1] };
        actInputState = InputState(
            window,
            { 0, 0 },
            newPos,
            actInputState.getMousePosition() - newPos
        );
        return onChangeCallback(actInputState);
    });
}

void InputHandler::onTick(const timing::TimeStep& tick)
{
     actInputState = InputState(
        window,
        { 0, 0 },
        actInputState.getMousePosition(),
        { 0, 0 }
    );
}
