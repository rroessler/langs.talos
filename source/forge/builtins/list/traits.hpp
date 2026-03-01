#ifndef _FORGE_BUILTINS_LIST_HPP
#define _FORGE_BUILTINS_LIST_HPP

/// Forge Modules
#include "forge/builtins/traits.hpp"
#include "forge/iterable/list.hpp"

//  X-MACROS  //

#define FORGE_XX_STATICS_LIST(X) \
    X(from)                      \
    X(empty)                     \
    X(range)                     \
    X(filled)

#define FORGE_XX_FIELDS_LIST(X, ...) \
    X(size)                          \
    X(empty)                         \
                                     \
    X(front)                         \
    X(back)                          \
                                     \
    X(get)                           \
    X(set)                           \
                                     \
    X(map)                           \
    X(fold)                          \
    X(erase)                         \
    X(slice)                         \
    X(filter)                        \
    X(reverse)                       \
                                     \
    X(push_front)                    \
    X(push_back)                     \
    X(pop_front)                     \
    X(pop_back)                      \
                                     \
    X(first_index_of)                \
    X(last_index_of)

//  NAMESPACES  //

namespace Forge::Builtins {

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

}  // namespace Forge::Builtins

#endif
