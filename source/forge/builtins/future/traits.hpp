#ifndef _FORGE_BUILTINS_FUTURE_HPP
#define _FORGE_BUILTINS_FUTURE_HPP

/// Forge Modules
#include "forge/async/future.hpp"
#include "forge/builtins/traits.hpp"

//  X-MACROS  //

#define FORGE_XX_STATICS_FUTURE(X) \
    X(async)                       \
    X(delay)                       \
    X(resolve)                     \
    X(reject)

#define FORGE_XX_FIELDS_FUTURE(X) \
    X(then)                       \
    X(fails)                      \
    X(await)                      \
    X(state)

//  NAMESPACES  //

namespace Forge::Builtins {

    /// @brief Tagged Future Builtin Traits.
    template <>
    struct Traits<Async::Future> : public Define<Async::Future, "Future">,
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

        /// @brief Gets the underlying "Future" instance typing.
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
        static Member::View m_attributes(const Async::Future& self, Value::Symbol symbol);
    };

}  // namespace Forge::Builtins

#endif
