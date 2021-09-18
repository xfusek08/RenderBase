
#include <iostream>
#include <RenderBase/window.h>

int main()
{
    Window w = createWindow();
    std::cout << "Window \"" << w.windowId << "\" cerated\n";
    return 0;
}
