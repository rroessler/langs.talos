#ifndef _XTDLIB_UTILITY_SINGLETON_HPP
#define _XTDLIB_UTILITY_SINGLETON_HPP

/// C++ Modules
#include <memory>

/// Library Includes
#include "xtdlib/utility/global.hpp"

namespace $ {

    /// @brief Handles instantiating singletons.
    template <class T>
    struct $_ABSTRACT Singleton {
        //  CONSTRUCTORS  //

        /// @brief Default singleton constructor.
        constexpr Singleton() = default;

        /// @brief Do not allow copy-construction.
        constexpr Singleton(const Singleton&) = delete;

        //  OPERATOR METHODS  //

        /// @brief Do not allow copy-assignment.
        constexpr Singleton& operator=(const Singleton&) = delete;

       protected:
        //  PRIVATE METHODS  //

        /// @brief Gets the underlying instance.
        static inline constexpr T* s_instance() { return Global::get<T>(); }
    };

}  // namespace $

#endif
