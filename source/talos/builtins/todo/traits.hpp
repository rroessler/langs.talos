#ifndef _TALOS_BUILTINS_TODO_HPP
#define _TALOS_BUILTINS_TODO_HPP

/// Talos Modules
#include "talos/builtins/traits.hpp"

/// Forward Declarations
TALOS_BUILTIN_CUSTOM(Todo)

namespace Talos::Builtins {

    /// @brief Todo Custom Builtin Traits.
    template <>
    struct Traits<Custom::Todo> : public Define<Custom::Todo, "Todo">,
                                  public Features<Adapter::GLOBALS, Adapter::TYPEDEFS> {
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
         * @brief Handles "Todo" panics.
         * @param isolate                   Runtime isolate.
         * @param args                      Native arguments.
         */
        static Value::Any m_panic(Runtime::Isolate* isolate, const Function::Arguments& args);
    };

}  // namespace Talos::Builtins

#endif
