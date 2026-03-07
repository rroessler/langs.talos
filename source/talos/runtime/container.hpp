#ifndef _TALOS_RUNTIME_CONTAINER_HPP
#define _TALOS_RUNTIME_CONTAINER_HPP

/// Talos Modules
#include "talos/runtime/options.hpp"

namespace Talos::Runtime {

    /// @brief Services Container Abstraction.
    struct Container : public XI::Container {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a services container.
         * @param options                   Runtime options.
         */
        explicit Container(const Options& options = {});
    };

}  // namespace Talos::Runtime

#endif
