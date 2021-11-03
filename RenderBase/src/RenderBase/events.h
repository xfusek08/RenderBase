/**
 * This file represents a encapsulated module implementing a simple general event displatching system.
 *
 * This file is based on Kohi Game Engine Project by Travis Vroman:
 * https://github.com/travisvroman/kohi/blob/main/engine/src/core/event.h
 */
#pragma once

#include <RenderBase/defines.h>

#include <functional>
#include <memory>

// modules namespace
namespace rb::events {
    
    /**
     * Data sended by event is fixed to 16B with different ways to look at them.
     */
    union EventData {
        int64   i64[2];
        uint64  u64[2];
        float64 f64[2];

        int32   i32[4];
        uint32  u32[4];
        float32 f32[4];

        int16   i16[8];
        uint16  u16[8];

        int8    i8[16];
        uint8   u8[16];

        char    c[16];
    };
    
    /**
     * Event value prepared to be passed between systems by value
     */
    struct Event {
        uint16 eventCode;
        void* sender;
        void* listener;
        EventData data;
    };
    
    /**
     * Type of event callback function with which listeneds will subscribe.
     */
    using EventCallback = std::function<bool(Event)>;
    
    /**
     * Main event system contex object
     */
    class EventDispatcher
    {
        public:
            EventDispatcher();
            ~EventDispatcher();
            
            /**
             * Subscribes listen for events sended with the provided code. Events with duplicate
             * listener/callback combos will not be registered again and will cause this to return false.
             *
             * @param eventCode The event code to listen for.
             * @param listener  A pointer to a listener instance. Can be nullptr.
             * @param callback  The callback to be invoked when the event code is fired.
             *
             * @returns true if the event is successfully registered; otherwise false.
             */
            bool subscribeToEvent(uint16 eventCode, void* listener, EventCallback callback);
            
            /**
             * Unsubscribes listener for events with the provided code. If no matching
             * registration is found, this function returns false.
             *
             * @param  eventCode The event code to stop listening for.
             * @param  listener  A pointer to a listener instance. Can be nullptr.
             *
             * @return true if the event is successfully unregistered; otherwise false.
             */
            bool unSubscribeToEvent(uint16 eventCode, void* listener);
            
            /**
             * Fires an event to subscribers of the given code. If an event handler returns
             * true, the event is considered handled and is not passed on to any more listeners.
             *
             * @param eventCode The event code to fire.
             * @param sender    A pointer to the sender. Can be nullptr.
             * @param data      The event data.
             *
             * @returns true if handled, false otherwise.
             */
            bool fireEvent(uint16 eventCode, void* sender, EventData data);
            
        public:
            struct State;
            std::unique_ptr<State> state;
    };
    
    // some predefined event codes used in the RB library, user-defined events should start beyond 255 value
    enum EventCodes {
        EVENT_CODE_APPLICATION_QUIT = 0x01, // application is to be existed | no data
        EVENT_CODE_KEY_PRESSED      = 0x02, // a keyboard key was pressed   | 1x u16 - key code
        EVENT_CODE_KEY_RELEASED     = 0x03, // a keyboard key was released  | 1x u16 - key code
        EVENT_CODE_KEY_REPEAT       = 0x04, // a keyboard key was repeated  | 1x u16 - key code
        EVENT_CODE_BUTTON_PRESSED   = 0x05, // a mouse button was pressed   | 1x u16 - button code
        EVENT_CODE_BUTTON_RELEASED  = 0x06, // a mouse button was released  | 1x u16 - button code
        EVENT_CODE_MOUSE_MOVED      = 0x07, // a mouse moved                | 2x f32 - current mouse X and Y absolute position
        EVENT_CODE_SCROLLED         = 0x08, // a scroll occurred            | 2x f32 - delta of scroll x and y
        EVENT_CODE_RESIZED          = 0x09, // application was resied       | 2x u16 - new width and height
        
        MAX_EVENT_CODE = 0xFF
    };
}
