#ifndef _FORGE_TESTING_SERVICE_HPP
#define _FORGE_TESTING_SERVICE_HPP

/// Forge Modules
#include "forge/async/service.hpp"
#include "forge/runtime/options.hpp"
#include "forge/testing/main.hpp"
#include "forge/testing/options.hpp"

namespace Forge::Testing {

    /// @brief Constructs a testing service.
    class Service : public XI::Define<Service, XI::Shared> {
        //  PROPERTIES  //

        /// @brief Available services container.
        XI::Container* m_services;

        /// @brief Asynchrononous runtime service.
        Async::Service* m_async;

        /// @brief The underlying session instance.
        Session* m_session;

        /// @brief The underlying registry instance.
        Registry* m_registry;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a runtime service.
         * @param services                  Services container.
         */
        explicit Service();
        explicit Service(XI::Container* services);

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying services container.
        inline constexpr XI::Container* services() const noexcept { return m_services; }

        /// @brief Gets the testing session.
        inline constexpr Session* session() const noexcept { return m_session; }

        /// @brief Gets the testing registry.
        inline constexpr Registry* registry() const noexcept { return m_registry; }

        /// @brief Handles launching the runtime.
        inline int32_t launch() { return m_async->launch<Main>(m_services); }
    };

}  // namespace Forge::Testing

#endif
