#ifndef _FORGE_BYTECODE_REQUEST_HPP
#define _FORGE_BYTECODE_REQUEST_HPP

/// C++ Modules
#include <queue>

/// Forge Modules
#include "forge/bytecode/routine.hpp"
#include "forge/variable/context.hpp"

namespace Forge::Bytecode {

    /// @brief Routine Request.
    class Request {
        //  TYPEDEFS  //

        /// @brief Allow the compiler internal access.
        friend class Compiler;

        //  PROPERTIES  //

        /// @brief Bound function instance.
        const Syntax::Lambda* m_function = nullptr;

        /// @brief Routine to compile to.
        $::Ptr::Unique<Routine> m_routine = nullptr;

        /// @brief Allocator for underlying registers.
        $::Ptr::Unique<Allocator> m_registers = nullptr;

        /// @brief Variables reference.
        $::Ptr::Shared<Variable::Context> m_variables = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a compilation request.
         * @param function              Function to compile.
         * @param upvalues              Optional upvalues.
         */
        explicit Request(const Syntax::Lambda* function);
        explicit Request(const Syntax::Lambda* function, const $::Ptr::Shared<Variable::Context>& upvalues);

        //  PUBLIC METHODS  //

        inline constexpr Routine* routine() const noexcept { return m_routine.get(); }
        inline constexpr Allocator* registers() const noexcept { return m_registers.get(); }
        inline constexpr Variable::Context* variables() const noexcept { return m_variables.get(); }

        /// @brief Scopes a new set of variables.
        inline constexpr auto scope() {
            m_variables = $::New().shared<Variable::Context>(m_variables);  // scope
            return $::Functor::Defer([&] { m_variables = m_variables->ancestor(); });
        }
    };

    /// @brief Routine Compilation Queue.
    class Queue {
        //  PROPERTIES  //

        /// @brief Current compilation offset.
        Index m_offset = 0;

        /// @brief Currently queued compilation requests.
        std::queue<$::Ptr::Unique<Request>> m_requests = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a compilation queue.
        explicit Queue() = default;

        //  PUBLIC METHODS  //

        inline constexpr bool empty() const noexcept { return m_requests.empty(); }
        inline constexpr size_t size() const noexcept { return m_requests.size(); }

        /**
         * @brief Handles enqueing functions.
         * @param function                  Function to enqueue.
         * @param upvalues                  Upvalues reference.
         */
        Index enqueue(const Syntax::Lambda* function);
        Index enqueue(const Syntax::Lambda* function, const $::Ptr::Shared<Variable::Context>& upvalues);

        /// @brief Pops the front queue entry.
        $::Ptr::Unique<Request> dequeue() noexcept;
    };

}  // namespace Forge::Bytecode

#endif
