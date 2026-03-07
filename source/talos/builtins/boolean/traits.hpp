#ifndef _TALOS_BUILTINS_BOOLEAN_HPP
#define _TALOS_BUILTINS_BOOLEAN_HPP

/// Talos Modules
#include "talos/builtins/traits.hpp"
#include "talos/value/boolean.hpp"

//  X-MACROS  //

#define TALOS_XX_STATICS_BOOLEAN(X) \
    X(parse)                        \
    X(from)

#define TALOS_XX_FIELDS_BOOLEAN(X)

//  NAMESPACES  //

namespace Talos::Builtins {

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

}  // namespace Talos::Builtins

#endif
