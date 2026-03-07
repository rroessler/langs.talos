#ifndef _TALOS_BUILTINS_SYMBOL_HPP
#define _TALOS_BUILTINS_SYMBOL_HPP

/// Talos Modules
#include "talos/builtins/traits.hpp"
#include "talos/value/symbol.hpp"

//  X-MACROS  //

#define TALOS_XX_STATICS_SYMBOL(X) X(from)
#define TALOS_XX_FIELDS_SYMBOL(X) X(hash)

//  NAMESPACES  //

namespace Talos::Builtins {

    /// @brief Tagged Symbol Builtin Traits.
    template <>
    struct Traits<Value::Symbol> : public Define<Value::Symbol, "Symbol">,
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

        /// @brief Gets the underlying "Symbol" typing.
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
         * @brief Handles looking up value fields.
         * @param self                      Self value.
         * @param symbol                    Field symbol.
         */
        static Member::View m_attributes(const Value::Symbol& self, Value::Symbol symbol);
    };

}  // namespace Talos::Builtins

#endif
