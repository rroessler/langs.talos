#ifndef _TALOS_SERVER_STYLE_HPP
#define _TALOS_SERVER_STYLE_HPP

/// Talos Includes
#include "talos/forward/server.hpp"
#include "talos/relint/mirror.hpp"

namespace Talos::Server::Style {

//  PUBLIC METHODS  //

/**
 * @brief Gets the styled typing for a node.
 * @param mirror                Syntax mirror.
 */
$::String::Buffer typing(const Relint::Mirror *mirror);

/**
 * @brief Handles notating hover content.
 * @param segments              Content to notate.
 */
$::String::Buffer hover(const $::String::View &content);
$::String::Buffer hover(const $::Notate::Segments &segments);
$::String::Buffer hover(const std::vector<$::String::Buffer> &segments);

} // namespace Talos::Server::Style

#endif
