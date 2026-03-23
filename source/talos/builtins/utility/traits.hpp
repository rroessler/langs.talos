#ifndef _TALOS_BUILTINS_UTILITY_HPP
#define _TALOS_BUILTINS_UTILITY_HPP

/// Talos Modules
#include "talos/builtins/traits.hpp"

/// Forward Declarations
TALOS_BUILTIN_CUSTOM(Utility)

namespace Talos::Builtins {

    /// @brief Utility Custom Builtin Traits.
    template <>
    struct Traits<Custom::Utility> : public Define<Custom::Utility, "Utility">, public Features<Adapter::TYPEDEFS> {
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
