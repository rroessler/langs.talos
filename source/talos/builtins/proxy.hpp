#ifndef _TALOS_BUILTINS_PROXY_HPP
#define _TALOS_BUILTINS_PROXY_HPP

/// Talos Modules
#include "talos/builtins/traits.hpp"
#include "talos/forward/globals.hpp"
#include "talos/value/symbol.hpp"

namespace Talos::Builtins {

    /// @brief Exposes Builtin Functionality.
    template <class T>
    struct Proxy : public Traits<T> {
        //  TYPEDEFS  //

        /// @brief Allow service internal access.
        friend class Service;

        /// @brief Allow globals internal access.
        friend class Globals::Service;

        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructors.
        using Traits<T>::Traits;

        //  PUBLIC METHODS  //

        /**
         * @brief Handles field attributes lookup.
         * @param value                 Parent value.
         * @param symbol                Field symbol.
         */
        static inline constexpr Member::View attribute(const T& value, Value::Symbol symbol) {
            if constexpr (Traits<T>::template uses<Adapter::FIELDS>()) return Traits<T>::m_attributes(value, symbol);
            else return nullptr;
        }

        /**
         * @brief Handles operator attributes lookup.
         * @param value                 Parent value.
         * @param kind                  Operator kind.
         */
        static inline constexpr Member::View attribute(const T& value, Operator::Kind kind) {
            if constexpr (Traits<T>::template uses<Adapter::OPERATORS>()) return Traits<T>::m_attributes(value, kind);
            else return nullptr;
        }

       private:
        //  PRIVATE METHODS  //

        /// @brief Gets the underlying globals factory for use.
        static inline constexpr Globals::Factory m_globals() {
            if constexpr (Traits<T>::template uses<Adapter::GLOBALS>()) return Traits<T>::m_globals;
            else return nullptr;  // cannot emplace this globals instance at all
        }

        /**
         * @brief Handles emplacing types onto the global world.
         * @param globals                       Global types.
         */
        static inline constexpr void m_typedefs(Type::World* globals) {
            if constexpr (Traits<T>::template uses<Adapter::TYPEDEFS>()) return Traits<T>::m_typedefs(globals);
        }
    };

}  // namespace Talos::Builtins

#endif
