#ifndef _TALOS_ASYNC_SERVICE_HPP
#define _TALOS_ASYNC_SERVICE_HPP

/// Talos Modules
#include "talos/forward/async.hpp"
#include "talos/runtime/options.hpp"

namespace Talos::Async {

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
        explicit Service(XI::Container* services) : Service(*services) {}
        explicit Service(const Runtime::Options* options) : Define(&options->async) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the main-runtime isolate.
        inline constexpr Runtime::Isolate* isolate() const noexcept { return m_main; }
    };

}  // namespace Talos::Async

#endif
