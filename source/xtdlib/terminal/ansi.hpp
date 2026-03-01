#ifndef _XTDLIB_TERMINAL_ANSI_HPP
#define _XTDLIB_TERMINAL_ANSI_HPP

/// Library Includes
#include "xtdlib/debug/printable.hpp"
#include "xtdlib/string/buffer.hpp"
#include "xtdlib/string/view.hpp"

//  X-MACROS  //

#define XX_ANSI_COLORS(X) \
    X(grey, 0)            \
    X(red, 1)             \
    X(green, 2)           \
    X(yellow, 3)          \
    X(blue, 4)            \
    X(magenta, 5)         \
    X(cyan, 6)            \
    X(white, 7)

#define XX_ANSI_STYLES(X) \
    X(bold, 1)            \
    X(dim, 2)             \
    X(italic, 3)          \
    X(underline, 4)       \
    X(blink, 5)

//  NAMESPACES  //

namespace $ {

    /// @brief ANSI Painter.
    class ANSI : public Printable {
        //  TYPEDEFS  //

        /// @brief Encapsulates background coloring.
        class Background : public Printable {
            //  PROPERTIES  //

            /// @brief ANSI parent reference.
            ANSI* m_ansi;

           public:
            //  CONSTRUCTORS  //

            /// @brief Inherit the base constructor.
            explicit constexpr Background(ANSI* ansi) : m_ansi(ansi) {}

            //  PUBLIC METHODS  //

#define X(N, V, ...) \
    inline constexpr ANSI& N() { return m_ansi->m_background = V, *m_ansi; }
            XX_ANSI_COLORS(X)
#undef X

           protected:
            //  PRIVATE METHODS  //

            /**
             * @brief Handles printing backgrounds.
             * @param os                Output stream.
             * @param self              Background value.
             */
            static inline void m_print(Stream::Output& os, const Background& self) { os << *self.m_ansi; }
        };

        //  PROPERTIES  //

        uint8_t m_style = UINT8_MAX;       // Styling data.
        uint8_t m_foreground = UINT8_MAX;  // Foreground data.
        uint8_t m_background = UINT8_MAX;  // Background data.

        /// @brief The underlying painted value.
        String::Buffer m_value = "";

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an ANSI painter.
         * @param value             Value buffer.
         */
        constexpr ANSI(const String::Buffer& buffer = "") : m_value(buffer) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying raw-value.
        inline constexpr String::View value() const noexcept { return m_value; }
        inline constexpr String::Buffer& value() noexcept { return m_value; }

        /// @brief Gets a mutable background reference.
        inline constexpr Background background() { return Background(this); }

        /// @brief Denotes if there is no actual styling.
        inline constexpr bool empty() const noexcept {
            return m_style == UINT8_MAX && m_foreground == UINT8_MAX && m_background == UINT8_MAX;
        }

#define X(N, V, ...) \
    inline constexpr ANSI& N() { return m_foreground = V, *this; }
        XX_ANSI_COLORS(X)
#undef X

#define X(N, V, ...) \
    inline constexpr ANSI& N() { return m_style = V, *this; }
        XX_ANSI_STYLES(X)
#undef X

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles formatting ANSI values.
         * @param os                    Output stream.
         * @param self                  ANSI instance.
         */
        static void m_print(Stream::Output& os, const ANSI& self);

        /**
         * @brief Allows forcibly stringifying values.
         * @param os                    Output stream.
         * @param self                  ANSI instance.
         */
        static void m_stringify(Stream::Output& os, const ANSI& self);
    };

}  // namespace $

namespace $::Dye {

#define X(N, ...)                                                                       \
    template <class T>                                                                  \
    inline ANSI N(const T& value) {                                                     \
        return ANSI(fmt::to_string(value)).N();                                         \
    }                                                                                   \
                                                                                        \
    template <class... As>                                                              \
    inline ANSI N(fmt::format_string<As...> message, As&&... args) {                    \
        return ANSI(fmt::format(message, std::forward<As>(args)...)).N();               \
    }                                                                                   \
                                                                                        \
    template <class... As>                                                              \
    inline ANSI N(const String::View& message, As&&... args) {                          \
        return ANSI(fmt::format(fmt::runtime(message), std::forward<As>(args)...)).N(); \
    }

    XX_ANSI_COLORS(X)
    XX_ANSI_STYLES(X)
#undef X

}  // namespace $::Dye

//  UNDEFINES  //

#undef XX_ANSI_COLORS
#undef XX_ANSI_STYLES

#endif
