#ifndef _TALOS_DYLIB_PROXY_HPP
#define _TALOS_DYLIB_PROXY_HPP

/// Talos Modules
#include "talos/dylib/addon.hpp"

namespace Talos::Dylib {

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

}  // namespace Talos::Dylib

#endif
