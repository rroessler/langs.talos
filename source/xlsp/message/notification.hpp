#ifndef _XLSP_MESSAGE_NOTIFICATION_HPP
#define _XLSP_MESSAGE_NOTIFICATION_HPP

/// XLSP Includes
#include "xlsp/message/traits.hpp"

//  MACROS  //

/// @brief Helper for building notifications.
#define XLSP_NOTIFICATION(N) ::XLSP::Notification::Params<::XLSP::Message::Type::N>

//  NAMESPACES  //

namespace XLSP::Notification {

    /// @brief Handles validating notifications.
    template <Message::Type T>
    concept Validate = T < Message::Type::$_NOTIFICATION;

    /// @brief Available Notification Parameters.
    template <Message::Type T>
    requires Validate<T> struct Params;

}  // namespace XLSP::Notification

#endif
