#ifndef _TALOS_TOOLCHAIN_LAUNCH_HPP
#define _TALOS_TOOLCHAIN_LAUNCH_HPP

/// Talos Modules
#include "talos/runtime/options.hpp"

namespace Talos::Toolchain {

    /**
     * @brief Handles launching a bundled runtime.
     * @param argc                      Argument count.
     * @param argv                      Variadic arguments.
     */
    int32_t launch(int32_t argc, char** argv);

    /**
     * @brief Handles launching a runtime.
     * @param options                   Runtime options.
     */
    int32_t launch(const Runtime::Options& options = {});

    /**
     * @brief Handles bootstrapping the runtime.
     * @param options                   Runtime options.
     */
    XI::Container* bootstrap(const Runtime::Options& options = {});

}  // namespace Talos::Toolchain

#endif
