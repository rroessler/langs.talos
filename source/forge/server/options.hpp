#ifndef _FORGE_SERVER_OPTIONS_HPP
#define _FORGE_SERVER_OPTIONS_HPP

/// Forge Includes
#include "forge/forward/server.hpp"

namespace Forge::Server {

    /// @brief Underlying server options.
    struct Options : public XLSP::Server::Options {
        //  CONSTRUCTORS  //

        /// @brief Ensures underlying options are set properly.
        constexpr Options() {
            server.title = FORGE_MM_TITLE;
            server.version = FORGE_MM_VERSION;
        }
    };

}  // namespace Forge::Server

#endif
