#ifndef _FORGE_BUILTINS_DEBUG_HPP
#define _FORGE_BUILTINS_DEBUG_HPP

/// Forge Modules
#include "forge/builtins/traits.hpp"

/// Forward Declarations
FORGE_BUILTIN_CUSTOM(Debug)

//  X-MACROS  //

#define FORGE_XX_FIELDS_DEBUG(X, ...) \
    X(print)                          \
    X(eprint)                         \
    X(println)                        \
    X(eprintln)

//  NAMESPACES  //

namespace Forge::Builtins {

    /// @brief Void Builtin Traits.
    template <>
    struct Traits<Custom::Debug> : public Define<Custom::Debug, "Debug">,
                                   public Features<Adapter::GLOBALS, Adapter::TYPEDEFS> {
        //  TYPEDEFS  //

        /// @brief Helper for constructing outputs.
        struct Field;

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
