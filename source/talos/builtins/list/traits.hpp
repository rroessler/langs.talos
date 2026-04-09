#ifndef _TALOS_BUILTINS_LIST_HPP
#define _TALOS_BUILTINS_LIST_HPP

/// Talos Modules
#include "talos/builtins/traits.hpp"
#include "talos/iterable/list.hpp"

namespace Talos::Builtins {

    /// @brief Tagged List Builtin Traits.
    template <>
    struct Traits<Iterable::List>
        : public Define<Iterable::List, "List">,
          public Features<Adapter::FIELDS, Adapter::GLOBALS, Adapter::OPERATORS, Adapter::TYPEDEFS> {
        //  TYPEDEFS  //

        /// @brief Helpers for constructing outputs.
        struct Apply;
        struct Field;
        struct Static;

       private:
        //  PROPERTIES  //

        /// @brief Available field descriptors.
        static Member::Storage m_members;

        /// @brief Available operator descriptors.
        static Operator::Storage<Iterable::List> m_operators;

       public:
        //  PUBLIC METHODS  //

        /// @brief Gets the underlying "List" instance typing.
        static Type::Erased typing();

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Allows instantiating global types.
         * @param globals                   Global type-world.
         */
        static void m_typedefs(Type::World* globals);

        /**
         * @brief Handles instantiating globals.
         * @param isolate                   Runtime isolate.
         */
        static Value::Any m_globals(Runtime::Isolate* isolate);

        /**
         * @brief Handles looking up value fields.
         * @param self                      Self value.
         * @param symbol                    Field symbol.
         */
        static Member::View m_attributes(const Iterable::List& self, Value::Symbol symbol);

        /**
         * @brief Handles looking up operator fields.
         * @param self                      Self value.
         * @param kind                      Operator kind.
         */
        static Member::View m_attributes(const Iterable::List& self, Operator::Kind kind);
    };

}  // namespace Talos::Builtins

#endif
