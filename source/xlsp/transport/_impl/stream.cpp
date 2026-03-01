/// XLSP Modules
#include "xlsp/transport/stream.hpp"
#include "xlsp/event/dispatcher.hpp"

//  PUBLIC METHODS  //

int32_t XLSP::Transport::Stream::listen(Event::Dispatcher* events) {
    // prepare the base buffer to be used
    $::String::Buffer buffer;

    // attempt looping whilst not the end-of-stream
    while (!m_input.eof()) {
        // ensure we have no current errors in our stream
        if (m_input.bad()) return std::error_code(errno, std::system_category()).value();

        // attempt reading the current message now
        if (!m_read(buffer)) continue;

        // parse the incoming message
        auto message = $::JSON::parse(buffer);

        // get the current shutdown details
        auto result = message.has_value() ? m_dispatch(message.value(), events) : false;

        // handle the response as necessary
        if (!message.has_value()) $_WARN("{0}", message.error());
        else if (!result.has_value()) $_ERROR("{0}", result.error());
        else if (!*result) return std::error_code().value();  // exit now
    }

    // received an IO error here (since stream was invalid)
    return std::make_error_code(std::errc::io_error).value();
}

//  PRIVATE METHODS  //

bool XLSP::Transport::Stream::m_read($::String::Buffer& buffer) {
    // prepare some details for reading now
    uint64_t length = 0;
    $::String::Buffer json = "";

    // attempt reading the incoming data
    for (;;) {
        // stop on any incoming errors found
        if (m_input.eof() || m_input.bad()) return false;

        // get a reference to the current line now
        std::getline(m_input, json);
        $::String::View line = json;

        // remove any leading white-space
        line = $::Trim::leading(line);

        // stop early if we have an empty line
        if (line.empty()) break;

        // we allow comments in the header
        if (line.starts_with('#')) continue;

        // content-length is a mandatory header to be used
        if (line.starts_with(JRPC::LENGTH)) {
            line.remove_prefix(JRPC::LENGTH.size());
            length = std::stoull(line.data());
        }
    }

    // refuse under certain conditions
    if (length == 0) return false;
    if (length > 1 << 30) return false;

    // resize our output buffer now
    buffer.resize(length);

    // and attempt reading our JSON string now
    return m_input.read(&buffer[0], length).gcount();
}

std::expected<bool, XLSP::Message::Error> XLSP::Transport::Stream::m_dispatch(
    const $::Serde::Value& message, Event::Dispatcher* events) {
    // ensure we have a suitable object instance now
    if (!message.is<$::Serde::Object>()) return m_fail("Expected a JSON object");

    // attempt getting underlying values now
    auto* version = message.at<$::Serde::Text>(JRPC::KEY);

    // attempt parsing our necessary details now
    if (version == nullptr || *version != JRPC::VERSION) return m_fail("Expected JRPC version {0}", JRPC::VERSION);

    // get the base details now of the message
    auto id = *$::JSON::stringify(message.at("id"));
    auto* method = message.at<$::Serde::Text>("method");

    // check for responses firstly
    if (method == nullptr) {
        // fail if we have a bad identifier value
        if (id == "null") return m_fail("Empty response identifier");

        // attempt parsing suitable results or errors now
        if (message.has("result")) return events->on_response(id, message.at("result"));
        else if (!message.has("error")) return m_fail("Empty response message");

        // construct the final response as necessary now (since an error occured)
        return events->on_response(id, $::Reflect::decode<Message::Error>(message.at("error")));
    }

    // get the underlying parameters object now
    auto params = message.at("params");

    // attempt formulating our desired dispatch necessary
    if (id == "null") return events->on_notify(*method, params);
    return events->on_request(id, *method, params);  // requests
}

/**
 * @brief Emits outgoing messages.
 * @param message                   Message to emit.
 */
void XLSP::Transport::Stream::m_send($::Serde::Object message) {
    // update the JRPC details to be used
    message.emplace(JRPC::KEY, JRPC::VERSION);

    // serialize our outgoing message now
    auto buffer = *$::JSON::stringify(message);

    fmt::print(m_output, "{0}{1}{2}{3}", JRPC::LENGTH, buffer.size(), JRPC::EOM, buffer);
    m_output.flush();  // attempt flushing the output stream now when requested to do so
}
