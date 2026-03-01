#ifndef _XASM_COMPILER_SCOPE_HPP
#define _XASM_COMPILER_SCOPE_HPP

/// XASM Modules
#include "xasm/forward/compiler.hpp"
#include "xasm/forward/runtime.hpp"

namespace XASM::Compiler {

    /// @brief Unviversal Compiler Wrapper.
    template <class T>
    class Typed : public asmjit::ujit::UniCompiler {
        //  TYPDEFS  //

        /// @brief Allow scopes internal access.
        template <class>
        friend class Scope;

        //  PROPERTIES  //

        /// @brief The underlying arena.
        Arena* m_arena = nullptr;

        /// @brief The bound runtime target.
        Runtime::Target* m_target = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a universal compiler.
         * @param target            Target runtime.
         * @param arena             Arena code holder.
         * @param backend           Backend compiler.
         */
        explicit Typed(Runtime::Target* target, Arena* arena, Backend* backend) :
            UniCompiler(backend, target->_cpu_features, target->_cpu_hints), m_arena(arena), m_target(target) {}

        //  PUBLIC METHODS  //

        /// @brief Handles safely finalizing functions.
        T finish() {
            // prepare the output functor
            T functor = {};

            // attempt finalizing the incoming callback
            $_EXPECT(end_func() == asmjit::Error::kOk);
            $_EXPECT(finalize() == asmjit::Error::kOk);
            $_EXPECT(m_target->add(&functor, m_arena) == asmjit::Error::kOk);

            // and finally declare as a success
            return m_arena->reset(), functor;
        }
    };

    /// @brief Compilation Scoping.
    template <class T>
    class Scope {
        //  PROPERTIES  //

        /// @brief The compiler interface.
        $::Ptr::Unique<Typed<T>> m_compiler = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a scoped compiler.
         * @param target                Runtime target.
         * @param arena                 Code holder.
         * @param backend               Backend compiler.
         * @param logger                Logger to bind.
         */
        explicit Scope(Runtime::Target* target, Arena* arena, Backend* backend, Runtime::Logger* logger = nullptr) :
            m_compiler($::New().unique<Typed<T>>(target, arena, backend)) {
            arena->reset();  // reset code buffer
            arena->init(target->environment());
            arena->attach(backend);  // bind cc

            // update the incoming logger as necessary now
            if (logger) logger->clear(), arena->set_logger(logger);
        }

        /// @brief Ensure the arena is cleared on completion.
        ~Scope() { m_compiler->m_arena->reset(); }

        //  OPERATOR METHODS  //

        /// @brief Gets the underlying universal compiler.
        inline constexpr Typed<T>* operator&() const noexcept { return m_compiler.get(); }

        /// @brief Gets the underlying universal compiler.
        inline constexpr Typed<T>* operator->() const noexcept { return m_compiler.get(); }
    };

}  // namespace XASM::Compiler

#endif
