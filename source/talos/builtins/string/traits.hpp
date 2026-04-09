#ifndef _TALOS_BUILTINS_STRING_HPP
#define _TALOS_BUILTINS_STRING_HPP

/// Talos Modules
#include "talos/builtins/traits.hpp"
#include "talos/string/large.hpp"
#include "talos/string/small.hpp"

namespace Talos::Builtins {

    /// @brief Any String Builtin Traits.
    template <>
    struct Traits<String::Dynamic>
        : public Define<String::Dynamic, "String">,
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
        static Operator::Storage<String::Dynamic> m_operators;

       public:
        //  PUBLIC METHODS  //

        /// @brief Gets the underlying "String" typing.
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
        static Member::View m_attributes(const String::Dynamic& self, Value::Symbol symbol);

        /**
         * @brief Handles looking up operator fields.
         * @param self                      Self value.
         * @param kind                      Operator kind.
         */
        static Member::View m_attributes(const String::Dynamic& self, Operator::Kind kind);
    };

    /// @brief Small String Builtin Traits.
    template <>
    struct Traits<String::Small> : public Traits<String::Dynamic> {};

    /// @brief Large String Builtin Traits.
    template <>
    struct Traits<String::Large> : public Traits<String::Dynamic> {};

}  // namespace Talos::Builtins

#endif
