#ifndef _FORGE_MACHINE_SIGNATURE_HPP
#define _FORGE_MACHINE_SIGNATURE_HPP

/// Forge Modules
#include "forge/forward/machine.hpp"
#include "forge/value/common.hpp"

namespace Forge::Machine {

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

}  // namespace Forge::Machine

#endif
