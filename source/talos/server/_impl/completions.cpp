/// Talos Modules
#include "talos/server/connection.hpp"

//  EVENT METHODS  //

void Talos::Server::Events::on_document_completes(XLSP_REQUEST(DOCUMENT_COMPLETIONS) request) {
    // destructure the incoming items to be used
    auto position = request.params.position;
    auto resource = request.params.identifier.resource;

    // show that a message was requested
    $_TRACE("--| completions: requested '{0}:{1}'", resource, position);

    // prepare the response to be used
    auto response = XLSP_RESPONSE(DOCUMENT_COMPLETIONS);

    // and ensure we reply as expected now
    request.reply(std::move(response));
}
