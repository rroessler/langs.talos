#ifndef _XLSP_TRANSPORT_CONSOLE_HPP
#define _XLSP_TRANSPORT_CONSOLE_HPP

/// XLSP Modules
#include "xlsp/transport/stream.hpp"

namespace XLSP::Transport {

    /// @brief Console Transport Implementation.
    struct Console : public Stream {
        //  CONSTRUCTORS  //

        /// @brief Constructs an explicit stdio console-stream.
        explicit Console() : Stream($::IO::cin(), $::IO::cout(), "<stdio>") {}
    };

}  // namespace XLSP::Transport

#endif
