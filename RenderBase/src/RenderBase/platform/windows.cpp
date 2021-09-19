
#include <RenderBase/defines.h>

#ifdef RB_PLATFORM_WINDOWS
    #include <RenderBase/platform.h>
    #include <iostream>

    void rb::platform::terminalPrint(std::string message, TerminalColor color = TerminalColor::Default) {
        // colors in windows will be supported in the future
        std::cout << message;
    }

#endif
