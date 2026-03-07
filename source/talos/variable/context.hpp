#ifndef _TALOS_VARIABLES_CONTEXT_HPP
#define _TALOS_VARIABLES_CONTEXT_HPP

/// Talos Modules
#include "talos/bytecode/allocator.hpp"
#include "talos/variable/upvalues.hpp"

namespace Talos::Variable {

    /// @brief Context Variables Container.
    class Context {
        //  PROPERTIES  //

        /// @brief Handles binding leaked values.
        $::Set<$::String::View> m_leaked = {};

        /// @brief Currently Bound Locals.
        $::Record<Bytecode::Register> m_bound = {};

        /// @brief Previous Variables Instance.
        $::Ptr::Shared<Context> m_ancestor = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a scoped set of variables.
         * @param ancestor              Variables ancestor.
         */
        explicit Context(const $::Ptr::Shared<Context>& ancestor = nullptr) : m_ancestor(ancestor) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the variables ancestor value.
        inline constexpr const $::Ptr::Shared<Context>& ancestor() const noexcept { return m_ancestor; }

        /**
         * @brief Attempts checking if there is a bound local.
         * @param name                  Name of local.
         */
        inline constexpr bool contains(const $::String::View& name) const {
            if (m_bound.contains(name)) return true;
            return m_ancestor ? m_ancestor->contains(name) : false;
        }

        /**
         * @brief Attempts checking if there is a leaked local.
         * @param name                  Name of local.
         */
        inline constexpr bool leaked(const $::String::View& name) const {
            if (m_leaked.contains(name)) return true;
            return m_ancestor ? m_ancestor->leaked(name) : false;
        }

        /**
         * @brief Resolves a local or upper-scoped variable.
         * @param name                  Name of local.
         */
        inline Bytecode::Register resolve(const $::String::View& name) const {
            if (m_bound.contains(name)) return m_bound.at(name);
            return m_ancestor ? m_ancestor->resolve(name) : Bytecode::Register();
        }

        /**
         * @brief Resolves a contextual upvalue.
         * @param name                      Name of upvalue.
         */
        inline Upvalue upvalue(const $::String::View& name) const { return m_upvalue(name); }

        /**
         * @brief Handles declaring a variable.
         * @param name                      Name of variable.
         * @param vreg                      Variable register.
         * @param leaked                    If variable is leaked.
         */
        inline bool declare(const $::String::View& name, const Bytecode::Register& vreg, bool leaked = false) {
            if (leaked) m_leaked.emplace(name);  // emplace
            return m_bound.try_emplace(name, vreg).second;
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles resolving upvalues.
         * @param name                      Name of upvalue.
         * @param depth                     Current depth.
         */
        Upvalue m_upvalue(const $::String::View& name, size_t depth = 0) const;
    };

}  // namespace Talos::Variable

#endif
