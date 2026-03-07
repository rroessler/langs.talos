#ifndef _TALOS_TOOLCHAIN_TEST_HPP
#define _TALOS_TOOLCHAIN_TEST_HPP

/// Talos Modules
#include "talos/runtime/options.hpp"

namespace Talos::Toolchain {

    /**
     * @brief Handles launching a testing runtime.
     * @param options                           Runtime options.
     */
    int32_t test(const Runtime::Options& options = {});

}  // namespace Talos::Toolchain

#endif
