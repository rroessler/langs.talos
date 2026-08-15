#ifndef _TALOS_TOOLCHAIN_BUNDLE_HPP
#define _TALOS_TOOLCHAIN_BUNDLE_HPP

/// Talos Includes
#include "talos/bundle/options.hpp"
#include "talos/runtime/options.hpp"

namespace Talos::Toolchain {

/**
 * @brief Handles linting a runtime.
 * @param options               Runtime options.
 */
int32_t lint(const Runtime::Options &options = {});

/**
 * @brief Handles bundling a runtime.
 * @param options               Options to bundle.
 * @param runtime               Runtime options.
 */
int32_t bundle(const Bundle::Options &options, const Runtime::Options &runtime = {});

} // namespace Talos::Toolchain

#endif
