#ifndef _XTDLIB_SERDE_CODEC_HPP
#define _XTDLIB_SERDE_CODEC_HPP

#include "xtdlib/serde/value.hpp"

namespace $::Serde {

    /// @brief Denotes any passthrough typing for codecs.
    template <class T>
    concept Constructible = Trivial<T> || std::arithmetic<T> || std::is_enum_v<T>;

    /// @brief Serialization Handler.
    template <class T, class... As>
    struct Encoder : public T {
        //  PUBLIC METHODS  //

        /// @brief Denotes an encoder validation.
        static inline constexpr bool validate() {
            return requires(const T& self, As&&... args) {
                { T::m_encode(self, args...) } -> std::convertible_to<Value>;
            };
        };

        /**
         * @brief Handles encoding a value.
         * @param encodable                 Value to encode.
         * @param args                      Additional arguments.
         */
        $_INLINE_PERF static Value encode(const T& encodable, As&&... args) {
            if constexpr (validate()) return T::m_encode(encodable, std::forward<As>(args)...);
            else $_ABORT("Value '{0}' is not encodable", RTTI::Name::of<T>());  // invalid here
        }
    };

    /// @brief Derialization Handler.
    template <class T, class... As>
    struct Decoder : public T {
        //  PUBLIC METHODS  //

        /// @brief Validates that a decoder exists.
        static inline constexpr bool validate() {
            return requires(const Value& value, As&&... args) {
                { T::m_decode(value, args...) } -> std::convertible_to<T>;
            };
        }

        /**
         * @brief Handles decoding a value.
         * @param decodable                 Value to decode.
         * @param args                      Additional arguments.
         */
        $_INLINE_PERF static T decode(const Value& decodable, As&&... args) {
            if constexpr (validate()) return T::m_decode(decodable, std::forward<As>(args)...);
            else $_ABORT("Value is not decodable to '{0}'", RTTI::Name::of<T>());  // invalid
        }
    };

}  // namespace $::Serde

#endif
