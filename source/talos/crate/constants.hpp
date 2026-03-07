#ifndef _TALOS_CRATE_CONSTANTS_HPP
#define _TALOS_CRATE_CONSTANTS_HPP

/// Talos Includes
#include "talos/forward/crate.hpp"

namespace Talos::Crate::Constants {

    //  PROPERTIES  //

    /// @brief Explicit crate filename.
    static inline constexpr $::String::View filename() { return "_crate.jsonc"; }

    //  PUBLIC METHODS  //

    /// @brief Gets the builtin crates directory.
    static inline constexpr $::Filesystem::Path internal() {
        return $::Path::canonical("../crates", $::Executable::resolve());
    }

    /// @brief Gets the vendors crates directory.
    static inline constexpr $::Filesystem::Path external() { $_ABORT("Unimplemented!"); }

}  // namespace Talos::Crate::Constants

#endif
