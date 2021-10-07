/**
 * This file is inspired by Hazel engine
 *  - https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/PlatformDetection.h
 *  - https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/Base.h
 */

#pragma once

#ifdef _WIN32
    #ifdef _WIN64
		/* Windows x64  */
		#define RB_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__linux__)
    #define RB_PLATFORM_LINUX
#else
    #error "Yet usuported platform!"
#endif
