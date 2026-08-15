#ifndef _XTDLIB_SYSTEM_SWITCH_HPP
#define _XTDLIB_SYSTEM_SWITCH_HPP

/// Library Includes
#include "xtdlib/string/view.hpp"
#include "xtdlib/system/architecture.hpp"
#include "xtdlib/system/platform.hpp"

//  MACROS  //

/// @brief Handles matching against details.
#define $_ARCH_TEST() $::System::arch().ends_with("64")
#define $_ARCH_MATCH(L, R) $_ARCH_TEST() ? L : R
#define $_ARCH_TYPED(L, R) std::conditional_t<$_ARCH_TEST(), L, R>

//  NAMESPACES  //

namespace $::System {
//  PROPERTIES  //

/// @brief The system architecture identifier.
static inline constexpr String::View arch() { return $_ARCH_NAME; }

/// @brief The system platform identifier.
static inline constexpr String::View platform() { return $_PLATFORM_NAME; }

} // namespace $::System

#endif
