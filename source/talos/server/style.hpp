#ifndef _TALOS_SERVER_STYLE_HPP
#define _TALOS_SERVER_STYLE_HPP

/// Talos Modules
#include "talos/forward/server.hpp"
#include "talos/relint/mirror.hpp"

namespace Talos::Server::Style {

    //  PUBLIC METHODS  //

    /**
     * @brief Gets the styled typing for a node.
     * @param mirror                Syntax mirror.
     */
    $::String::Buffer typing(const Relint::Mirror* mirror);

}  // namespace Talos::Server::Style

#endif
