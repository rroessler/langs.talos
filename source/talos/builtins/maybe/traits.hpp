#ifndef _TALOS_BUILTINS_MAYBE_HPP
#define _TALOS_BUILTINS_MAYBE_HPP

/// Talos Modules
#include "talos/builtins/traits.hpp"

/// Forward Declarations
TALOS_BUILTIN_CUSTOM(Maybe)

namespace Talos::Builtins {

    /// @brief Maybe Custom Builtin Traits.
    template <>
    struct Traits<Custom::Maybe> : public Define<Custom::Maybe, "Maybe">, public Features<Adapter::TYPEDEFS> {
        //  PUBLIC METHODS  //

        /// @brief Gets the underlying "Maybe" typing.
        static Type::Erased typing();

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Allows instantiating global types.
         * @param globals                   Global type-world.
         */
        static void m_typedefs(Type::World* globals);
    };

}  // namespace Talos::Builtins

#endif
