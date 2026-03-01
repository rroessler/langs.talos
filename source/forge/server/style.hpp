#ifndef _FORGE_SERVER_STYLE_HPP
#define _FORGE_SERVER_STYLE_HPP

/// Forge Modules
#include "forge/forward/server.hpp"
#include "forge/relint/mirror.hpp"

namespace Forge::Server::Style {

    //  PUBLIC METHODS  //

    /**
     * @brief Gets the styled typing for a node.
     * @param mirror                Syntax mirror.
     */
    $::String::Buffer typing(const Relint::Mirror* mirror);

}  // namespace Forge::Server::Style

#endif
