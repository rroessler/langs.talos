#ifndef _FORGE_ASYNC_SERVICE_HPP
#define _FORGE_ASYNC_SERVICE_HPP

/// Forge Modules
#include "forge/forward/async.hpp"
#include "forge/runtime/options.hpp"

namespace Forge::Async {

    /// @brief Asynchronous Event-Loop Service.
    class Service : public XI::Define<Service, XI::Shared, XSIO::Async::Manager> {
        //  TYPEDEFS  //

        /// @brief Allow main isolates internal access.
        friend struct Main;

        //  PROPERTIES  //

        /// @brief The main runtime isolate.
        Runtime::Isolate* m_main = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Allow default construction.
        explicit Service() = default;

        /**
         * @brief Constructs an asynchronous manager.
         * @param services          Services container.
         */
        explicit Service(XI::Container* services) : Define(&services->get<Runtime::Options>()->async) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the main-runtime isolate.
        inline constexpr Runtime::Isolate* isolate() const noexcept { return m_main; }
    };

}  // namespace Forge::Async

#endif
