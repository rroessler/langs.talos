#ifndef _FORGE_SIGNAL_SERVICE_HPP
#define _FORGE_SIGNAL_SERVICE_HPP

/// Forge Modules
#include "forge/async/service.hpp"
#include "forge/forward/signal.hpp"
#include "forge/runtime/executor.hpp"

namespace Forge::Signal {

    /// @brief Signal Codes Typing.
    using Code = XSIO::Signal::Symbolic;

    /// @brief Signal Handling Service.
    class Service : public XI::Define<Service, XI::Shared, XI::Immediate> {
        //  PROPERTIES  //

        /// @brief Associated asynchronous runtime.
        Async::Service* m_async = nullptr;

        /// @brief Prepare the runtime handler.
        Value::Any m_handler = Value::Void();

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a signal service.
         * @param services                  Services container.
         */
        explicit Service(XI::Container* services);

        //  PUBLIC METHODS  //

        /**
         * @brief Handles raising signals.
         * @param code                      Signal code/name.
         */
        inline constexpr void raise(Code code) { m_async->signals()->raise(code); }
        inline constexpr void raise(const $::String::View& name) { m_async->signals()->raise(name); }

        /// @brief Handles ignoring user signal handling.
        inline constexpr void ignore() { subscribe(Value::Void()); }

        /**
         * @brief Handles subscribing a user signal handler.
         * @param handler                   Signal callback.
         */
        inline constexpr void subscribe(Value::Any handler) { m_handler = handler; }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles delegating incoming signals.
         * @param code                      Signal code.
         */
        void m_dispatch(const XSIO::Signal::Code& code);
    };

}  // namespace Forge::Signal

#endif
