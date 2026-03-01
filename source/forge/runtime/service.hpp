#ifndef _FORGE_RUNTIME_SERVICE_HPP
#define _FORGE_RUNTIME_SERVICE_HPP

/// Vendor Includes
#include <xinv/xinv.hpp>

/// Forge Includes
#include "forge/async/service.hpp"
#include "forge/runtime/main.hpp"
#include "forge/runtime/options.hpp"

namespace Forge::Runtime {

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
         * @brief Constructs a runtime service.
         * @param services                  Services container.
         */
        explicit Service();
        explicit Service(XI::Container* services);

        //  PUBLIC METHODS  //

        /// @brief Handles launching the runtime.
        inline int32_t launch() { return m_async->launch<Main>(m_services); }

        /**
         * @brief Handles exiting the runtime.
         * @param exit_code                 Exit code to set.
         */
        inline void exit(int32_t exit_code = $_EXIT_SUCCESS) { m_async->exit(exit_code); }
    };

}  // namespace Forge::Runtime

#endif
