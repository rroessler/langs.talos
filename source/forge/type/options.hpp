#ifndef _FORGE_TYPE_OPTIONS_HPP
#define _FORGE_TYPE_OPTIONS_HPP

/// Forge Modules
#include "forge/diagnostic/reporter.hpp"
#include "forge/forward/type.hpp"

namespace Forge::Type {

    /// @brief Type Options.
    struct Options {
        XI::Container* services = nullptr;
        Diagnostic::Reporter* reporter = nullptr;
    };

}  // namespace Forge::Type

#endif
