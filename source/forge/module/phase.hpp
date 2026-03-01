#ifndef _FORGE_MODULE_PHASE_HPP
#define _FORGE_MODULE_PHASE_HPP

/// Forge Modules
#include "forge/forward/module.hpp"

//  X-MACROS  //

/// @brief Available Module Phases.
#define FORGE_XX_MODULE_PHASES(X) \
    X(CLEANED)                    \
    X(PARSED)                     \
    X(TYPED)                      \
    X(COMPILED)                   \
    X(EXPORTED)

/// @brief Available Modules Dumps.
#define FORGE_XX_MODULE_DUMPS(X) \
    X(SYNTAX)                    \
    X(TYPEDEFS)                  \
    X(BYTECODE)

//  NAMESPACES  //

namespace Forge::Module {

    /// @brief Available Printing Dumps.
    $_XX_ENUM_CLASS(Dump, uint8_t, FORGE_XX_MODULE_DUMPS);

    /// @brief Available Module Phases.
    $_XX_ENUM_CLASS(Phase, uint8_t, FORGE_XX_MODULE_PHASES);

}  // namespace Forge::Module

#endif
