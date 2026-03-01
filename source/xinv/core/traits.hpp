#ifndef _XINV_CORE_TRAITS_HPP
#define _XINV_CORE_TRAITS_HPP

/// XINV Modules
#include "xinv/core/service.hpp"

namespace XI::Traits {

    /// @brief Allows introspection of services.
    template <std::derived_from<Service> T>
    struct Transient : public T {
        //  TYPEDEFS  //

        /// @brief Gets the baseline-typing.
        using Base = T::Base;
    };

    /// @brief Handles inferring base-types.
    template <std::derived_from<Service> T>
    using Infer = typename Traits::Transient<T>::Base;

    /// @brief Ensures a type is base-like.
    template <class T>
    concept Abstract = $::Traits::Disjunction<T, Shared, Unique>;

    /// @brief Denotes if a service can be injected onto.
    template <class T, class... As>
    concept Injectable = std::constructible_from<T, Container*, As...>;

}  // namespace XI::Traits

#endif
