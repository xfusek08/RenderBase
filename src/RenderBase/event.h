#pragma once

namespace rb {

    enum class EventType {
        Unknown,
        MouseMove,
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

    union Event {
        EventType type = EventType::Unknown;
        MouseMoveEvent mouseMoveData;
    };

}