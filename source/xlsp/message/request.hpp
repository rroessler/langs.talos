#ifndef _XLSP_MESSAGE_REQUEST_HPP
#define _XLSP_MESSAGE_REQUEST_HPP

/// XLSP Includes
#include "xlsp/message/channel.hpp"
#include "xlsp/params/special.hpp"

namespace XLSP::Request {

/// @brief Request Identifier Typing.
using Identifier = $::String::Buffer;

/// @brief Request Cancellation Parameters.
using Cancel = Notification::Params<Notification::Channel::QUERY_CANCEL>;

/// @brief Request Parameters Declaration.
template <Message::Channel> struct Params;

/// @brief Request Result Declaration.
template <Message::Channel> struct Result;

/// @brief Denotes Empty Request Parameters.
template <Message ::Channel C> using Empty = Message::Empty<Params<C>>;

/// @brief Denotes Nullish Request Result.
template <Message::Channel C> using Nullish = Message::Nullish<Result<C>>;

/// @brief Response Callback Typing.
template <Message::Channel C> using Callback = $::Unique::Functor<void(const Message::Result<Result<C>> &) const>;

/// @brief Request Handle Structure.
template <Message::Channel C, class R = Callback<C>, class P = Params<C>> class Handle {
  //  TYPEDEFS  //

  /// @brief Allow the event-binder internal access.
  friend class Event::Binder;

  //  PROPERTIES  //

  R m_reply;
  P m_params;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a request handle.
   * @param reply                   Callback to bind.
   */
  constexpr Handle(R &&reply = nullptr) : m_reply(std::move(reply)) {}

  /**
   * @brief Constructs a request handle.
   * @param params                  Params to bind.
   * @param reply                   Callback to bind.
   */
  constexpr Handle(const P &params, R &&reply = nullptr) : m_reply(std::move(reply)), m_params(params) {}

  //  PUBLIC METHODS  //

  /// @brief Allows getting the underlying parameters.
  inline constexpr const P &params() const noexcept { return m_params; }

  /// @brief Cancels the parent request.
  inline constexpr void cancel() const noexcept { m_reply(Error::Code::SERVER_CANCELLED); }

  /**
   * @brief Prepares a baseline result to be returned.
   * @param args                    Result arguments.
   */
  template <class... As> inline constexpr Result<C> prepare(As &&...args) const noexcept {
    return Result<C>(std::forward<As>(args)...);
  }

  /**
   * @brief Responds to the request with a result.
   * @param result                  Result to reply.
   */
  inline constexpr void reply() const { m_reply(prepare()); }
  inline constexpr void reply(const Message::Result<Result<C>> &result) const { m_reply(result); }
};

} // namespace XLSP::Request

#endif
