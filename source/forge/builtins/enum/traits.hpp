#ifndef _FORGE_BUILTINS_ENUM_HPP
#define _FORGE_BUILTINS_ENUM_HPP

/// Forge Modules
#include "forge/builtins/traits.hpp"

//  X-MACROS  //

#define FORGE_XX_STATICS_ENUM(X) \
    X(name)                      \
    X(label)                     \
    X(value)

#define FORGE_XX_FIELDS_ENUM(X)

//  NAMESPACES  //

namespace Forge::Builtins {

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

}  // namespace Forge::Builtins

#endif
