#ifndef _FORGE_BUILTINS_RESULT_HPP
#define _FORGE_BUILTINS_RESULT_HPP

/// Forge Modules
#include "forge/builtins/traits.hpp"
#include "forge/monad/result.hpp"

//  X-MACROS  //

#define FORGE_XX_STATICS_RESULT(X) \
    X(wrap)                        \
    X(okay)                        \
    X(error)

#define FORGE_XX_FIELDS_RESULT(X) \
    X(is_okay)                    \
    X(is_error)                   \
                                  \
    X(unwrap_okay)                \
    X(unwrap_error)

//  NAMESPACES  //

namespace Forge::Builtins {

    /// @brief Tagged Result Builtin Traits.
    template <>
    struct Traits<Monad::Result> : public Define<Monad::Result, "Result">,
                                   public Features<Adapter::FIELDS, Adapter::GLOBALS, Adapter::TYPEDEFS> {
        //  TYPEDEFS  //

        /// @brief Helper for constructing outputs.
        struct Field;
        struct Static;

       private:
        //  PROPERTIES  //

        /// @brief Available field descriptors.
        static Member::Storage m_members;

       public:
        //  PUBLIC METHODS  //

        /// @brief Gets the underlying "Result" typing.
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
        static Member::View m_attributes(const Monad::Result& self, Value::Symbol symbol);
    };

}  // namespace Forge::Builtins

#endif
