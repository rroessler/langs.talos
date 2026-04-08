/// Talos Modules
#include "talos/server/connection.hpp"

/// Syntax Modules
#include "talos/syntax/annotation/qualifier.hpp"

//  EVENT METHODS  //

void Talos::Server::Events::on_document_vardef(XLSP_REQUEST(DOCUMENT_VARIABLE_DEFINITION) request) {
    // destructure the incoming items to be used
    auto position = request.params.position;
    auto resource = request.params.identifier.resource;

    // show that a message was requested
    $_TRACE("--| vardef: requested '{0}:{1}'", resource.relative(), position);

    // we need to prepare a suitable context to resolve details from
    m_connection->schedule(resource, [position, request = std::move(request)](Worker* worker) {
        // forcibly re-analyze the incoming module
        worker->analyze(Refresh::PARTIAL);

        // prepare the available utilities service
        auto* utilities = worker->utilities();

        // prepare the response to be used
        auto response = XLSP_RESPONSE(DOCUMENT_VARIABLE_DEFINITION);

        // attempt resolving a suitable node to be used now
        if (auto* node = utilities->vardef_node_at(worker->resource(), position)) {
            $_TRACE("--| vardef: found node '{0}' at {1}", node->canonical(), node->range());
            response.locations.emplace_back(utilities->syntax_to_client(node));  // emit
        }

        // and ensure we reply as expected now
        request.reply(std::move(response));
    });
}

void Talos::Server::Events::on_document_typedef(XLSP_REQUEST(DOCUMENT_TYPE_DEFINITION) request) {
    // destructure the incoming items to be used
    auto position = request.params.position;
    auto resource = request.params.identifier.resource;

    // show that a message was requested
    $_TRACE("--| typedef: requested '{0}:{1}'", resource.relative(), position);

    // we need to prepare a suitable context to resolve details from
    m_connection->schedule(resource, [position, request = std::move(request)](Worker* worker) {
        // forcibly re-analyze the incoming module
        worker->analyze(Refresh::PARTIAL);

        // prepare the available utilities service
        auto* utilities = worker->utilities();

        // prepare the response to be used
        auto response = XLSP_RESPONSE(DOCUMENT_TYPE_DEFINITION);

        // attempt resolving a suitable node to be used now
        if (auto* node = utilities->typedef_node_at(worker->resource(), position)) {
            $_TRACE("--| typedef: found node '{0}' at {1}", node->canonical(), node->range());
            response.locations.emplace_back(utilities->syntax_to_client(node));  // emit
        }

        // and ensure we reply as expected now
        request.reply(std::move(response));
    });
}
