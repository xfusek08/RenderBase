/**
 * This file is inspired by Hazel engine by Yan Chernikov
 *  https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/PlatformDetection.h
 *  https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/Base.h
 *
 * and Kohi Game Engine Project by Travis Vroman:
 *   https://github.com/travisvroman/kohi/blob/main/engine/src/defines.h
 */

#pragma once

// Unsigned int types.
typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

// Signed int types.
typedef signed char      int8;
typedef signed short     int16;
typedef signed int       int32;
typedef signed long long int64;

// Floating point types
typedef float  float32;
typedef double float64;

// Properly define static assertions.
#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else
#define STATIC_ASSERT static_assert
#endif

// Ensure all types are of the correct size.
STATIC_ASSERT(sizeof(uint8)  == 1, "Expected uint8 to be 1 byte.");
STATIC_ASSERT(sizeof(uint16) == 2, "Expected uint16 to be 2 bytes.");
STATIC_ASSERT(sizeof(uint32) == 4, "Expected uint32 to be 4 bytes.");
STATIC_ASSERT(sizeof(uint64) == 8, "Expected uint64 to be 8 bytes.");

STATIC_ASSERT(sizeof(int8)  == 1, "Expected int8 to be 1 byte.");
STATIC_ASSERT(sizeof(int16) == 2, "Expected int16 to be 2 bytes.");
STATIC_ASSERT(sizeof(int32) == 4, "Expected int32 to be 4 bytes.");
STATIC_ASSERT(sizeof(int64) == 8, "Expected int64 to be 8 bytes.");

STATIC_ASSERT(sizeof(float32) == 4, "Expected float32 to be 4 bytes.");
STATIC_ASSERT(sizeof(float64) == 8, "Expected float64 to be 8 bytes.");

// platform detection
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
