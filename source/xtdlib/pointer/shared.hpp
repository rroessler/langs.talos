#ifndef _XTDLIB_POINTER_SHARED_HPP
#define _XTDLIB_POINTER_SHARED_HPP

/// C++ Modules
#include <memory>

/// Library Modules
#include "xtdlib/macros/attributes.hpp"

namespace $::Ptr {

    /// @brief Encompasses a shared pointer.
    template <class T>
    using Shared = std::shared_ptr<T>;

    /// @brief Handles making variables castable privately.
    template <class T>
    class $_ABSTRACT Castable : public std::enable_shared_from_this<Castable<T>> {
        //  TYPEDEFS  //

        /// @brief Hide all the internally used methods.
        using std::enable_shared_from_this<Castable<T>>::enable_shared_from_this;
        using std::enable_shared_from_this<Castable<T>>::weak_from_this;
        using std::enable_shared_from_this<Castable<T>>::shared_from_this;

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles safely casting to another shared-pointer.
        template <std::derived_from<T> U>
        inline constexpr Shared<U> m_as() noexcept {
            return std::static_pointer_cast<U>(m_self());
        }

        /// @brief Handles safely casting to another shared-pointer.
        template <std::derived_from<T> U>
        inline constexpr Shared<const U> m_as() const noexcept {
            return std::static_pointer_cast<const U>(m_self());
        }

        /// @brief Allows getting the self value.
        inline constexpr Shared<Castable<T>> m_self() { return shared_from_this(); }
        inline constexpr Shared<const Castable<T>> m_self() const { return shared_from_this(); }
    };

}  // namespace $::Ptr

#endif
