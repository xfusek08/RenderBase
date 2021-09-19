
/**
 * This is super simple logging implementation when debug mode is enabled
 *
 * For future better logging implementation see these:
 *  - https://github.com/xfusek08/GeoPlanetDemo/blob/master/src/GeoPlanetDemo/core/Log.
 *  - https://www.youtube.com/watch?v=dZr-53LAlOw&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT
 *  - https://youtu.be/l9e8PJskYnI?t=617
 */

#pragma once

#if defined DEBUG
    #include <iostream>
    #include <glm/gtx/string_cast.hpp>
    #define RB_LOG_DEBUG(...) std::cerr << __VA_ARGS__ << std::endl
#else
    #define RB_LOG_DEBUG(...)
#endif
