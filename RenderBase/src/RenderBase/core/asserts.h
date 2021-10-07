
/**
 * This is definition of basic assertion macros inspired by Kohi game engine:
 * https://github.com/travisvroman/kohi/blob/main/engine/src/core/asserts.h
 */

#pragma once

#include <RenderBase/core/logging.h>

#define REPORT_ASSERT_MSG(expr, message) RB_FATAL(STREAM_TO_STR( \
        "Assertion Failure: " << (#expr) << "\n" << \
        "Message: " << message << "\n" << \
        "In file: " << __FILE__ << "\n" << \
        "On line: " << __LINE__ \
    ))

#ifdef NO_ASSERT
    #define RB_ASSERT_MSG(expr,message) REPORT_ASSERT_MSG(expr, message); RB_INFO("Assertion skipped due to NO_ASSERT Flag.")
    #define RB_ASSERT(expr)             RB_ASSERT_MSG(expr, "")
#else
    #include <string>

    #ifdef RB_PLATFORM_WINDOWS
        #define RB_DEBUG_BREAK() __debugbreak()
    #else
        #define RB_DEBUG_BREAK() __builtin_trap()
    #endif

    #define RB_ASSERT(expr) { \
            if (expr) { \
            } else { \
                REPORT_ASSERT_MSG(expr, ""); \
                RB_DEBUG_BREAK(); \
            } \
        }

    #define RB_ASSERT_MSG(expr, message) { \
            if (expr) { \
            } else { \
                REPORT_ASSERT_MSG(expr, message); \
                RB_DEBUG_BREAK(); \
            } \
        }
#endif
