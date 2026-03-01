#ifndef _FORGE_BUILTINS_BOOLEAN_HPP
#define _FORGE_BUILTINS_BOOLEAN_HPP

/// Forge Modules
#include "forge/builtins/traits.hpp"
#include "forge/value/boolean.hpp"

//  X-MACROS  //

#define FORGE_XX_STATICS_BOOLEAN(X) \
    X(parse)                        \
    X(from)

#define FORGE_XX_FIELDS_BOOLEAN(X)

//  NAMESPACES  //

namespace Forge::Builtins {

    /// @brief Tagged Boolean Builtin Traits.
    template <>
    struct Traits<Value::Boolean> : public Define<Value::Boolean, "Boolean">,
                                    public Features<Adapter::GLOBALS, Adapter::TYPEDEFS> {
        //  TYPEDEFS  //

        /// @brief Helpers for constructing outputs.
        struct Field;
        struct Static;

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying "Boolean" typing.
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
    };

}  // namespace Forge::Builtins

#endif
