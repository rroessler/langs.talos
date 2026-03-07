#ifndef _TALOS_SERVER_OPTIONS_HPP
#define _TALOS_SERVER_OPTIONS_HPP

/// Talos Includes
#include "talos/forward/server.hpp"

namespace Talos::Server {

    /// @brief Underlying server options.
    struct Options : public XLSP::Server::Options {
        //  CONSTRUCTORS  //

        /// @brief Ensures underlying options are set properly.
        constexpr Options() {
            server.title = TALOS_MM_TITLE;
            server.version = TALOS_MM_VERSION;
        }
    };

}  // namespace Talos::Server

#endif
