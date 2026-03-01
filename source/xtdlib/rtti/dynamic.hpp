#ifndef _XTDLIB_RTTI_DYNAMIC_HPP
#define _XTDLIB_RTTI_DYNAMIC_HPP

/// Library Modules
#include "xtdlib/rtti/hash.hpp"

namespace $::RTTI {

    /// @brief Dynamic Base Class.
    struct $_ABSTRACT Dynamic {
        //  CONSTRUCTORS  //

        /// @brief Abstract Destructor.
        virtual ~Dynamic() = default;

        //  PUBLIC METHODS  //

        /// @brief Checks if other types are equal to this one.
        template <class... As>
        $_INLINE_PERF constexpr bool is() const noexcept {
            return (m_is(Hash<As>()) || ...);
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles checking individual tags.
         * @param tag                   Tag to compare.
         */
        $_INLINE_PERF virtual constexpr bool m_is($_UNUSED Tag tag) const noexcept { return false; }
    };

    /// @brief Dynamic Inheritance Abstraction.
    template <class T, std::derived_from<Dynamic> B>
    struct Extends : public B {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base class details.
        using B::B;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Allows extending against multiple variants.
         * @param tag                   Tag to compare.
         */
        $_INLINE_PERF virtual constexpr bool m_is(Tag tag) const noexcept override {
            return tag == Hash<T>() || B::m_is(tag);  // allow inheritance queries
        }
    };

    /**
     * @brief Forces a dynamic assertion.
     * @param dynamic                   Dynamic value to assert.
     */
    template <std::derived_from<Dynamic> T>
    $_INLINE_PERF static constexpr void Assert($_UNUSED const Dynamic* dynamic) {
        $_ASSERT(dynamic->is<T>(), "Value is not of type '{0}'", Name::of<T>());
    }

}  // namespace $::RTTI

#endif
