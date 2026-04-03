/// Talos Modules
#include "talos/server/connection.hpp"

/// Forward Declarations
$_FWD(Talos::Server::Encoding, XLSP::Encoding::Type query(const $::Serde::Value&))

//  PUBLIC METHODS  //

/**
 * @brief Handles parsing a suitable position-encoding.
 * @param capabilities                  Capabilities to parse.
 */
XLSP::Encoding::Type Talos::Server::Encoding::query(const $::Serde::Value& capabilities) {
    auto general = capabilities.at("general");  // get the general details
    if (!general.is<$::Serde::Object>()) return XLSP::Encoding::Type::UTF16;

    // attempt getting the underlying offset-encoding values
    auto encodings = general.at("positionEncodings");
    if (!encodings.is<$::Serde::Array>()) return XLSP::Encoding::Type::UTF16;

    // should be able to iterate over the position encodings now
    for (const auto& value : *encodings.as<$::Serde::Array>()) {
        if (!value.is<$::String::Buffer>()) continue;  // invalid value
        auto encoding = XLSP::Encoding::resolve(*value.as<$::Serde::Text>());

        // intentionally prefer anything other than UTF-16
        switch (encoding) {
            case XLSP::Encoding::Type::UTF8: $_FALLTHROUGH;
            case XLSP::Encoding::Type::UTF32: return encoding;
            default: break;  // get the next availabale value
        }
    }

    // fallback should now be UTF-16
    return XLSP::Encoding::Type::UTF16;
}

//  EVENT METHODS  //

void Talos::Server::Events::on_initialize(XLSP_REQUEST(LIFECYCLE_INITIALIZE) request) {
    // get the base encoding details and update them as necessary for the server
    auto* encoding = const_cast<XLSP::Encoding::Type*>(&m_connection->options()->server.encoding);
    if (*encoding == XLSP::Encoding::Type::INVALID) *encoding = Encoding::query(request.params.capabilities);

    // forcibly update the underlying encoding value now to be used
    m_connection->service<Runtime::Options>()->diagnostics.encoding = *encoding;

    // prepare some necessary handlers now
    auto bind = m_connection->binder();

    // bind all the base events to be ignored
    bind.on_notify(this, &Events::m_ignore<XLSP::Message::Type::TRACE_SET>);
    bind.on_notify(this, &Events::m_ignore<XLSP::Message::Type::LIFECYCLE_INITIALIZED>);

    // bind all the document events to be handled
    bind.on_notify(this, &Events::on_document_opened);
    bind.on_notify(this, &Events::on_document_closed);
    bind.on_notify(this, &Events::on_document_changed);
    bind.on_notify(this, &Events::on_workspace_watcher);

    // and bind all the requests that we want to handle
    bind.on_request(this, &Events::on_document_hover);
    bind.on_request(this, &Events::on_document_links);
    bind.on_request(this, &Events::on_document_format);
    bind.on_request(this, &Events::on_document_symbols);
    bind.on_request(this, &Events::on_document_vardef);
    bind.on_request(this, &Events::on_document_typedef);
    bind.on_request(this, &Events::on_document_completes);

    auto response = XLSP_RESPONSE(LIFECYCLE_INITIALIZE);
    response.server = XLSP::Process::Information();

    // set the base details to be used now
    response.server->name = m_connection->options()->server.title;
    response.server->version = m_connection->options()->server.version;

    // update the current capabilities now
    response.capabilities["hoverProvider"] = true;
    response.capabilities["documentFormattingProvider"] = true;
    response.capabilities["documentLinkProvider"] = { { "resolveProvider", false } };
    response.capabilities["positionEncoding"] = XLSP::Encoding::format(*encoding);
    response.capabilities["textDocumentSync"] = {
        { "save", false },
        { "openClose", true },
        { "change", XLSP::Document::Sync::FULL },
    };

    // return the final result now
    request.reply(response);
}

void Talos::Server::Events::on_shutdown(XLSP_REQUEST(LIFECYCLE_SHUTDOWN, XLSP::Event::Answer) request) {
    request.reply($::Serde::Null()), m_connection->shutdown();
}
