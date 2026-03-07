#ifndef _TALOS_MODULE_PHASE_HPP
#define _TALOS_MODULE_PHASE_HPP

/// Talos Modules
#include "talos/forward/module.hpp"

//  X-MACROS  //

/// @brief Available Module Phases.
#define TALOS_XX_MODULE_PHASES(X) \
    X(CLEANED)                    \
    X(PARSED)                     \
    X(TYPED)                      \
    X(COMPILED)                   \
    X(EXPORTED)

/// @brief Available Modules Dumps.
#define TALOS_XX_MODULE_DUMPS(X) \
    X(SYNTAX)                    \
    X(TYPEDEFS)                  \
    X(BYTECODE)

//  NAMESPACES  //

namespace Talos::Module {

    /// @brief Available Printing Dumps.
    $_XX_ENUM_CLASS(Dump, uint8_t, TALOS_XX_MODULE_DUMPS);

    /// @brief Available Module Phases.
    $_XX_ENUM_CLASS(Phase, uint8_t, TALOS_XX_MODULE_PHASES);

}  // namespace Talos::Module

#endif
