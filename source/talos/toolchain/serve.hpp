#ifndef _TALOS_TOOLCHAIN_SERVE_HPP
#define _TALOS_TOOLCHAIN_SERVE_HPP

/// Talos Includes
#include "talos/runtime/options.hpp"

namespace Talos::Toolchain {

/**
 * @brief Handles launching the "talos" language-server.
 * @param options                   Options to bind.
 */
int32_t serve(const Runtime::Options &options = {});

} // namespace Talos::Toolchain

#endif
