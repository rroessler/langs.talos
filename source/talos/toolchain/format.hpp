#ifndef _TALOS_TOOLCHAIN_FORMAT_HPP
#define _TALOS_TOOLCHAIN_FORMAT_HPP

/// Talos Includes
#include "talos/document/buffer.hpp"
#include "talos/format/options.hpp"

namespace Talos::Toolchain {

/**
 * @brief Handles formatting source-code.
 * @param buffer                Buffer to format.
 * @param options               Format options.
 */
Format::Result format(const $::String::View &buffer, const Format::Options &options = {});
Format::Result format(const Document::Buffer &document, const Format::Options &options = {});

} // namespace Talos::Toolchain

#endif
