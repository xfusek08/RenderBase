
/**
 * This is definition of basic assertion macros inspired by Kohi game engine:
 * https://github.com/travisvroman/kohi/blob/main/engine/src/core/asserts.h
 */

#pragma once

#ifndef NO_ASSERT
    #include <string>

    #ifdef RB_PLATFORM_WINDOWS
        #define RB_DEBUG_BREAK() __debugbreak()
    #else
        #define RB_DEBUG_BREAK() __builtin_trap()
    #endif

    namespace rb
    {
        void reportAssert(std::string expression, std::string message, std::string file, int32_t line);
    }

    #define RB_ASSERT(expr) \
        { \
            if (expr) { \
            } else { \
                rb::reportAssert(#expr, "", __FILE__, __LINE__); \
                RB_DEBUG_BREAK(); \
            } \
        }

    #define RB_ASSERT_MSG(expr, message) \
        { \
            if (expr) { \
            } else { \
                rb::reportAssert(#expr, message, __FILE__, __LINE__); \
                RB_DEBUG_BREAK(); \
            } \
        }
#else
    #define RB_ASSERT(...)
    #define RB_ASSERT_MSG(...)
#endif
