#ifndef _XLSP_TRANSPORT_ABSTRACT_HPP
#define _XLSP_TRANSPORT_ABSTRACT_HPP

/// XLSP Modules
#include "xlsp/forward/event.hpp"
#include "xlsp/forward/transport.hpp"
#include "xlsp/message/request.hpp"

namespace XLSP::Transport {

    /// @brief Transport Interface.
    struct $_ABSTRACT Abstract {
        //  CONSTRUCTORS  //

        /// @brief Virtual Destructor.
        virtual ~Abstract() = default;

        //  PUBLIC METHODS  //

        /// @brief Title of transport type.
        virtual $::String::View label() const = 0;

        /**
         * @brief Handles listening to incoming events and dispatching them.
         * @param events                    Events dispatcher.
         */
        virtual int32_t listen(Event::Dispatcher* events) = 0;

        /**
         * @brief Handles emitting notifications.
         * @param method                    Method channel to notify.
         * @param params                    Notification parameters.
         */
        virtual void notify(const Message::Method& method, const Message::Params& params) = 0;

        /**
         * @brief Handles emitting requests.
         * @param id                        Identifier for a request.
         * @param method                    Method channel to request.
         * @param params                    Request parameters.
         */
        virtual void request(
            const Request::Identifier& id, const Message::Method& method, const Message::Params& params) = 0;

        /**
         * @brief Handles emitting responses.
         * @param id                        Identifier for a request.
         * @param result                    Response result value.
         */
        virtual void respond(const Request::Identifier& id, const Message::Result<$::Serde::Value>& result) = 0;
    };

}  // namespace XLSP::Transport

#endif
