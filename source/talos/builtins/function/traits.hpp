#ifndef _TALOS_BUILTINS_FUNCTION_HPP
#define _TALOS_BUILTINS_FUNCTION_HPP

/// Talos Modules
#include "talos/builtins/traits.hpp"
#include "talos/function/closure.hpp"
#include "talos/function/native.hpp"

namespace Talos::Builtins {

    /// @brief Any Function Builtin Traits.
    template <>
    struct Traits<Function::Dynamic> : public Define<Function::Dynamic, "Function">,
                                       public Features<Adapter::FIELDS, Adapter::GLOBALS, Adapter::TYPEDEFS> {
        //  TYPEDEFS  //

        /// @brief Helpers for constructing outputs.
        struct Field;
        struct Static;

       private:
        //  PROPERTIES  //

        /// @brief Available field descriptors.
        static Member::Storage m_members;

       public:
        //  PUBLIC METHODS  //

        /// @brief Gets the underlying "Function" typing.
        static Type::Erased typing();

        /// @brief Gets the glue function information.
        static const Function::Info* binder();

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
        static Member::View m_attributes(const Function::Dynamic& self, Value::Symbol symbol);
    };

    /// @brief Native Builtin Traits.
    template <>
    struct Traits<Function::Native> : public Traits<Function::Dynamic> {};

    /// @brief Jitted Builtin Traits.
    template <>
    struct Traits<Function::Jitted> : public Traits<Function::Dynamic> {};

    /// @brief Closure Builtin Traits.
    template <>
    struct Traits<Function::Closure> : public Traits<Function::Dynamic> {};

}  // namespace Talos::Builtins

#endif
