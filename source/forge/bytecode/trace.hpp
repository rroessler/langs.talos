#ifndef _FORGE_BYTECODE_TRACE_HPP
#define _FORGE_BYTECODE_TRACE_HPP

/// C++ Modules
#include <stack>

/// Forge Modules
#include "forge/forward/bytecode.hpp"
#include "forge/linker/records.hpp"

namespace Forge::Bytecode {

    /// @brief Bytecode Source Trace.
    struct Trace {
        //  TYPEDEFS  //

        /// @brief Stack of traces.
        using Stack = std::stack<Linker::Position>;

       private:
        //  PROPERTIES  //

        /// @brief Compilation stack.
        Stack* m_stack = nullptr;

        /// @brief Bound trace position.
        Linker::Position m_position = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs an empty trace.
        explicit constexpr Trace() = default;

        /**
         * @brief Constructs a bytecode-trace.
         * @param stack             Stack to append to.
         * @param position          Current position.
         */
        explicit constexpr Trace(Stack* stack, const Linker::Position& position = {}) :
            m_stack(stack), m_position(position) {
            if (valid()) m_stack->push(m_position);
        }

        /// @brief Handles removing the trace instance.
        constexpr ~Trace() {
            if (valid()) $_ASSERT(m_stack->top() == m_position), m_stack->pop();
        }

        //  PUBLIC METHODS  //

        inline constexpr const Linker::Position& position() const noexcept { return m_position; }
        inline constexpr bool valid() const noexcept { return m_stack && m_position != Linker::Position(); }
    };

}  // namespace Forge::Bytecode

#endif
