
/**
 * This is super simple assertion implementation when debug mode is enabled
 *
 * For future better logging implementation see these:
 *  - https://github.com/xfusek08/GeoPlanetDemo/blob/master/src/GeoPlanetDemo/core/Utils.h
 *  - https://youtu.be/l9e8PJskYnI?t=1446
 */

#pragma once

#if DEBUG
    #include <RenderBase/defines.h>
    #include <RenderBase/logging.h>
    #define RB_ASSERT(x, ...) if(!(x)) { RB_ERROR("Assertion Failed: " << __VA_ARGS__); } RB_DEBUG_BREAK()
#else
    #define RB_ASSERT(...)
#endif
