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

// moduile-internal data structure for storing registrations to events
// ---------------------------------------------------------------------------------------------------------

/**
 * Defines max number of unique events code which can be used to be subscribet to (iamgine biding points)
 */
#define MAX_CODES 1024

struct EventSubscription {
    void* listener;
    EventCallback callback;
};
using EventSubscriptionLists     = vector<EventSubscription>;
using EventSubscriptionCodeTable = array<EventSubscriptionLists, MAX_CODES>;

/**
 * In order to encapsulate implementation details in this module we store internal event dispatcher data
 * in static variable.
 * We do this to avoid using stl types in header file for this module and to have cleaner API.
 */
static unordered_map<EventDispatcher*, EventSubscriptionCodeTable> dispatchersSubstrictionTable;


// implementation of API
// ----------------------------------------------------------------------------------------------------------

EventDispatcher::EventDispatcher()
{
    dispatchersSubstrictionTable[this] = {};
}

EventDispatcher::~EventDispatcher()
{
    dispatchersSubstrictionTable.erase(this);
}

bool EventDispatcher::subscribeToEvent(uint16 eventCode, void* listener, EventCallback callback)
{
    RB_ASSERT(eventCode < MAX_CODES);
    auto& codesSubscribers = dispatchersSubstrictionTable[this][eventCode];
    
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
    auto& codesSubscribers = dispatchersSubstrictionTable[this][eventCode];
    
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
    auto& codesSubscribers = dispatchersSubstrictionTable[this][eventCode];
    
    if (codesSubscribers.empty()) {
        return false; // no one is listenig
    }
    
    for (auto subscribtion : codesSubscribers) {
        if (subscribtion.callback({eventCode, sender, subscribtion.listener, data})) {
            return true; // event succesfuly handled
        }
    }
    
    // event was not handled
    return false;
}
