#ifndef _FORGE_BUILTINS_OBJECT_HPP
#define _FORGE_BUILTINS_OBJECT_HPP

/// Forge Modules
#include "forge/builtins/traits.hpp"
#include "forge/object/instance.hpp"

//  X-MACROS  //

#define FORGE_XX_STATICS_OBJECT(X)
#define FORGE_XX_FIELDS_OBJECT(X)

//  NAMESPACES  //

namespace Forge::Builtins {

    /// @brief Instance Builtin Traits.
    template <>
    struct Traits<Object::Instance> : public Define<Object::Instance, "Object">,
                                      public Features<Adapter::FIELDS, Adapter::GLOBALS, Adapter::TYPEDEFS> {
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
         * @brief Handles looking up instance fields.
         * @param self                      Object instance.
         * @param symbol                    Field symbol.
         */
        static Member::View m_attributes(const Object::Instance& self, Value::Symbol symbol);
    };

    /// @brief Object Builtin Traits.
    template <>
    struct Traits<Object::Any> : public Traits<Object::Instance> {};

}  // namespace Forge::Builtins

#endif
