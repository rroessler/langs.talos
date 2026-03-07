#ifndef _TALOS_VALUE_VOID_HPP
#define _TALOS_VALUE_VOID_HPP

/// Talos Includes
#include "talos/value/common.hpp"

namespace Talos::Value {

    //  TYPEDEFS  //

    /// @brief Void Runtime Value.
    struct Void : public Any {
        //  CONSTRUCTORS  //

        /// @brief Constructs a default void-value.
        explicit constexpr Void() : Any(Pointer::Kind::VOID) {}

        /**
         * @brief Constructs a void value with an error.
         * @param feedback              Feedback value.
         */
        constexpr Void(const Feedback& feedback) : Any(m_encode(feedback)) {}

        //  PUBLIC METHODS  //

        /// @brief Denotes if the void value is "okay".
        inline constexpr bool okay() const noexcept { return traits().okay(); }

        /// @brief Gets the underlying error value.
        inline constexpr Feedback feedback() const noexcept { return traits().feedback(); }

        /// @brief Denotes if we have a sentinel value.
        inline constexpr bool sentinel() const noexcept { return feedback() == Feedback::ITERATOR_SENTINEL; }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Validates the value.
         * @param traits                Pointer traits
         */
        static inline constexpr bool m_is(const Pointer::Traits& traits) { return traits.is<Pointer::Kind::VOID>(); }

        /**
         * @brief Get truthiness of a value.
         * @param pointer               Pointer to resolve.
         */
        static inline constexpr bool m_truthiness(const Void&) { return false; }

        /**
         * @brief Handles encoding error values.
         * @param code                  Error code.
         */
        static inline constexpr Pointer::Underlying m_encode(const Feedback& feedback) {
            return (static_cast<uint8_t>(feedback) << Pointer::Shift::FBK) |
                   static_cast<Pointer::Underlying>(Pointer::Kind::VOID);
        }

        /**
         * @brief Handles dumping the runtime value.
         * @param os                    Output stream.
         * @param self                  Value instance.
         */
        static inline void m_print($::Stream::Output& os, const Void& self) {
            os << $::Dye::dim("Void") << $::Dye::dim(self.okay() ? "" : "(EXCEPTION)");
        }
    };

    //  PUBLIC METHODS  //

    static inline constexpr Value::Any Timeout() { return Void(Feedback::ASYNC_TIMEOUT); }
    static inline constexpr Value::Any Missing() { return Void(Feedback::FIELD_MISSING); }
    static inline constexpr Value::Any Failure() { return Void(Feedback::EXCEPTION_THROWN); }
    static inline constexpr Value::Any Sentinel() { return Void(Feedback::ITERATOR_SENTINEL); }

}  // namespace Talos::Value

#endif
