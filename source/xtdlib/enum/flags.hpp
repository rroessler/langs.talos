#ifndef _XTDLIB_ENUM_FLAGS_HPP
#define _XTDLIB_ENUM_FLAGS_HPP

/// C++ Modules
#include <limits>

/// Library Modules
#include "xtdlib/traits/concepts.hpp"

namespace $::Enum {

    /// @brief Enum Flags Container.
    template <class E>
    requires std::is_scoped_enum_v<E> struct Flags {
        //  TYPEDEFS  //

        /// @brief The underlying enumeration typing.
        using Underlying = std::underlying_type_t<E>;

       private:
        //  PROPERTIES  //

        /// @brief The underlying flags value.
        Underlying m_flags = 0;

       public:
        //  CONSTRUCTORS  //

        /// @brief Allow default construction.
        constexpr Flags() = default;

        /**
         * @brief Sets an initial set of flags.
         * @param flags                 Flags to set.
         */
        template <std::convertible_to<E>... Es>
        constexpr Flags(Es&&... flags) {
            if constexpr (sizeof...(Es)) set(std::forward<Es>(flags)...);
        }

        /**
         * @brief Sets the initial set of flags.
         * @param flags                 Flags to set.
         */
        constexpr Flags(Underlying flags) : m_flags(flags) {}

        //  OPERATOR METHODS  //

        friend inline Flags operator|(Underlying left, const Flags& right) { return Flags(left | right.m_flags); }
        friend inline Flags operator|(const Flags& left, Underlying right) { return Flags(left.m_flags | right); }
        friend inline Flags operator|(const Flags& left, const Flags& right) {
            return Flags(left.m_flags | right.m_flags);
        }

        //  PUBLIC METHODS  //

        /// @brief Denotes if no bits have been set.
        inline constexpr bool none() const noexcept { return m_flags == 0; }

        /// @brief Denotes if any bits have been set.
        inline constexpr bool any() const noexcept { return m_flags != 0; }

        /// @brief Denotes if all bits have been set.
        inline constexpr bool all() const noexcept { return m_flags == max(); }

        /// @brief Gets the current underlying value.
        inline constexpr Underlying value() const noexcept { return m_flags; }

        /// @brief Gets the maximum value possible.
        inline constexpr Underlying max() const noexcept { return std::numeric_limits<Underlying>().max(); }

        /// @brief Forcibly sets all underlying bits.
        inline constexpr Flags& set() noexcept { return m_flags = max(), *this; }

        /// @brief Forcibly clears all the underlying bits.
        inline constexpr Flags& clear() noexcept { return m_flags = 0, *this; }

        /**
         * @brief Handles fliping singular bits.
         * @param flag                      Flag to flip.
         * @param state                     Optional state.
         */
        inline constexpr Flags& flip(E flag) { return m_flags ^= 1 << m_nth(flag), *this; }
        inline constexpr Flags& flip(E flag, bool state) {
            return m_flags &= ~(1 << m_nth(flag)), m_flags |= state << m_nth(flag), *this;
        }

        /**
         * @brief Handles setting all the given bits.
         * @param flags                     Flags to set.
         */
        template <std::convertible_to<E>... Es>
        inline constexpr Flags& set(Es&&... flags) noexcept {
            return m_flags |= ((1 << m_nth(flags)) | ...), *this;
        }

        /**
         * @brief Handles clearing all the given bits.
         * @param flags                     Flags to set.
         */
        template <std::convertible_to<E>... Es>
        inline constexpr Flags& clear(Es&&... flags) noexcept {
            return m_flags = ((m_flags & ~(1 << m_nth(flags))) | ...), *this;
        }

        /**
         * @brief Tests if flags are set.
         * @param flags                     Flags to test.
         */
        template <std::convertible_to<E>... Es>
        inline constexpr bool test(Es&&... flags) const noexcept {
            return ((m_flags >> m_nth(flags) & 1) || ...);
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Casts a flag to a bit.
         * @param flag                      Flag to cast.
         */
        inline constexpr Underlying m_nth(E flag) const noexcept { return static_cast<Underlying>(flag); }
    };

}  // namespace $::Enum

#endif
