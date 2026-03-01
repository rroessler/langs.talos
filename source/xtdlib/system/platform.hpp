#ifndef _XTDLIB_SYSTEM_PLATFORM_HPP
#define _XTDLIB_SYSTEM_PLATFORM_HPP

//  MACROS  //

#if defined(__APPLE__)
#include <TargetConditionals.h>
#define $_PLATFORM_NAME "darwin"

#if TARGET_OS_OSX
#define $_PLATFORM_DARWIN 1
#else
#error Unsupported Apple target!
#endif
#else
#define $_PLATFORM_DARWIN 0
#endif

#if defined(_WIN32) || defined(_WIN64)
#define $_PLATFORM_NAME "windows"
#define $_PLATFORM_WINDOWS 1
#else
#define $_PLATFORM_WINDOWS 0
#endif

#if defined(__linux__)
#define $_PLATFORM_NAME "linux"
#define $_PLATFORM_LINUX 1
#else
#define $_PLATFORM_LINUX 0
#endif

#if __has_include(<unistd.h>)
#define $_PLATFORM_POSIX 1
#else
#define $_PLATFORM_POSIX 0
#endif

#ifndef $_PLATFORM_NAME
#error Unsupported operating system!
#endif

#endif
