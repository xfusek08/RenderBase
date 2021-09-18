
#include <iostream>
#include <RenderBase/rb.h>

int main()
{
    Window w = createWindow();
    std::cout << "Window \"" << w.windowId << "\" cerated\n";
    return 0;
}
