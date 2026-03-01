#ifndef _FORGE_ENGINE_OPERAND_HPP
#define _FORGE_ENGINE_OPERAND_HPP

/// Forge Modules
#include "forge/forward/bytecode.hpp"
#include "forge/forward/engine.hpp"

namespace Forge::Engine {

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

}  // namespace Forge::Engine

#endif
