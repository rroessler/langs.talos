#ifndef _XLSP_TRANSPORT_STREAM_HPP
#define _XLSP_TRANSPORT_STREAM_HPP

/// C++ Modules
#include <expected>

/// XLSP Modules
#include "xlsp/message/error.hpp"
#include "xlsp/transport/abstract.hpp"

namespace XLSP::Transport {

    /// @brief Stream Transport Implementation.
    class Stream : public Abstract {
        //  PROPERTIES  //

        $::String::View m_name;       // Name of stream.
        $::Stream::Input& m_input;    // Input stream.
        $::Stream::Output& m_output;  // Output stream.

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a stream transport.
         * @param input                     Input stream.
         * @param output                    Output stream.
         * @param name                      Name of stream.
         */
        explicit Stream($::Stream::Input& input, $::Stream::Output& output, const $::String::View& name = "<unknown>") :
            m_name(name), m_input(input), m_output(output) {}

        //  PUBLIC METHODS  //

        /**
         * @brief Handles listening to JSON-RPC events.
         * @param events                    Events delegate.
         */
        int32_t listen(Event::Dispatcher* events) final;

        /// @brief Transport title to inherit.
        inline $::String::View label() const final { return m_name; }

        /**
         * @brief Emits an outgoing notification.
         * @param method                    Notification method.
         * @param params                    Notification parameters.
         */
        inline void notify(const Message::Method& method, const Message::Params& params) final {
            m_send({ { "method", method }, { "params", params } });
        }

        /**
         * @brief Emits an outgoing request.
         * @param id                        Request id.
         * @param method                    Request method.
         * @param params                    Request parameters.
         */
        inline void request(
            const Request::Identifier& id, const Message::Method& method, const Message::Params& params) final {
            $::Serde::Object message = { { "method", method }, { "params", params } };
            message.emplace("id", $::JSON::parse(id).value()), m_send(message);
        }

        /**
         * @brief Emits an outgoing response.
         * @param id                        Response id.
         * @param result                    Response result.
         */
        void respond(const Request::Identifier& id, const Message::Result<$::Serde::Value>& result) final {
            auto message = $::Serde::Object();  // build the base message
            if (auto* value = std::get_if<$::Serde::Value>(&result)) message.emplace("result", *value);
            else message.emplace("error", $::Reflect::encode(std::get<Message::Error>(result)));
            message.emplace("id", $::JSON::parse(id).value()), m_send(message);  // and emit
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Attempts reading into the buffer.
         * @param buffer                    Buffer to output.
         */
        bool m_read($::String::Buffer& buffer);

        /**
         * @brief Emits outgoing messages.
         * @param message                   Message to emit.
         */
        void m_send($::Serde::Object message);

        /**
         * @brief Attempts delegating incoming messages.
         * @param message                   Message to emit.
         * @param events                    Events dispatcher.
         */
        std::expected<bool, Message::Error> m_dispatch(const $::Serde::Value& message, Event::Dispatcher* events);

        /**
         * @brief Handles constructing parsing failures.
         * @param format                    Error message.
         * @param args                      Message arguments.
         */
        template <class... As>
        inline std::expected<bool, Message::Error> m_fail(fmt::format_string<As...> format, As&&... args) const {
            static constexpr auto code = Message::Error::Code::PARSE_ERROR;
            auto message = fmt::format(format, std::forward<As>(args)...);
            return std::unexpected(Message::Error(code, message));
        }
    };

}  // namespace XLSP::Transport

#endif
