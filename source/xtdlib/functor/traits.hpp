#ifndef _XTDLIB_FUNCTOR_TRAITS_HPP
#define _XTDLIB_FUNCTOR_TRAITS_HPP

/// C++ Includes
#include <cstddef>
#include <tuple>

namespace $::Functor {

    /// @brief Allows delegating functor traits.
    template <class T>
    struct Details : public Details<decltype(&T::operator())> {};

    /// @brief Contains functor traits.
    template <class R, class... As>
    struct Details<R(As...)> {
        //  TYPEDEFS  //

        /// @brief The return typing of the functor.
        using Returns = R;

        /// @brief An aliased lambda typing.
        using Lambda = R(As...);

        /// @brief An aliased pointer typing.
        using Pointer = R (*)(As...);

        /// @brief The expected arity of the functor.
        enum { Arity = sizeof...(As) };

        /// @brief Allows getting the available arguments.
        struct Parameters {
            //  TYPEDEFS  //

            /// @brief A tuple list of parameters
            using List = std::tuple<As...>;

            /// @brief Allows getting a parameter.
            template <size_t N>
            using Nth = typename std::tuple_element_t<N, List>;
        };
    };

    /// @brief Gets functor return-types.
    template <class T>
    using Returns = typename Details<T>::Returns;

    /// @brief Gets functor parameters.
    template <class T>
    using Parameters = typename Details<T>::Parameters;

}  // namespace $::Functor

#endif
