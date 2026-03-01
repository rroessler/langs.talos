#ifndef _FORGE_RUNTIME_CONTAINER_HPP
#define _FORGE_RUNTIME_CONTAINER_HPP

/// Forge Modules
#include "forge/runtime/options.hpp"

namespace Forge::Runtime {

    /// @brief Services Container Abstraction.
    struct Container : public XI::Container {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a services container.
         * @param options                   Runtime options.
         */
        explicit Container(const Options& options = {});
    };

}  // namespace Forge::Runtime

#endif
