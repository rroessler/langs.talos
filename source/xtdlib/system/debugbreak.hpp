#ifndef _XTDLIB_SYSTEM_DEBUGBREAK_HPP
#define _XTDLIB_SYSTEM_DEBUGBREAK_HPP

/// Library Includes
#include "xtdlib/macros/attributes.hpp"
#include "xtdlib/system/architecture.hpp"
#include "xtdlib/system/unreachable.hpp"

namespace $::System {

//  PUBLIC METHODS  //

/// @brief Internal debugbreak handler.
$_NORETURN $_INLINE_FORCE static void debugbreak() {
#if defined(_MSC_VER)
  __debugbreak();
#elif defined(__has_builtin) && __has_builtin(__builtin_debugbreak)
  __builtin_debugbreak();
#elif defined(__has_builtin) && __has_builtin(__builtin_trap)
  __builtin_trap();
#elif defined(__has_builtin) && __has_builtin(__builtin_debugtrap)
  __builtin_debugtrap();
#elif $_ARCH_X32 || $_ARCH_X64
  __asm__ volatile("int $0x03");
#elif $_ARCH_ARM
  __asm__ volatile(".inst 0xE7F001F0");
#elif $_ARCH_ARM64
  __asm__ volatile(".inst 0xD4200000");
#elif $_ARCH_PPC32
  __asm__ volatile(".4byte 0x7d821008");
#elif $_ARCH_RISCV64
  __asm__ volatile(".4byte 0x00100073");
#else // attempt handling via trap signal instance
  std::raise(SIGTRAP);
#endif

  // ensure that everything is unreachable now
  unreachable();
}

} // namespace $::System

#endif
