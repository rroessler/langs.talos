#ifndef _XLSP_MESSAGE_REQUEST_HPP
#define _XLSP_MESSAGE_REQUEST_HPP

/// XLSP Includes
#include "xlsp/message/error.hpp"

//  MACROS  //

/// @brief Helper for building requests.
#define XLSP_REQUEST(N, ...) ::XLSP::Request::Handle<::XLSP::Message::Type::N $_PP_VARGS(__VA_ARGS__)>

/// @brief Helper for building responses.
#define XLSP_RESPONSE(N, ...) ::XLSP::Response::Value<::XLSP::Message::Type::N>(__VA_ARGS__)

//  NAMESPACES  //

namespace XLSP::Request {

    /// @brief Potential identifiers available.
    using Identifier = $::String::Buffer;

    /// @brief Handles validating notifications.
    template <Message::Type T>
    concept Validate = T > Message::Type::$_REQUEST;

    /// @brief Available Notification Parameters.
    template <Message::Type T>
    requires Validate<T> struct Params;

}  // namespace XLSP::Request

namespace XLSP::Response {

    /// @brief Declares explicit response values.
    template <Message::Type T>
    struct Value;

}  // namespace XLSP::Response

namespace XLSP::Request {

    /// @brief Request Responder Callback.
    template <Message::Type T>
    using Callback = $::Functor::Unique<void(const Message::Result<Response::Value<T>>&)>;

    /// @brief Request Handle Container.
    template <Message::Type T, class C = Callback<T>, class P = Params<T>>
    struct Handle {
        //  PROPERTIES  //

        C reply;   // Handles response values.
        P params;  // Incoming parameters value.

        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an empty handle.
         * @param params                Parameters to bind.
         * @param reply                 Reply to bind.
         */
        constexpr Handle(const P& params, C&& reply = nullptr) : reply(std::move(reply)), params(params) {}

        //  PUBLIC METHODS  //

        /// @brief Handles cancelling the response.
        inline constexpr void cancel() const noexcept { reply(XLSP_ERROR(SERVER_CANCELLED)); }
    };

}  // namespace XLSP::Request

#endif
