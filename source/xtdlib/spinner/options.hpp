#ifndef _XTDLIB_SPINNER_OPTIONS_HPP
#define _XTDLIB_SPINNER_OPTIONS_HPP

/// Library Modules
#include "xtdlib/chrono/duration.hpp"
#include "xtdlib/io/print.hpp"
#include "xtdlib/spinner/frames.hpp"
#include "xtdlib/string/buffer.hpp"

namespace $::Spinner {

    /// @brief Denotes the spinner mode.
    enum class Mode : uint8_t {
        ENABLED,   // fully enabled
        DISABLED,  // fully disabled
        PARTIAL,   // open/close only
        RESOLVE,   // auto-decide here
    };

    /// @brief Spinner Options.
    struct Options {
        Mode mode = Mode::RESOLVE;
        String::Buffer prefix = "";
        String::Buffer suffix = "";
        Chrono::Duration tick = 80ms;
        Stream::Output& os = IO::cout();
        Frames frames = Animation::dots();
    };

}  // namespace $::Spinner

#endif
