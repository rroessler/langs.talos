#ifndef _TALOS_BUILTINS_ENUM_HPP
#define _TALOS_BUILTINS_ENUM_HPP

/// Talos Modules
#include "talos/builtins/traits.hpp"

namespace Talos::Builtins {

    /// @brief Tagged Enumeration Builtin Traits.
    template <>
    struct Traits<Object::Enum> : public Define<Object::Enum, "Enum">,
                                  public Features<Adapter::FIELDS, Adapter::GLOBALS, Adapter::TYPEDEFS> {
        //  TYPEDEFS  //

        /// @brief Helper for constructing outputs.
        struct Field;
        struct Static;

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
        static Member::View m_attributes(const Object::Enum& self, Value::Symbol symbol);
    };

}  // namespace Talos::Builtins

#endif
