
#include <RenderBase/window.h>
#include <RenderBase/logging.h>

using namespace rb;
using namespace rb::window;

void Window::swapFrames()
{
    RB_DEBUG('frame swap');
}

void Window::fireEvents()
{
    events::EventData dummy;
    this->eventDispatcher.fireEvent(events::EVENT_CODE_APPLICATION_QUIT, this, dummy);
}
