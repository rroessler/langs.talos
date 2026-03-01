#ifndef _FORGE_TOOLCHAIN_SERVE_HPP
#define _FORGE_TOOLCHAIN_SERVE_HPP

/// Forge Modules
#include "forge/runtime/options.hpp"
#include "forge/server/options.hpp"

namespace Forge::Toolchain {

    /**
     * @brief Handles launching the "talos" language-server.
     * @param options                   Options to bind.
     */
    int32_t serve(const Runtime::Options& options = {});

}  // namespace Forge::Toolchain

#endif
