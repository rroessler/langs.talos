#ifndef _FORGE_DIAGNOSTIC_OPTIONS_HPP
#define _FORGE_DIAGNOSTIC_OPTIONS_HPP

/// Forge Includes
#include "forge/forward/diagnostic.hpp"

namespace Forge::Diagnostic {

    /// @brief Diagnostic Options.
    struct Options {
        //  PROPERTIES  //

        /// @brief Diagnostics limit.
        size_t limit = SIZE_MAX;

        /// @brief Minimum allowable severities.
        Severity severity = Severity::WARN;

        /// @brief Available override severities.
        $::Map<Code, Severity> overrides = {};

        /// @brief The defaulted encoding for diagnostic ranges.
        XLSP::Encoding::Type encoding = XLSP::Encoding::Type::UTF8;

        //  CONSTRUCTORS  //

        /// @brief Default constructor.
        constexpr Options() = default;
    };

}  // namespace Forge::Diagnostic

#endif
