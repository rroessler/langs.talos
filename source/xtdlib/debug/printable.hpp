#ifndef _XTDLIB_DEBUG_PRINTABLE_HPP
#define _XTDLIB_DEBUG_PRINTABLE_HPP

/// Library Modules
#include "xtdlib/macros/attributes.hpp"
#include "xtdlib/macros/forward.hpp"
#include "xtdlib/stream/color.hpp"
#include "xtdlib/string/buffer.hpp"
#include "xtdlib/string/stream.hpp"
#include "xtdlib/string/view.hpp"
#include "xtdlib/terminal/dye.hpp"
#include "xtdlib/vendors/fmt.hpp"

/// Forward Declarations
$_FWD(template <class T $_PP_COMMA class... As> static String::Buffer stringify(const T&, As&&...), $::Convert)

namespace $ {

    /// @brief Printable Base Abstraction.
    class $_ABSTRACT Printable {
        //  TYPEDEFS  //

        /// @brief Allow printables internal access.
        template <std::derived_from<Printable> T>
        $_INLINE_ALWAYS friend Stream::Output& operator<<(Stream::Output& os, const T& self) {
            return Expose<T>::print(os, self), os;
        }

        /// @brief Allow stringification internal access.
        template <class T, class... As>
        friend String::Buffer Convert::stringify(const T&, As&&...);

        /// @brief Allow formatters internal access.
        template <class, class, class>
        friend struct fmt::formatter;

        /// @brief Printable Accessor Instance.
        template <std::derived_from<Printable> T>
        struct Expose : public T {
            //  PUBLIC METHODS  //

            /**
             * @brief Handles exposing the "stringify" method.
             * @param self                      Instance to stringify.
             */
            template <class... As>
            static $_INLINE_ALWAYS String::Buffer stringify(const T& self, As&&... args) {
                auto oss = String::Stream();  // prepare stream for use now
                T::m_stringify(oss, self, std::forward<As>(args)...);
                return oss.str();  // and convert the result to a string
            }

            /**
             * @brief Handles exposing the "print" method.
             * @param os                        Output stream.
             * @param self                      Instance to dump.
             */
            static $_INLINE_ALWAYS void print(Stream::Output& os, const T& self) { T::m_print(os, self); }
        };
    };

}  // namespace $

//  SPECIALIZATIONS  //

template <class T>
struct fmt::formatter<T, std::enable_if_t<std::is_base_of_v<$::Printable, T>, char>>
    : fmt::formatter<$::String::View, char> {
    //  PUBLIC METHODS  //

    /// @brief Handles printing out details.
    auto format(const T& value, fmt::format_context& ctx) const -> decltype(ctx.out()) {
        auto buffer = fmt::basic_memory_buffer<char>();
        auto&& format_buf = fmt::detail::formatbuf<std::basic_streambuf<char>>(buffer);
        auto&& output = std::basic_ostream<char>(&format_buf);

#if !defined(FMT_STATIC_THOUSANDS_SEPARATOR)
        output.imbue(std::locale::classic());
#endif

        // determine if we are using colors or not
        const auto pretty = m_pretty(ctx);

        // and output our details now
        if (pretty) $::Dye::enabled(output, true);
        $::Printable::Expose<T>::print(output, value);
        if (pretty) $::Dye::enabled(output, false);

        // and further format as necessary now
        output.exceptions(std::ios_base::failbit | std::ios_base::badbit);
        return fmt::formatter<$::String::View, char>::format({ buffer.data(), buffer.size() }, ctx);
    }

   private:
    //  PRIVATE METHODS  //

    /**
     * @brief Checks if the context is prettified.
     * @param ctx                   Context to query.
     */
    bool m_pretty(fmt::format_context& ctx) const {
        auto locale = ctx.locale().get<std::locale>();
        if (!std::has_facet<$::Facet::Color>(locale)) return false;
        return !std::use_facet<$::Facet::Color>(locale).disabled;
    }
};

#endif
