#pragma once

namespace rb {

    enum class EventType {
        Unknown,
        MouseMove,
        MouseWheel,
        KeyPressed,
    };

    struct MouseButtons {
        bool left   = false;
        bool right  = false;
        bool middle = false;
    };

    struct MouseMoveEvent {
        EventType type;
        float xPos;
        float yPos;
        float xMovedRel;
        float yMovedRel;
        MouseButtons buttons;
    };

    struct MouseWheelEvent {
        EventType type;
        float scroll;
    };

    struct KeyPressedEvent {
        EventType   type;
        int32_t keyCode;
    };

    union Event {
        EventType type = EventType::Unknown;
        MouseMoveEvent mouseMoveData;
        MouseWheelEvent mouseWheelData;
        KeyPressedEvent keyPressedData;
    };

}