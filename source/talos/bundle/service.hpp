#ifndef _TALOS_BUNDLE_SERVICE_HPP
#define _TALOS_BUNDLE_SERVICE_HPP

/// Vendor Includes
#include <xinv/xinv.hpp>

/// Talos Includes
#include "talos/async/service.hpp"
#include "talos/bundle/options.hpp"
#include "talos/bundle/worker.hpp"

namespace Talos::Bundle {

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

}  // namespace Talos::Bundle

#endif
