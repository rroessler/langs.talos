/// Talos Modules
#include "talos/server/connection.hpp"

//  EVENT METHODS  //

void Talos::Server::Events::on_document_completes(XLSP_REQUEST(DOCUMENT_COMPLETIONS) request) {
    // since this relies on an updated set of modules, we guard the connection
    $_UNUSED $_AUTO = m_connection->guard();

    // destructure the incoming items to be used
    auto position = request.params.position;
    auto resource = request.params.identifier.resource;

    // show that a message was requested
    $_TRACE("--| completions: requested '{0}:{1}'", resource.relative(), position);

    // prepare the response to be used
    auto response = XLSP_RESPONSE(DOCUMENT_COMPLETIONS);

    // resolve the incoming node that is being completed (expecting an identifier)
    if (auto* node = m_utilities->syntax_node_at<Syntax::Identifier>(resource, position)) {
        // show that we found a node that we could use for our completions handler now
        $_TRACE("--| completions: found node '{0}' at {1}", node->canonical(), node->range());
    }

    // and ensure we reply as expected now
    request.reply(std::move(response));
}
