#ifndef _FORGE_BUNDLE_SERVICE_HPP
#define _FORGE_BUNDLE_SERVICE_HPP

/// Vendor Includes
#include <xinv/xinv.hpp>

/// Forge Includes
#include "forge/async/service.hpp"
#include "forge/bundle/options.hpp"
#include "forge/bundle/worker.hpp"

namespace Forge::Bundle {

    /// @brief Core Runtime Service.
    class Service : public XI::Define<Service, XI::Shared> {
        //  PROPERTIES  //

        /// @brief Available services container.
        XI::Container* m_services;

        /// @brief Asynchrononous runtime service.
        Async::Service* m_async;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a bundling service.
         * @param services                  Services container.
         */
        explicit Service();
        explicit Service(XI::Container* services);

        //  PUBLIC METHODS  //

        /**
         * @brief Handles bundling the runtime.
         * @param options                   Bundle options.
         */
        int32_t bundle(const Options& options);
    };

}  // namespace Forge::Bundle

#endif
