#ifndef _FORGE_CRATE_CONSTANTS_HPP
#define _FORGE_CRATE_CONSTANTS_HPP

/// Forge Includes
#include "forge/forward/crate.hpp"

namespace Forge::Crate::Constants {

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

}  // namespace Forge::Crate::Constants

#endif
