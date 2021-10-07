
#include <RenderBase/rb.h>

static bool wasInitialized = false;

void rb::initialize() {
    RB_ASSERT_MSG(!wasInitialized, "Render base cannot be initialized twice in live of the application");
    // TODO: initialization code
    wasInitialized = true;
}

void rb::destroy() {
    wasInitialized = false;
}
