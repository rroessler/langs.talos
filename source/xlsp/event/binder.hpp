#ifndef _XLSP_EVENT_BINDER_HPP
#define _XLSP_EVENT_BINDER_HPP

/// XLSP Includes
#include "xlsp/event/storage.hpp"
#include "xlsp/message/notification.hpp"
#include "xlsp/message/request.hpp"

namespace XLSP::Event {

/// @brief Handles binding events to a cache.
class Binder {
  //  PROPERTIES  //

  /// @brief Events Storage Reference.
  Storage *m_storage;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs an events binder.
   * @param storage               Events storage.
   */
  explicit Binder(Storage *storage) : m_storage(storage) {}

  //  PUBLIC METHODS  //

  /**
   * @brief Core binder for notifications.
   * @param method                Notification method.
   * @param handler               Handler to be bound.
   */
  template <class P>
  inline void on_notify(const Message::Method &method, $::Unique::Functor<void(const P &) const> &&cb) {
    $_TRACE("--| notification: registered {0}", method); // bind registration information
    m_storage->notifications[method] = [cb = std::move(cb)](const $::Serde::Value &value) {
      cb(P($::Serde::Decode<P>(value)));
    };
  }

  /**
   * @brief Allows binding class methods to notifications.
   * @param method                Notification method.
   * @param self                  Self instance value.
   * @param handler               Handler to be bound.
   */
  template <class T, std::derived_from<T> B, class P>
  inline void on_notify(const Message::Method &method, T *self, void (B::*handler)(const P &)) {
    on_notify(method, [self, handler](const auto &params) { return (self->*handler)(params); });
  }

  /**
   * @brief Handles binding notifications.
   * @param handler               Handler to be bound.
   */
  template <Message::Channel C>
  inline void on_notify($::Unique::Functor<void(const Notification::Params<C> &) const> &&handler) {
    on_notify<Notification::Params<C>>(C.view(), std::move(handler));
  }

  /**
   * @brief Allows binding class methods to notifications.
   * @param self                  Self instance value.
   * @param handler               Handler to be bound.
   */
  template <class T, std::derived_from<T> B, Message::Channel C>
  inline void on_notify(T *self, void (B::*handler)(const Notification::Params<C> &)) {
    on_notify<C>([self, handler](const Notification::Params<C> &params) { return (self->*handler)(params); });
  }

  /**
   * @brief Handles generic requests.
   * @param method                Request method.
   * @param handler               Handler to bind.
   */
  template <class P>
  inline void on_request(const Message::Method &method, $::Unique::Functor<void(const P &, Answer &&) const> &&cb) {
    $_TRACE("--| request: registered {0}", method); // bind the registration details
    m_storage->requests[method] = [cb = std::move(cb)](const auto &value, Answer &&reply) {
      cb(P($::Serde::Decode<P>(value)), std::move(reply));
    };
  }

  /**
   * @brief Handles generic requests.
   * @param method                Request method.
   * @param self                  Instance self value.
   * @param handler               Handler to bind.
   */
  template <class T, std::derived_from<T> B, class P>
  inline void on_request(const Message::Method &method, T *self, void (B::*handler)(const P &, Answer &&)) {
    on_request(method, [self, handler](const $::Serde::Value &params, Answer &&reply) {
      (self->*handler)(params, std::move(reply));
    });
  }

  /**
   * @brief Handles binding typed requests.
   * @param handler               Handler to be bound.
   */
  template <Message::Channel C, class R>
  inline void on_request($::Unique::Functor<void(Request::Handle<C, R>) const> &&cb) {
    // prepare a transformer callback to be used
    auto transformer = [cb = std::move(cb)](const auto &params, Answer &&reply) {
      // prepare a handle to be used now
      Request::Handle<C, R> request = Request::Handle<C, R>(params);

      if constexpr (std::is_same_v<R, Answer>) request.m_reply = std::move(reply);
      else request.m_reply = Binder::m_respond<C>(std::move(reply)); // bind reply

      // and trigger the result now
      cb(std::move(request));
    };

    // and bind it to the original requestor now
    on_request<Request::Params<C>>(C.view(), std::move(transformer));
  }

  /**
   * @brief Handles transforming typed requests.
   * @param self                  Instance self value.
   * @param handler               Handler to bind.
   */
  template <class T, std::derived_from<T> B, Message::Channel C, class R>
  inline void on_request(T *self, void (B::*handler)(Request::Handle<C, R>)) {
    on_request<C, R>([self, handler](auto handle) { (self->*handler)(std::move(handle)); });
  }

private:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles binding responses.
   * @param reply                     Response callback.
   */
  template <Message::Channel C> static inline Request::Callback<C> m_respond(Answer &&reply) {
    return [rp = std::move(reply)](const Message::Result<Request::Result<C>> &result) {
      if (const auto *error = std::get_if<Error>(&result)) rp(*error);
      else rp($::Serde::Encode(std::get<Request::Result<C>>(result)));
    };
  }
};

} // namespace XLSP::Event

#endif
