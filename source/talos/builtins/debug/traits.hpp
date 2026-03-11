#ifndef _TALOS_BUILTINS_DEBUG_HPP
#define _TALOS_BUILTINS_DEBUG_HPP

/// Talos Modules
#include "talos/builtins/traits.hpp"

/// Forward Declarations
TALOS_BUILTIN_CUSTOM(Debug)

//  X-MACROS  //

#define TALOS_XX_FIELDS_DEBUG(X, ...) \
    X(print)                          \
    X(eprint)                         \
    X(println)                        \
    X(eprintln)                       \
    X(breakpoint)

//  NAMESPACES  //

namespace Talos::Builtins {

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

}  // namespace Talos::Builtins

#endif
