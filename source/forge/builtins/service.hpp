#ifndef _FORGE_BUILTINS_SERVICE_HPP
#define _FORGE_BUILTINS_SERVICE_HPP

/// Forge Modules
#include "forge/builtins/proxy.hpp"
#include "forge/globals/service.hpp"
#include "forge/type/world.hpp"

namespace Forge::Builtins {

    /// @brief Builtins Service.
    class Service : public XI::Define<Service, XI::Shared> {
        //  PROPERTIES  //

        /// @brief Available globals service.
        Globals::Service* m_globals;

        /// @brief Builtin Types Available.
        $::Ptr::Unique<Type::World> m_types;

       public:
        //  CONSTUCTORS  //

        /**
         * @brief Constructs a builtins service.
         * @param services                  Service container.
         */
        explicit Service();
        explicit Service(XI::Container* services);

        //  PUBLIC METHODS  //

        inline constexpr Type::World* types() const noexcept { return m_types.get(); }
        inline constexpr Globals::Service* globals() const noexcept { return m_globals; }
    };

}  // namespace Forge::Builtins

#endif
