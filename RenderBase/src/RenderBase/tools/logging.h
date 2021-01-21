#pragma once
#if defined DEBUG && !defined DISABLE_LOGGING
    #include <iostream>
    #include <stdio.h>
    #include <glm/gtx/string_cast.hpp>
    #define LOG_DEBUG(...)       std::cerr << __VA_ARGS__ << std::endl
    #define LOG_DEBUG_F(...)     printf(__VA_ARGS__)
    #define ASSERT_DEBUG(x, ...) if(!(x)) LOG_DEBUG("Assertion Failed: " << __VA_ARGS__); __debugbreak()
#else
    #define LOG_DEBUG(...)       while(false)
    #define LOG_DEBUG_F(...)     while(false)
    #define ASSERT_DEBUG(x, ...) while(false)
#endif
