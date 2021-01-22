#pragma once
#if defined DEBUG && !defined DISABLE_LOGGING
    #include <iostream>
    #include <stdio.h>
    #include <glm/gtx/string_cast.hpp>
    #define RB_DEBUG(...)     std::cerr << __VA_ARGS__ << std::endl
    #define RB_DEBUG_F(...)   printf(__VA_ARGS__)
    #define RB_ASSERT(x, ...) if(!(x)) RB_DEBUG("Assertion Failed: " << __VA_ARGS__); __debugbreak()
#else
    #define RB_DEBUG(...)     while(false)
    #define RB_DEBUG_F(...)   while(false)
    #define RB_ASSERT(x, ...) while(false)
#endif
