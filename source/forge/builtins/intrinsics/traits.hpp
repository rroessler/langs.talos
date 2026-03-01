#ifndef _FORGE_BUILTINS_INTRINSICS_HPP
#define _FORGE_BUILTINS_INTRINSICS_HPP

/// Forge Modules
#include "forge/builtins/traits.hpp"

/// Forward Declarations
FORGE_BUILTIN_CUSTOM(Intrinsics)

namespace Forge::Builtins {

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

}  // namespace Forge::Builtins

#endif
