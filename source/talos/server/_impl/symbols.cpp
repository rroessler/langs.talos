/// Talos Modules
#include "talos/server/connection.hpp"

//  EVENT METHODS  //

void Talos::Server::Events::on_document_symbols(XLSP_REQUEST(DOCUMENT_SYMBOLS) request) {
    // destructure the incoming items to be used
    auto resource = request.params.identifier.resource;

    // show that a message was requested
    $_TRACE("--| symbols: requested '{0}'", resource);

    // prepare the symbols response to be used
    auto response = XLSP_RESPONSE(DOCUMENT_SYMBOLS);

    // and ensure we reply as expected now
    request.reply(std::move(response));
}
