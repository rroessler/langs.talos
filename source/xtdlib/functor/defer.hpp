#ifndef _XTDLIB_FUNCTOR_DEFER_HPP
#define _XTDLIB_FUNCTOR_DEFER_HPP

/// C++ Modules
#include <utility>

namespace $::Functor {

    /// @brief Deferrence Function.
    template <class F>
    class Defer {
        //  PROPERTIES  //

        /// @brief Underlying cleanup function.
        F m_cleanup;

       public:
        //  CONSTRUCTORS  //

        /// @brief Do not allow copying/moving.
        constexpr Defer(Defer&&) = delete;
        constexpr Defer(const Defer&) = delete;

        /**
         * @brief Constructs a suitable deference handler.
         * @param cleanup                   Cleanup function.
         */
        template <class T>
        constexpr Defer(T&& cleanup) : m_cleanup(std::forward<T>(cleanup)) {}

        /// @brief Handles cleaning up a deferred function.
        constexpr ~Defer() { m_cleanup(); }

        //  OPERATOR METHODS  //

        inline constexpr Defer& operator=(Defer&&) = delete;
        inline constexpr Defer& operator=(const Defer&) = delete;
    };

    //  SPECIALIZATIONS  //

    template <class T>
    Defer(T&&) -> Defer<T>;

}  // namespace $::Functor

#endif
