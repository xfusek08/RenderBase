#pragma once

namespace rb {

    enum class EventType {
        Unknown,
        MouseMove,
        MouseWheel,
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

    union Event {
        EventType type = EventType::Unknown;
        MouseMoveEvent mouseMoveData;
        MouseWheelEvent mouseWheelData;
    };

}