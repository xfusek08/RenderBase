/**
 * This header specifies common interface of platform-specific code wrapped in rb::platform namespace
 */

#pragma once

#include <string>

namespace rb::platform
{
    enum class TerminalColor {
        Default,
        Red,
        Blue,
        Yellow,
        Green,
        Orange,
        Purple
    };
    
    void terminalPrint(std::string message, TerminalColor color = TerminalColor::Default);
}
