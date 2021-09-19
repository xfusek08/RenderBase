
#include <lib.h>

#include <RenderBase/window.h>

#include <iostream>

void printTest()
{
    Window w = createWindow();
    std::cout << "Window \"" << w.windowId << "\" cerated\n";
}
