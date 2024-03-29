
/**
 * This is super simple logging implementation when debug mode is enabled
 *
 * For future better logging implementation see these:
 *  - https://github.com/xfusek08/GeoPlanetDemo/blob/master/src/GeoPlanetDemo/core/Log.
 *  - https://www.youtube.com/watch?v=dZr-53LAlOw&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT
 *  - https://youtu.be/l9e8PJskYnI?t=617
 */

#pragma once

#include <sstream>

namespace rb
{
    enum class LogLevel {
        Fatal,
        Error,
        Warning,
        Info,
        Debug,
        Trace
    };
    
    // this function can be in the future replace by more complex logger singleton object
    // __attribute__((visibility("default"))) void log(LogLevel level, std::string message);
    void log(LogLevel level, std::string message);
}

#ifdef NO_LOG
    #define STREAM_TO_STR(...)
    #define RB_FATAL(...)
    #define RB_ERROR(...)
    #define RB_WARNING(...)
    #define RB_INFO(...)
    #define RB_DEBUG(...)
    #define RB_TRACE(...)
#else
    #define STREAM_TO_STR(S) ((std::ostringstream() << S)).str()

    #define RB_FATAL(...)   rb::log(rb::LogLevel::Fatal, STREAM_TO_STR(__VA_ARGS__))
    
    #define RB_ERROR(...)   rb::log(rb::LogLevel::Error, STREAM_TO_STR(__VA_ARGS__))
    
    #ifndef NO_WARNING_LOG
        #define RB_WARNING(...) rb::log(rb::LogLevel::Warning, STREAM_TO_STR(__VA_ARGS__))
    #else
        #define RB_WARNING(...)
    #endif
    
    #define RB_INFO(...)    rb::log(rb::LogLevel::Info, STREAM_TO_STR(__VA_ARGS__))

    #if defined(DEBUG) and !defined(NO_DEBUG_LOG)
        #define RB_DEBUG(...) rb::log(rb::LogLevel::Debug, STREAM_TO_STR(__VA_ARGS__))
        #define RB_TRACE(...) rb::log(rb::LogLevel::Trace, STREAM_TO_STR(__VA_ARGS__ << "\n In File: " << __FILE__ << "\n On Line: " << __LINE__))
    #else
        #define RB_DEBUG(...)
        #define RB_TRACE(...)
    #endif
#endif
