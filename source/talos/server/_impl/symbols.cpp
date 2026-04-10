/// Talos Modules
#include "talos/relint/metadata.hpp"
#include "talos/server/connection.hpp"

//  EVENT METHODS  //

void Talos::Server::Events::on_document_symbols(XLSP_REQUEST(DOCUMENT_SYMBOLS) request) {
    // symbols requires modules to be ready
    $_UNUSED $_AUTO = m_connection->guard();

    // destructure the incoming items to be used
    auto resource = request.params.identifier.resource;

    // show that a message was requested
    $_TRACE("--| symbols: requested '{0}'", resource.relative());

    // prepare the symbols response to be used
    auto response = XLSP_RESPONSE(DOCUMENT_SYMBOLS);

    // only bind the symbols if possible to do so
    auto* mirrors = m_utilities->syntax_view_at(resource);
    if (mirrors) response.symbols = mirrors->symbols();

    // and ensure we reply as expected now
    request.reply(std::move(response));
}
