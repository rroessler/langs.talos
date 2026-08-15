#ifndef _XLSP_MESSAGE_NOTIFICATION_HPP
#define _XLSP_MESSAGE_NOTIFICATION_HPP

/// XLSP Includes
#include "xlsp/message/channel.hpp"

namespace XLSP::Notification {

/// @brief Notification Parameters Declaration.
template <Message::Channel> struct Params;

/// @brief Denotes Empty Notification Parameters.
template <Message ::Channel C> using Empty = Message::Empty<Params<C>>;

/// @brief Denotes Nullish Notification Parameters.
template <Message::Channel C> using Nullish = Message::Nullish<Params<C>>;

} // namespace XLSP::Notification

#endif
