#ifndef _XTDLIB_SPINNER_FRAMES_HPP
#define _XTDLIB_SPINNER_FRAMES_HPP

/// C++ Modules
#include <array>
#include <span>

/// Library Modules
#include "xtdlib/string/view.hpp"

//  X-MACROS  //

#define XX_ANIMATION_BOX(X) X("▖") X("▘") X("▝") X("▗")
#define XX_ANIMATION_LINE(X) X("-") X("\\") X("|") X("/")
#define XX_ANIMATION_BALLOON(X) X(" ") X(".") X("o") X("O") X("@") X("*") X(" ")
#define XX_ANIMATION_DOTS(X) X("⠋") X("⠙") X("⠹") X("⠸") X("⠼") X("⠴") X("⠦") X("⠧") X("⠇") X("⠏")

#define XX_ANIMATION_LIST(X)   \
    X(box, XX_ANIMATION_BOX)   \
    X(line, XX_ANIMATION_LINE) \
    X(dots, XX_ANIMATION_DOTS) \
    X(balloon, XX_ANIMATION_BALLOON)

//  NAMESPACES  //

namespace $::Spinner {

    /// @brief Frames View Typing.
    using Frames = std::span<const String::View>;

}  // namespace $::Spinner

namespace $::Spinner::Animation {

#define XX_UNWRAP(F, ...) F,
#define XX_SIZEOF(...) 1 +
#define XX_DEFINE(N, L, ...)                                                               \
    static inline constexpr Frames N() {                                                   \
        static constexpr size_t s_size = L(XX_SIZEOF) 0;                                   \
        static constexpr auto s_frames = std::array<String::View, s_size>{ L(XX_UNWRAP) }; \
        return s_frames;                                                                   \
    }

    XX_ANIMATION_LIST(XX_DEFINE)
#undef XX_DEFINE
#undef XX_SIZEOF
#undef XX_UNWRAP

}  // namespace $::Spinner::Animation

//  UNDEFINES  //

#undef XX_ANIMATION_BOX
#undef XX_ANIMATION_DOTS
#undef XX_ANIMATION_LINE
#undef XX_ANIMATION_BALLOON
#undef XX_ANIMATION_LIST

#endif
