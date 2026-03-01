#ifndef _FORGE_TOOLCHAIN_TEST_HPP
#define _FORGE_TOOLCHAIN_TEST_HPP

/// Forge Modules
#include "forge/runtime/options.hpp"

namespace Forge::Toolchain {

    /**
     * @brief Handles launching a testing runtime.
     * @param options                           Runtime options.
     */
    int32_t test(const Runtime::Options& options = {});

}  // namespace Forge::Toolchain

#endif
