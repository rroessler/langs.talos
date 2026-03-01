#ifndef _XHASH_FNV_HPP
#define _XHASH_FNV_HPP

/// Hash Modules
#include "xhash/forward/algorithms.hpp"

namespace XH::FNV {

    //  TYPEDEFS  //

    /// @brief Fowler/Noll/Vo Hasher.
    template <std::integral T, T P, T S>
    class Digest {
        //  PROPERTIES  //

        static inline constexpr T m_prime = P;
        static inline constexpr T m_seed = S;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a FNV hasher.
        explicit constexpr Digest() = default;

        //  OPERATOR METHODS  //

        /// @brief Handles hashing singular characters.
        inline constexpr T operator()(char ch, T value = m_seed) const noexcept {
            return (value ^ static_cast<T>(static_cast<uint8_t>(ch))) * m_prime;
        }

        /// @brief Handles hashing unknown-size c-strings.
        inline constexpr T operator()(const char* str, T value = m_seed) const noexcept {
            for (; *str != '\0'; ++str) value = digest(*str, value);
            return value;  // return the resulting value now here
        }

        /// @brief Handles hasing known-size c-strings.
        inline constexpr T operator()(const char* str, size_t size, T value = m_seed) const noexcept {
            for (size_t ii = 0; ii < size; ++ii) value = digest(str[ii], value);
            return value;  // return the resulting value now
        }

        /// @brief Handles hashing string-views.
        inline constexpr T operator()(const Input& view, T value = m_seed) const noexcept {
            return (*this)(view.data(), view.size(), value);
        }

        //  PUBLIC METHODS  //

        /// @brief Allow getting the seed value.
        inline constexpr T seed() const noexcept { return m_seed; }

        /// @brief Allow getting the prime value.
        inline constexpr T prime() const noexcept { return m_prime; }

        /// @brief Allow forwarding values to the baseline operator.
        template <class... As>
        inline constexpr T digest(As&&... args) const noexcept {
            return (*this)(std::forward<As>(args)...);
        }
    };

    //  PROPERTIES  //

    static constexpr auto U32 = Digest<uint32_t, 0x1000193, 0x811c9dc5>();
    static constexpr auto U64 = Digest<uint64_t, 0x100000001b3, 0xcbf29ce484222325>();

}  // namespace XH::FNV

#endif
