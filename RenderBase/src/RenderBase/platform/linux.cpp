
#include <RenderBase/core/defines.h>
#ifdef RB_PLATFORM_LINUX

    #include <RenderBase/core/platform.h>
    #include <stdio.h>

    using namespace rb::platform;

    const char* colorCodes[] = {
        "1;37", // 0 - Default
        "1;31", // 1 - Red
        "1;34", // 2 - Blue
        "1;33", // 3 - Yellow
        "1;32", // 4 - Green
        "0;33", // 5 - Orange
        "1;35", // 6 - Purple
    };

    const char* getColorCode(TerminalColor color)
    {
        switch (color) {
            case TerminalColor::Red:    return colorCodes[1];
            case TerminalColor::Blue:   return colorCodes[2];
            case TerminalColor::Yellow: return colorCodes[3];
            case TerminalColor::Green:  return colorCodes[4];
            case TerminalColor::Orange: return colorCodes[5];
            case TerminalColor::Purple: return colorCodes[6];
            default:                    return colorCodes[0];
        }
    };

    void rb::platform::terminalPrint(std::string message, TerminalColor color)
    {
        printf("\033[%sm%s\033[0m", getColorCode(color), message.c_str());
    }
    
#endif
