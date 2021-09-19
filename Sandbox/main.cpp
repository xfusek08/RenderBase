
#include <RenderBase/logging.h>
#include <RenderBase/asserts.h>

int main()
{
    int32_t i = 1;
    RB_FATAL("Log test " << i++);
    RB_ERROR("Log test " << i++);
    RB_WARNING("Log test " << i++);
    RB_INFO("Log test " << i++);
    RB_DEBUG("Log test " << i++);
    RB_TRACE("Log test " << i++);
    
    auto a = 1;
    RB_ASSERT(a == 0);
    
    return 0;
}
