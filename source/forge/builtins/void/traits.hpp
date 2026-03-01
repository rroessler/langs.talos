#ifndef _FORGE_BUILTINS_VOID_HPP
#define _FORGE_BUILTINS_VOID_HPP

/// Forge Modules
#include "forge/builtins/traits.hpp"
#include "forge/value/void.hpp"

//  X-MACROS  //

#define FORGE_XX_STATICS_VOID(X)
#define FORGE_XX_FIELDS_VOID(X)

//  NAMESPACES  //

namespace Forge::Builtins {

    /// @brief Void Builtin Traits.
    template <>
    struct Traits<Value::Void> : public Define<Value::Void, "Void">,
                                 public Features<Adapter::GLOBALS, Adapter::TYPEDEFS> {
        //  PUBLIC METHODS  //

        /// @brief Gets the underlying "Void" typing.
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
