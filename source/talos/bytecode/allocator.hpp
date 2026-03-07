#ifndef _TALOS_BYTECODE_ALLOCATOR_HPP
#define _TALOS_BYTECODE_ALLOCATOR_HPP

/// Talos Modules
#include "talos/engine/register.hpp"

namespace Talos::Bytecode {

    /// @brief Expose registers here.
    using Register = Engine::Register;
    using Destination = Engine::Register;
    using Accumulator = Engine::Accumulator;

    /// @brief Simple Contiguous Register Alloctor.
    class Allocator {
        //  TYPEDEFS  //

        friend class Register::List;
        friend class Register::Scoped;

        //  PROPERTIES  //

        Register::Encoded m_index = 1;  // Next register index.
        Register::Encoded m_count = 1;  // Current maximum count.

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a simple register allocator.
        explicit constexpr Allocator() = default;

        //  PUBLIC METHODS  //

        inline constexpr Accumulator accumulator() { return Accumulator(); }
        inline constexpr Register::List list() { return Register::List(this); }
        inline constexpr Register::Scoped temporary() { return Register::Scoped(this); }

        inline constexpr Allocator& reset() { return m_index = m_count = 1, *this; }
        inline constexpr Register::Encoded maximum() const noexcept { return m_count; }
        inline constexpr Register allocate() { return m_count = std::max(++m_index, m_count), m_index - 1; }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Releases all registers above an index.
         * @param index                     Register index to delist.
         */
        inline void m_delist(Register::Encoded index) { m_index = index; }

        /**
         * @brief Releases a singular register.
         * @param reg                       Register to release.
         */
        inline void m_release($_UNUSED Register reg) {
            $_ASSERT(m_index - 1 == reg, "Register release mismatch"), m_index--;
        }
    };

}  // namespace Talos::Bytecode

#endif
