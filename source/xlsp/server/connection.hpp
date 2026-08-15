#ifndef _XLSP_SERVER_CONNECTION_HPP
#define _XLSP_SERVER_CONNECTION_HPP

/// XLSP Includes
#include "xlsp/event/binder.hpp"
#include "xlsp/event/emitter.hpp"
#include "xlsp/event/storage.hpp"
#include "xlsp/server/options.hpp"
#include "xlsp/transport/abstract.hpp"

namespace XLSP::Server {

/// @brief LSP Connection Container..
class Connection {
  //  PROPERTIES  //

  /// @brief Outgoing write mutex.
  mutable $::Mutex::Auto m_mutex;

  /// @brief Denotes if currently quiting.
  $::Async::Atomic<bool> m_quitting;

  /// @brief Contained connection options.
  Options m_options = {};

  /// @brief Bound transport instance.
  $::Unique::Pointer<Transport::Abstract> m_transport;

  /// @brief Underlying event storage.
  $::Unique::Pointer<Event::Storage> m_events = $::Unique::New<Event::Storage>();

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a connection instance.
   * @param options                   Server options.
   */
  explicit Connection(const Options &options = {});

  /**
   * @brief Constructs a connection instance.
   * @param transport                 Transport handler.
   * @param options                   Server options.
   */
  explicit Connection($::Unique::Pointer<Transport::Abstract> &&transport, const Options &options = {});

  /// @brief Abstract destructor.
  virtual ~Connection() = default;

  //  PUBLIC METHODS  //

  /// @brief Gets the current quitting status.
  inline constexpr bool quitting() const { return m_quitting; }

  /// @brief Gets the underlying options assigned.
  inline constexpr const Options *options() const { return &m_options; }

  /// @brief Gets the underlying events cache.
  inline constexpr Event::Storage *events() { return m_events.get(); }

  /// @brief Constructs an event-binder.
  inline constexpr Event::Binder binder() { return Event::Binder(m_events.get()); }

  /// @brief Gets the associated transport instance.
  inline constexpr Transport::Abstract *transport() const { return m_transport.get(); }

  /// @brief Declares as currently quitting now
  inline void shutdown() {
    $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
    m_quitting = true; // declare as quitting
  }

  /// @brief Handles listening for incoming events.
  inline int32_t listen() {
    // declare that we are running this connection instance
    $_DEBUG("{0} LSP v{1}", m_options.server.title, m_options.server.version);

    // show some details about the server now
    $_DEBUG("Process ID: {0}", $::System::pid());
    $_DEBUG("Transport: {0}", m_transport->label());

    // start running the listener loop now
    auto error = m_listen();

    // declare as being closed now
    $_DEBUG("Closing {0} LSP", m_options.server.title), $_DEBUG("Exited with errc: {0}", error);

    // if we have an error code, then immediately fail
    if (error != EXIT_SUCCESS) return error;

    // otherwise declare the exit code based on if we requested quitting
    return m_quitting ? EXIT_SUCCESS : EXIT_FAILURE;
  }

  /**
   * @brief Emits an outgoing notification.
   * @param method                    Notification method.
   * @param params                    Notification parameters.
   */
  inline void notify(const Message::Method &method, const Message::Params &params) {
    $_TRACE("<-- notification: {0}", method);
    $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
    m_transport->notify(method, params);
  }

  /**
   * @brief Emits a typed notification.
   * @tparam M                        Notification type.
   * @param notification              Notification parameters.
   */
  template <Message::Channel M> inline void notify(const Notification::Params<M> &params) {
    notify(M.view(), $::Serde::Encode(params));
  }

  /**
   * @brief Emits an outgoing request.
   * @param method                    Request method.
   * @param params                    Request parameters.
   * @param reply                     Reply to inherit.
   */
  inline void request(const Message::Method &method, const Message::Params &params, Event::Answer &&reply) {
    auto id = m_bind(std::move(reply)); // bind
    $_TRACE("<-- request: {0}({1})", method, id);

    // and emit the request outwards now
    $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
    m_transport->request(id, method, params);
  }

  /**
   * @brief Emits a typed request.
   * @tparam M                        Request type.
   * @param params                    Request parameters.
   * @param reply                     Reply callback.
   */
  template <Message::Channel C> inline void request(Request::Handle<C> handle) {
    // copy the current parameters now before moving the reply
    auto params = handle.params;

    // prepare a transformer instance to be used
    Event::Answer transformer = [rp = std::move(handle.reply)](const Message::Result<$::Serde::Value> &result) {
      if (auto *error = std::get_if<Error>(&result)) rp(*error); // immediate bypass
      else rp($::Serde::Decode<Request::Result<C>>(std::get<$::Serde::Value>(result)));
    };

    // and attempt making the request now
    request(C.view(), $::Serde::Encode(params), std::move(transformer));
  }

  /**
   * @brief Handles responding to requests.
   * @param identifier                Response identfier.
   * @param result                    Result to emit.
   */
  inline void respond(const Request::Identifier &identifier, const Message::Result<$::Serde::Value> &result) {
    $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
    m_transport->respond(identifier, result);
  }

protected:
  //  PROTECTED METHODS  //

  /// @brief Allows overriding the listen function.
  virtual inline int32_t m_listen() {
    auto emitter = Event::Emitter(this);
    return m_transport->listen(&emitter);
  }

private:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles binding replies.
   * @param reply                     Reply to bind.
   */
  $::String::Buffer m_bind(Event::Answer &&reply);
};

} // namespace XLSP::Server

#endif
