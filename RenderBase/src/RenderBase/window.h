
#pragma once

struct Window
{
    int windowId;
};

Window createWindow()
{
    Window window;
    window.windowId = 0;
    return window;
}
