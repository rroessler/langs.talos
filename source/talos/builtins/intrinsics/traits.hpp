#ifndef _TALOS_BUILTINS_INTRINSICS_HPP
#define _TALOS_BUILTINS_INTRINSICS_HPP

/// Talos Modules
#include "talos/builtins/traits.hpp"

/// Forward Declarations
TALOS_BUILTIN_CUSTOM(Intrinsics)

namespace Talos::Builtins {

    /// @brief Void Builtin Traits.
    template <>
    struct Traits<Custom::Intrinsics> : public Define<Custom::Intrinsics, "Intrinsics">,
                                        public Features<Adapter::TYPEDEFS> {
       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Defines the underlying global types.
         * @param globals                   Type world.
         */
        static void m_typedefs(Type::World* globals);
    };

}  // namespace Talos::Builtins

#endif
