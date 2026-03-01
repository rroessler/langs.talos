#ifndef _FORGE_TOOLCHAIN_FORMAT_HPP
#define _FORGE_TOOLCHAIN_FORMAT_HPP

/// Forge Includes
#include "forge/document/buffer.hpp"
#include "forge/format/options.hpp"

namespace Forge::Toolchain {

    /**
     * @brief Handles formatting source-code.
     * @param buffer                Buffer to format.
     * @param options               Format options.
     */
    Format::Result format(const $::String::View& buffer, const Format::Options& options = {});
    Format::Result format(const Document::Buffer& document, const Format::Options& options = {});

}  // namespace Forge::Toolchain

#endif
