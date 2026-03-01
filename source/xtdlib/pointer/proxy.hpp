#ifndef _XTDLIB_POINTER_PROXY_HPP
#define _XTDLIB_POINTER_PROXY_HPP

/// C++ Modules
#include <concepts>
#include <type_traits>
#include <utility>

namespace $::Ptr {

    /// @brief Allows internal access to types.
    template <class T>
    struct Proxy : public T {
        //  CONSTRUCTORS  //

        /// @brief Exposes pointer construction when necessary.
        template <class... As>
        explicit constexpr Proxy(As&&... args) : T(std::forward<As>(args)...) {}
    };

    /// @brief Ensures valid construction details.
    template <class T, class... As>
    concept Ensure = std::constructible_from<Proxy<T>, As...>;

    /// @brief Infers a pointers necessary constructor typing.
    template <class T, class... As>
    using Infer = std::conditional_t<std::is_constructible_v<T, As...>, T, Proxy<T>>;

}  // namespace $::Ptr

#endif
