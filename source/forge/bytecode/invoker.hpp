#ifndef _FORGE_BYTECODE_INVOKER_HPP
#define _FORGE_BYTECODE_INVOKER_HPP

/// Forge Modules
#include "forge/bytecode/allocator.hpp"

/// Syntax Modules
#include "forge/syntax/expression/accessor.hpp"
#include "forge/syntax/expression/caret.hpp"
#include "forge/syntax/expression/group.hpp"
#include "forge/syntax/expression/typed.hpp"
#include "forge/syntax/literal/identifier.hpp"

namespace Forge::Bytecode {

    /// @brief Available Call-Site Conventions
    enum class Convention : uint8_t { VOID, INLINE, FIELD };

    /// @brief Handles Call Invocations.
    class Invoker {
        //  TYPEDEFS  //

        /// @brief Potential Classification Typing.
        using Classification = std::pair<Convention, const Syntax::Expression*>;

        //  PROPERTIES  //

        /// @brief The convention to be used.
        Convention m_convention = Convention::VOID;

        /// @brief The associated callee to be used.
        const Syntax::Expression* m_callee = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a suitable call-invocation.
        explicit Invoker() = default;

        /**
         * @brief Constructs a expression based invocation.
         * @param callee            Callee to classify.
         */
        explicit Invoker(const Syntax::Expression* callee) : Invoker(m_classify(callee)) {}
        explicit Invoker(const Classification& classification) :
            m_convention(classification.first), m_callee(classification.second) {}

        //  PUBLIC METHODS  //

        inline constexpr Convention convention() const noexcept { return m_convention; }
        inline constexpr const Syntax::Expression* callee() const noexcept { return m_callee; }

        /// @brief Denotes if the invocation is inlinable.
        inline constexpr bool inlined(bool async = false) const noexcept {
            return m_convention == Convention::INLINE && !async;
        }

        /**
         * @brief Handles running the invocation.
         * @param compiler          Bytecode compiler.
         * @param destination       Destination register.
         * @param arguments         Call arguments.
         */
        void invoke(Compiler* compiler, Destination destination,
            const std::vector<Syntax::Expression*>& arguments = {}) const noexcept;

        /**
         * @brief Handles running the asynchronous invocation.
         * @param compiler          Bytecode compiler.
         * @param destination       Destination register.
         * @param arguments         Call arguments.
         */
        void spawn(Compiler* compiler, Destination destination,
            const std::vector<Syntax::Expression*>& arguments = {}) const noexcept;

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles preparing an invocation.
         * @param compiler          Bytecode compiler.
         * @param destination       Destination register.
         * @param arguments         Call arguments.
         * @param async             Asynchronous flag.
         */
        Register::List m_prepare(Compiler* compiler, Destination& destination,
            const std::vector<Syntax::Expression*>& arguments = {}, bool async = false) const noexcept;

        /**
         * @brief Handles emitting synchronous invocation.
         * @param compiler          Byecode compiler.
         * @param destination       Destination register.
         * @param span              Optional arguments span.
         */
        void m_invoke(Compiler* compiler, Destination destination) const noexcept;
        void m_invoke(Compiler* compiler, Destination destination, const Register::Span& span) const noexcept;

        /**
         * @brief Handles emitting asynchronous invocations.
         * @param compiler          Byecode compiler.
         * @param destination       Destination register.
         * @param span              Optional arguments span.
         */
        void m_spawn(Compiler* compiler, Destination destination) const noexcept;
        void m_spawn(Compiler* compiler, Destination destination, const Register::Span& span) const noexcept;

        /**
         * @brief Handles classifying the invocation.
         * @param callee            Callee to classify.
         */
        static inline constexpr Classification m_classify(const Syntax::Expression* callee) {
            switch (callee->traits()->tag()) {
                case $::RTTI::Hash<Syntax::Caret>(): return { Convention::INLINE, callee };
                case $::RTTI::Hash<Syntax::Accessor>(): return { Convention::FIELD, callee };
                case $::RTTI::Hash<Syntax::Group>(): return m_classify(callee->as<Syntax::Group>()->value());
                case $::RTTI::Hash<Syntax::Typed>(): return m_classify(callee->as<Syntax::Typed>()->value());

                // stop for normal conventions to be found
                default: return { Convention::VOID, callee };
            }
        }
    };

}  // namespace Forge::Bytecode

#endif
