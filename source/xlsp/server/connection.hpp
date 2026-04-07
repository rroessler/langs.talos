#ifndef _XLSP_SERVER_CONNECTION_HPP
#define _XLSP_SERVER_CONNECTION_HPP

/// XLSP Includes
#include "xlsp/event/binder.hpp"
#include "xlsp/event/dispatcher.hpp"
#include "xlsp/event/storage.hpp"
#include "xlsp/server/options.hpp"
#include "xlsp/transport/console.hpp"

namespace XLSP::Server {

    /// @brief LSP Connection Container..
    class Connection {
        //  PROPERTIES  //

        /// @brief Outgoing write mutex.
        mutable $::Mutex::Auto m_mutex;

        /// @brief Denotes if currently quiting.
        $::Atomic<bool> m_quitting;

        /// @brief Contained connection options.
        const Options* m_options;

        /// @brief Bound transport instance.
        $::Ptr::Unique<Transport::Abstract> m_transport;

        /// @brief Underlying event storage.
        $::Ptr::Unique<Event::Storage> m_events = $::New().unique<Event::Storage>();

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a connection instance.
         * @param options                   Server options.
         */
        explicit Connection(const Options* options = $::Global::get<Options>()) :
            Connection($::New().unique<Transport::Console>(), options) {}

        /**
         * @brief Constructs a connection instance.
         * @param transport                 Transport handler.
         * @param options                   Server options.
         */
        explicit Connection(
            $::Ptr::Unique<Transport::Abstract>&& transport, const Options* options = $::Global::get<Options>()) :
            m_options(options), m_transport(std::move(transport)) {}

        /// @brief Abstract destructor.
        virtual ~Connection() = default;

        //  PUBLIC METHODS  //

        /// @brief Gets the current quitting status.
        inline constexpr bool quitting() const { return m_quitting; }

        /// @brief Gets the underlying options assigned.
        inline constexpr const Options* options() const { return m_options; }

        /// @brief Gets the underlying events cache.
        inline constexpr Event::Storage* events() { return m_events.get(); }

        /// @brief Constructs an event-binder.
        inline constexpr Event::Binder binder() { return Event::Binder(m_events.get()); }

        /// @brief Gets the associated transport instance.
        inline constexpr Transport::Abstract* transport() const { return m_transport.get(); }

        /// @brief Declares as currently quitting now
        inline void shutdown() {
            $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
            m_quitting = true;  // declare as quitting
        }

        /// @brief Handles listening for incoming events.
        inline int32_t listen() {
            // declare that we are running this connection instance
            $_DEBUG("{0} LSP v{1}", m_options->server.title, m_options->server.version);

            // show some details about the server now
            $_DEBUG("Process ID: {0}", $::System::pid());
            $_DEBUG("Transport: {0}", m_transport->label());

            // start running the listener loop now
            auto error = m_listen();

            // declare as being closed now
            $_DEBUG("Closing {0} LSP", m_options->server.title), $_DEBUG("Exited with errc: {0}", error);

            // if we have an error code, then immediately fail
            if (error != $_EXIT_SUCCESS) return error;

            // otherwise declare the exit code based on if we requested quitting
            return m_quitting ? $_EXIT_SUCCESS : $_EXIT_FAILURE;
        }

        /**
         * @brief Emits an outgoing notification.
         * @param method                    Notification method.
         * @param params                    Notification parameters.
         */
        inline void notify(const Message::Method& method, const Message::Params& params) {
            $_TRACE("<-- notification: {0}", method);
            $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
            m_transport->notify(method, params);
        }

        /**
         * @brief Emits a typed notification.
         * @tparam M                        Notification type.
         * @param notification              Notification parameters.
         */
        template <Message::Type M>
        inline void notify(const Notification::Params<M>& params) {
            notify(Message::Channel<M>(), $::Reflect::encode(params));
        }

        /**
         * @brief Emits an outgoing request.
         * @param method                    Request method.
         * @param params                    Request parameters.
         * @param reply                     Reply to inherit.
         */
        inline void request(const Message::Method& method, const Message::Params& params, Event::Answer&& reply) {
            auto id = m_bind(std::move(reply));  // bind
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
        template <Message::Type M>
        inline void request(Request::Handle<M> handle) {
            // copy the current parameters now before moving the reply
            auto params = handle.params;

            // prepare a transformer instance to be used
            Event::Answer transformer = [rp = std::move(handle.reply)](const Message::Result<$::Serde::Value>& result) {
                if (auto* error = std::get_if<Message::Error>(&result)) rp(*error);
                else rp($::Reflect::decode<Response::Value<M>>(std::get<$::Serde::Value>(result)));
            };

            // and attempt making the request now
            request(Message::Channel<M>(), $::Reflect::encode(params), std::move(transformer));
        }

        /**
         * @brief Handles responding to requests.
         * @param identifier                Response identfier.
         * @param result                    Result to emit.
         */
        inline void respond(const Request::Identifier& identifier, const Message::Result<$::Serde::Value>& result) {
            $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
            m_transport->respond(identifier, result);
        }

       protected:
        //  PRIVATE METHODS  //

        /// @brief Allows overriding the listen function.
        virtual inline int32_t m_listen() {
            auto dispatcher = Event::Dispatcher(this);
            return m_transport->listen(&dispatcher);
        }

       private:
        /**
         * @brief Handles binding replies.
         * @param reply                     Reply to bind.
         */
        $::String::Buffer m_bind(Event::Answer&& reply) {
            // prepare the necessary identifier to be used
            auto identifier = fmt::to_string(++m_events->identifier);

            // get the maximum queue threshold
            const auto threshold = m_options->events.threshold;

            // prepare a response handler for missing replies
            std::optional<Event::Pending> pending = std::nullopt;

            // ensure no other calls can be made whilst we bind a response
            auto lock = $::Lock::scope(m_events->mutex.reply);

            // emplace the necessary callback to be used now
            m_events->responses.emplace_back(identifier, std::move(reply));

            // if the queue overflows, we assume the client did not reply
            if (m_events->responses.size() > threshold) {
                pending = std::move(m_events->responses.front());  // get the pending request now
                $_ERROR("More than {0} outstanding LSP requests, forgetting about {1}", threshold, pending->identifier);
                m_events->responses.pop_front();  // ensure the callback has now been ignored
            }

            // declare as finishing our lock region now
            lock.unlock();

            // declare an error if necessary
            if (pending.has_value()) {
                auto message = fmt::format("Failed to receive reply for request ({0})", identifier);
                pending->answer(XLSP_ERROR(REQUEST_FAILED, message));  // emit the failure now
            }

            // return the resulting identifier
            return identifier;
        }
    };

}  // namespace XLSP::Server

#endif
