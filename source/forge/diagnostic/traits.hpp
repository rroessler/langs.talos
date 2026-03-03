#ifndef _FORGE_DIAGNOSTIC_TRAITS_HPP
#define _FORGE_DIAGNOSTIC_TRAITS_HPP

/// Forge Modules
#include "forge/forward/diagnostic.hpp"

//  X-MACROS  //

#define XX_SEVERITY_COLORS(X) \
    X(NONE, grey)             \
    X(HINT, cyan)             \
    X(INFO, blue)             \
    X(ERROR, red)             \
    X(WARN, yellow)

//  NAMESPACES  //

namespace Forge::Diagnostic::Traits {

    /**
     * @brief Gets the associated tags.
     * @param code                  Diagnostic code.
     */
    Tags tags(Code code);

    /**
     * @brief Checks if a diagnostic can be overriden.
     * @param code                  Diagnostic code.
     */
    bool overridable(Code code);

    /**
     * @brief Gets the default severity.
     * @param code                  Diagnostic code.
     */
    Severity severity(Code code);

    /**
     * @brief Gets the message format.
     * @param code                  Diagnostic code.
     */
    $::String::View message(Code code);

    /**
     * @brief Gets the associated category.
     * @param code                  Diagnostic code.
     */
    $::String::View category(Code code);

    /**
     * @brief Handles coloring severities.
     * @param severity              Severity to color.
     */
    static inline constexpr $::ANSI color(Severity severity) {
#define X(N, C, ...) \
    case Severity::N: return $::Dye::C(#N).bold();
        switch (severity) { XX_SEVERITY_COLORS(X) default : return $::Dye::dim("UNK"); }
#undef X
    }

    /**
     * @brief Handles formatting traits.
     * @param code                  Diagnostic code.
     * @param args                  Arguments to format.
     */
    template <class... As>
    static inline constexpr $::String::Buffer format(Code code, As&&... args) {
        return fmt::format(fmt::runtime(message(code)), std::forward<As>(args)...);
    }

}  // namespace Forge::Diagnostic::Traits

//  UNDEFINES  //

#undef XX_SEVERITY_COLORS

#endif
