#ifndef _FORGE_TOOLCHAIN_BUNDLE_HPP
#define _FORGE_TOOLCHAIN_BUNDLE_HPP

/// Forge Modules
#include "forge/bundle/options.hpp"
#include "forge/runtime/options.hpp"

namespace Forge::Toolchain {

    /**
     * @brief Handles linting a runtime.
     * @param options               Runtime options.
     */
    int32_t lint(const Runtime::Options& options = {});

    /**
     * @brief Handles bundling a runtime.
     * @param options               Options to bundle.
     * @param runtime               Runtime options.
     */
    int32_t bundle(const Bundle::Options& options, const Runtime::Options& runtime = {});

}  // namespace Forge::Toolchain

#endif
