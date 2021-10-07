
#include <RenderBase/logging.h>
#include <RenderBase/platform.h>

using namespace rb;
using namespace rb::platform;

std::string levelToString(LogLevel level)
{
    switch (level) {
        case LogLevel::Fatal:   return "Fatal";
        case LogLevel::Error:   return "Error";
        case LogLevel::Warning: return "Warning";
        case LogLevel::Info:    return "Info";
        case LogLevel::Debug:   return "Debug";
        case LogLevel::Trace:   return "Trace";
        default:                return "";
    }
}

TerminalColor levelToColor(LogLevel level)
{
    switch (level) {
        case LogLevel::Fatal:   return TerminalColor::Purple;
        case LogLevel::Error:   return TerminalColor::Red;
        case LogLevel::Warning: return TerminalColor::Yellow;
        case LogLevel::Info:    return TerminalColor::Blue;
        default:                return TerminalColor::Default;
    }
}

void rb::log(LogLevel level, std::string message)
{
    terminalPrint(
        "[" + levelToString(level) + "]: " + message + "\n",
        levelToColor(level)
    );
}
