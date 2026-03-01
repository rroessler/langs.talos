#ifndef _FORGE_FORMAT_OPTIONS_HPP
#define _FORGE_FORMAT_OPTIONS_HPP

/// Forge Includes
#include "forge/forward/format.hpp"

//  X-MACROS  //

#define XX_FORMAT_OPTIONS(X)                          \
    X(line_width, "line.width", size_t, 120)          \
    X(indent_width, "indent.width", size_t, 4)        \
                                                      \
    X(indent_spaces, "indent.spaces", bool, true)     \
    X(newline_final, "newline.final", bool, true)     \
    X(arrow_compress, "arrow.compress", bool, true)   \
    X(commas_trailing, "commas.trailing", bool, true) \
    X(braces_compress, "braces.compress", bool, true) \
    X(braces_preserve, "braces.preserve", bool, true) \
    X(terminator_insert, "terminator.insert", bool, true)

//  NAMESPACES  //

namespace Forge::Format {

    /// @brief Formatter Options.
    struct Options {
        //  PROPERTIES  //

#define X(N, _, T, V, ...) T N = V;
        XX_FORMAT_OPTIONS(X)
#undef X

        //  CONSTRUCTORS  //

        /// @brief Default options constructor.
        constexpr Options() = default;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles decoding format options.
         * @param value                     Value to decode.
         */
        static Options m_decode(const $::Serde::Value& value) {
            // construct the default options output
            auto options = Options();

            // stop-fast if there is no valid value
            if (!value.is<$::Serde::Object>()) return options;

#define X(N, K, T, V, ...)                                                                \
    if (auto* _ = value.at<std::conditional_t<std::integral<T>, $::Serde::Number, T>>(K)) \
        options.N = static_cast<T>(*_);
            XX_FORMAT_OPTIONS(X)
#undef X

            // and return the resulting details now
            return options;
        };
    };

}  // namespace Forge::Format

//  UNDEFINES  //

#undef XX_FORMAT_OPTIONS

#endif
