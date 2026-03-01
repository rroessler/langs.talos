#ifndef _FORGE_BUILTINS_NUMBER_HPP
#define _FORGE_BUILTINS_NUMBER_HPP

/// Forge Modules
#include "forge/builtins/traits.hpp"
#include "forge/number/tagged.hpp"

//  X-MACROS  //

#define FORGE_XX_STATICS_NUMBER(X) X(parse)
#define FORGE_XX_FIELDS_NUMBER(X) \
    X(sign)                       \
                                  \
    X(abs)                        \
    X(ceil)                       \
    X(floor)                      \
    X(round)                      \
    X(trunc)                      \
    X(clamp)                      \
                                  \
    X(is_nan)                     \
    X(is_fin)                     \
    X(is_inf)                     \
                                  \
    X(to_precision)               \
    X(to_scientific)

//  NAMESPACES  //

namespace Forge::Builtins {

    /// @brief Tagged Number Builtin Traits.
    template <>
    struct Traits<Number::Tagged> : public Define<Number::Tagged, "Number">,
                                    public Features<Adapter::FIELDS, Adapter::GLOBALS, Adapter::TYPEDEFS> {
        //  TYPEDEFS  //

        /// @brief Helpers for constructing outputs.
        struct Apply;
        struct Field;
        struct Static;

       private:
        //  PROPERTIES  //

        /// @brief Available field descriptors.
        static Member::Storage m_members;

       public:
        //  PUBLIC METHODS  //

        /// @brief Gets the underlying "Number" typing.
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
        static Member::View m_attributes(const Number::Tagged& self, Value::Symbol symbol);
    };

}  // namespace Forge::Builtins

#endif
