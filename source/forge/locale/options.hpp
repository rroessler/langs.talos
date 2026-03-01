#ifndef _FORGE_LOCALE_OPTIONS_HPP
#define _FORGE_LOCALE_OPTIONS_HPP

/// Forge Modules
#include "forge/forward/locale.hpp"

namespace Forge::Locale {

    /// @brief Locale Options.
    struct Options {
        //  PROPERTIES  //

        /// @brief Denotes the initial locale.
        const char* initial = nullptr;

        //  CONSTRUCTORS  //

        /// @brief Default locale options constructor.
        constexpr Options() = default;
    };

}  // namespace Forge::Locale

#endif
