#ifndef _XTDLIB_SYSTEM_ARCHITECTURE_HPP
#define _XTDLIB_SYSTEM_ARCHITECTURE_HPP

//  MACROS  //

#if defined(__APPLE__)
#include <TargetConditionals.h>
#endif

#if defined(__x386__) || defined(_M_IX86)
#define $_ARCH_X32 1
#define $_ARCH_NAME "x32"
#else
#define $_ARCH_X32 0
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(_M_AMD64)
#define $_ARCH_X64 1
#define $_ARCH_NAME "x64"
#else
#define $_ARCH_X64 0
#endif

#if defined(__arm__) || defined(__ARMEL__) || defined(_M_ARM)
#define $_ARCH_ARM 1
#define $_ARCH_NAME "arm32"
#else
#define $_ARCH_ARM 0
#endif

#if defined(__aarch64__) || defined(__M_ARM64)
#define $_ARCH_A64 1
#define $_ARCH_NAME "arm64"
#else
#define $_ARCH_A64 0
#endif

#if defined(__powerpc__) || defined(__ppc__) || defined(__PPC__)
#define $_ARCH_PPC32 1
#define $_ARCH_NAME "ppc32"
#else
#define $_ARCH_PPC32 0
#endif

#if defined(__powerpc64__) || defined(__PPC64__)
#define $_ARCH_PPC64 1
#define $_ARCH_NAME "ppc64"
#else
#define $_ARCH_PPC64 0
#endif

#if defined(__riscv)
#define $_ARCH_RISCV64 1
#define $_ARCH_NAME "riscv64"
#else
#define $_ARCH_RISCV64 0
#endif

#ifndef $_ARCH_NAME
#error Unsupported CPU architecture!
#endif

#endif
