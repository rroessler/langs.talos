#ifndef _XTDLIB_POINTER_FACTORY_HPP
#define _XTDLIB_POINTER_FACTORY_HPP

/// Library Modules
#include "xtdlib/debug/location.hpp"
#include "xtdlib/pointer/auto.hpp"
#include "xtdlib/pointer/proxy.hpp"
#include "xtdlib/pointer/shared.hpp"
#include "xtdlib/pointer/unique.hpp"
#include "xtdlib/traits/newable.hpp"

namespace $ {

    /// @brief New Factory Interface.
    class New {
        //  PROPERTIES  //

        /// @brief Internally bound location.
        Location m_location;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a new-factory.
         * @param location              Source-location.
         */
        explicit consteval New(const Location& location = Location()) : m_location(location) {}

        //  PUBLIC METHODS  //

        /**
         * @brief Forwards "new" operations for objects.
         * @param args              Arguments to forward.
         * @param location          Constructor location.
         */
        template <class T, class... As>
        inline constexpr T* with(As&&... args) requires Ptr::Ensure<T, As...> {
            using P = typename Ptr::Infer<T>;  // infer the pointers proxy typing to be used
            if constexpr (Traits::Newable<P, Location>) return new (m_location) P(std::forward<As>(args)...);
            else return new P(std::forward<As>(args)...);  // otherwise default to non-tracing here
        }

        /**
         * @brief Constructs a thread-unsafe shared pointer.
         * @param args              Arguments to forward.
         */
        template <class T, class... As>
        inline constexpr Ptr::Auto<T> light(As&&... args) requires Ptr::Ensure<T, As...> {
            using Derived = typename Ptr::Auto<T>::Derived;  // prepare base
            return Ptr::Auto<T>(with<Derived>(std::forward<As>(args)...));
        }

        /**
         * @brief Constructs a move-only unique pointer.
         * @param args              Arguments to forward.
         */
        template <class T, class... As>
        inline constexpr Ptr::Unique<T> unique(As&&... args) requires Ptr::Ensure<T, As...> {
            return Ptr::Unique<T>(with<T>(std::forward<As>(args)...));
        }

        /**
         * @brief Constructs a thread-safe shared pointer.
         * @param args              Arguments to forward.
         */
        template <class T, class... As>
        inline constexpr Ptr::Shared<T> shared(As&&... args) requires Ptr::Ensure<T, As...> {
            return Ptr::Shared<T>(with<T>(std::forward<As>(args)...));
        }
    };

}  // namespace $

#endif
