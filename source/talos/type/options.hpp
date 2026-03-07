#ifndef _TALOS_TYPE_OPTIONS_HPP
#define _TALOS_TYPE_OPTIONS_HPP

/// Talos Modules
#include "talos/diagnostic/reporter.hpp"
#include "talos/forward/type.hpp"

namespace Talos::Type {

    /// @brief Type Options.
    struct Options {
        XI::Container* services = nullptr;
        Diagnostic::Reporter* reporter = nullptr;
    };

}  // namespace Talos::Type

#endif
