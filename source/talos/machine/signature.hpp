#ifndef _TALOS_MACHINE_SIGNATURE_HPP
#define _TALOS_MACHINE_SIGNATURE_HPP

/// Talos Modules
#include "talos/forward/machine.hpp"
#include "talos/value/common.hpp"

namespace Talos::Machine {

    /// @brief Function Signature Template.
    template <class... As, class... Ts>
    inline constexpr XASM::Function::Signature Signature(Ts&&... args) {
        return XASM::Function::Build<Reference, Runtime::Isolate*, const Function::Arguments&, As..., Ts...>(
            std::forward<Ts>(args)...);
    }

    /// @brief Function Signature Template.
    template <class... As, class... Ts>
    inline constexpr XASM::Function::Node* Signature(Compiler* compiler, Ts&&... args) {
        return XASM::Function::Build<Reference, Runtime::Isolate*, const Function::Arguments&, As..., Ts...>(
            compiler, std::forward<Ts>(args)...);
    }

}  // namespace Talos::Machine

#endif
