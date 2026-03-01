#ifndef _FORGE_DYLIB_PROXY_HPP
#define _FORGE_DYLIB_PROXY_HPP

/// Forge Modules
#include "forge/dylib/addon.hpp"

namespace Forge::Dylib {

    /// @brief Name String Literal.
    template <size_t N>
    using Name = $::String::Literal<N>;

    /// @brief Library Proxy Container.
    template <Name N>
    struct $_ABSTRACT Proxy {
        //  TYPEDEFS  //

        /// @brief Allow the registry internal access.
        friend class Registry;

        //  CONSTRUCTORS  //

        /// @brief Default proxy constructor.
        constexpr Proxy() = default;

       protected:
        //  PRIVATE METHODS  //

        /// @brief Gets the name of the addon.
        static inline constexpr $::String::View m_name() noexcept { return N.view(); }
    };

}  // namespace Forge::Dylib

#endif
