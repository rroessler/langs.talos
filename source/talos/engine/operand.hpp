#ifndef _TALOS_ENGINE_OPERAND_HPP
#define _TALOS_ENGINE_OPERAND_HPP

/// Talos Modules
#include "talos/forward/bytecode.hpp"
#include "talos/forward/engine.hpp"

namespace Talos::Engine {

    /// @brief Engine Operand Definition.
    template <size_t N>
    struct $_ABSTRACT Operand {
        //  TYPEDEFS  //

        /// @brief Allow operands internal access.
        template <class...>
        friend struct Bytecode::Operands;

        //  CONSTRUCTORS  //

        /// @brief Default constructor.
        constexpr Operand() = default;

       private:
        //  PRIVATE METHODS  //

        /// @brief Gets the underlying operand size.
        static inline constexpr uint64_t m_sizeof() noexcept { return N; }
    };

}  // namespace Talos::Engine

#endif
