#ifndef _XTDLIB_STRING_LITERAL_HPP
#define _XTDLIB_STRING_LITERAL_HPP

/// Library Modules
#include "xtdlib/debug/printable.hpp"

namespace $::String {

    /// @brief Template String Literal.
    template <size_t N>
    struct Literal : public Printable {
        //  PROPERTIES  //

        /// @brief The underlying character buffer.
        char buffer[N] = {};

        //  CONSTRUCTORS  //

        /// @brief Default literal constructor.
        constexpr Literal() = default;

        /**
         * @brief Constructs a string literal.
         * @param buffer                    Character buffer.
         */
        constexpr Literal(const char (&buffer)[N]) { std::copy_n(buffer, N, this->buffer); }

        //  PUBLIC METHODS  //

        inline constexpr size_t size() const noexcept { return N - 1; }
        inline constexpr bool empty() const noexcept { return size() == 0; }
        inline constexpr const char* data() const noexcept { return buffer; }
        inline constexpr String::View view() const noexcept { return { data(), size() }; }

        /// @brief Allows joining literals.
        template <size_t M>
        inline constexpr auto join(const char (&suffix)[M]) const noexcept {
            // prepare the result of joining items
            auto result = Literal<N + M - 1>();

            // copy across this buffer and the one to join
            std::copy_n(buffer, N - 1, result.buffer);
            std::copy_n(suffix, M, result.buffer + N - 1);

            // return the resulting literal now
            return result;
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles printing literals.
         * @param os                        Output stream.
         * @param self                      String literal.
         */
        static inline void m_print(::$::Stream::Output& os, const Literal& self) { os << self.view(); }
    };

}  // namespace $::String

#endif
