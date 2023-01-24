/**
 * This implementation is based on Kohi Game Engine Project by Travis Vroman:
 * https://github.com/travisvroman/kohi/blob/main/engine/src/core/event.c
 */

#include <RenderBase/events.h>
#include <RenderBase/asserts.h>

#include <array>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
using namespace rb::events;

// internal datastructure implementation
// ---------------------------------------------------------------------------------------------------------

/**
 * Defines max number of unique events code which can be used to be subscribed to
 */
#define MAX_CODES 1024

/**
 * Internal record of listener subscribed to an event with callback function
 */
struct EventSubscription {
    void* listener;
    EventCallback callback;
};

/**
 * Internal dispatcher state
 *
 * For each code there is a vector of subscribed callbacks with their listenres
 */
struct EventDispatcher::State {
    array<vector<EventSubscription>, MAX_CODES> subscriptionTables;
};

// implementation of API
// ----------------------------------------------------------------------------------------------------------

EventDispatcher::EventDispatcher()
{
    state = make_unique<State>();
}

EventDispatcher::~EventDispatcher()
{
    // descruction procedure ...
}

bool EventDispatcher::subscribeToEvent(uint16 eventCode, void* listener, EventCallback callback)
{
    RB_ASSERT(eventCode < MAX_CODES);
    auto& codesSubscribers = state->subscriptionTables[eventCode];
    
    auto match = ranges::find_if(codesSubscribers, [listener](EventSubscription subscription) {
        return subscription.listener == listener;
    });
    
    if (match != codesSubscribers.end()) {
        RB_WARNING("Cannot register event - listener is already registered for this event code.");
        return false;
    }
    
    codesSubscribers.push_back({listener, callback});
    return true;
}

bool EventDispatcher::unSubscribeToEvent(uint16 eventCode, void* listener)
{
    RB_ASSERT(eventCode < MAX_CODES);
    auto& codesSubscribers = state->subscriptionTables[eventCode];
    
    if (codesSubscribers.empty()) {
        return false;
    }
    
    auto match = ranges::find_if(codesSubscribers, [listener](EventSubscription subscription) {
        return subscription.listener == listener;
    });
    
    if (match != codesSubscribers.end()) {
        codesSubscribers.erase(match);
        return true;
    }
    
    return false;
}

bool EventDispatcher::fireEvent(uint16 eventCode, void* sender, EventData data)
{
    RB_ASSERT(eventCode < MAX_CODES);
    auto& codesSubscribers = state->subscriptionTables[eventCode];
    
    if (codesSubscribers.empty()) {
        return false; // no one is listening -> not handled
    }
    
    for (auto subscription : codesSubscribers) {
        if (subscription.callback({eventCode, sender, subscription.listener, data})) {
            return true; // event successfully handled
        }
    }
    
    return false; // not handled
}
