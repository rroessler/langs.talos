#ifndef _XTDLIB_SYSTEM_CONSTANTS_HPP
#define _XTDLIB_SYSTEM_CONSTANTS_HPP

/// Library Modules
#include "xtdlib/string/view.hpp"
#include "xtdlib/system/architecture.hpp"
#include "xtdlib/system/platform.hpp"

//  MACROS  //

/// @brief Handles matching against details.
#define $_ARCH_MATCH(L, R) $::System::arch().ends_with("64") ? L : R
#define $_ARCH_TYPED(L, R) std::conditional_t<$::System::arch().ends_with("64"), L, R>

//  NAMESPACES  //

namespace $::System {
    //  PROPERTIES  //

    /// @brief The system architecture identifier.
    static inline constexpr String::View arch() { return $_ARCH_NAME; }

    /// @brief The system platform identifier.
    static inline constexpr String::View platform() { return $_PLATFORM_NAME; }

}  // namespace $::System

#endif
