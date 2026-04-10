/// Talos Modules
#include "talos/server/connection.hpp"

/// Syntax Modules
#include "talos/syntax/annotation/qualifier.hpp"

//  EVENT METHODS  //

void Talos::Server::Events::on_document_vardef(XLSP_REQUEST(DOCUMENT_VARIABLE_DEFINITION) request) {
    // since this relies on an updated set of modules, we guard the connection
    $_UNUSED $_AUTO = m_connection->guard();

    // destructure the incoming items to be used
    auto position = request.params.position;
    auto resource = request.params.identifier.resource;

    // show that a message was requested
    $_TRACE("--| vardef: requested '{0}:{1}'", resource.relative(), position);

    // prepare the response to be used
    auto response = XLSP_RESPONSE(DOCUMENT_VARIABLE_DEFINITION);

    // attempt resolving a suitable node to be used now
    if (auto* node = m_utilities->vardef_node_at(resource, position)) {
        $_TRACE("--| vardef: found node '{0}' at {1}", node->canonical(), node->range());
        response.locations.emplace_back(m_utilities->syntax_to_client(node));  // emit
    }

    // and ensure we reply as expected now
    request.reply(std::move(response));
}

void Talos::Server::Events::on_document_typedef(XLSP_REQUEST(DOCUMENT_TYPE_DEFINITION) request) {
    // since this relies on an updated set of modules, we guard the connection
    $_UNUSED $_AUTO = m_connection->guard();

    // destructure the incoming items to be used
    auto position = request.params.position;
    auto resource = request.params.identifier.resource;

    // show that a message was requested
    $_TRACE("--| typedef: requested '{0}:{1}'", resource.relative(), position);

    // prepare the response to be used
    auto response = XLSP_RESPONSE(DOCUMENT_TYPE_DEFINITION);

    // attempt resolving a suitable node to be used now
    if (auto* node = m_utilities->typedef_node_at(resource, position)) {
        $_TRACE("--| typedef: found node '{0}' at {1}", node->canonical(), node->range());
        response.locations.emplace_back(m_utilities->syntax_to_client(node));  // emit
    }

    // and ensure we reply as expected now
    request.reply(std::move(response));
}
