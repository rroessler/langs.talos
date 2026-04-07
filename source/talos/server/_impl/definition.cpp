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
    $_TRACE("--| vardef: requested '{0}:{1}'", resource, position);

    // prepare the response to be used
    auto response = XLSP_RESPONSE(DOCUMENT_VARIABLE_DEFINITION);

    // attempt resolving the source and definition as well
    auto* node = m_utilities->syntax_node_at(resource, position);

    // only allow emitting variable-definitions if we have a valid target
    if (auto* source = node && !node->qualified() ? node->definition()->variable : nullptr) {
        // show to developers what we have actually found so far now
        $_TRACE("--| vardef: found node '{0}' at {1}", node->canonical(), node->range());

        // convert our details as necessary now for the incoming source
        auto range = m_utilities->range_to_client(source->range());
        response.locations.emplace_back(XLSP::Location(resource, range));
    }

    // and ensure we reply as expected now
    request.reply(std::move(response));
}

void Talos::Server::Events::on_document_typedef(XLSP_REQUEST(DOCUMENT_TYPE_DEFINITION) request) {
    // destructure the incoming items to be used
    auto position = request.params.position;
    auto resource = request.params.identifier.resource;

    // show that a message was requested
    $_TRACE("--| typedef: requested '{0}:{1}'", resource, position);

    // prepare the response to be used
    auto response = XLSP_RESPONSE(DOCUMENT_TYPE_DEFINITION);

    // attempt resolving the source and definition as well
    auto* node = m_utilities->syntax_node_at(resource, position);

    // only allow emitting type-definitions if we have a valid target
    if (auto* source = node && node->qualified() ? node->definition()->annotation : nullptr) {
        // show to developers what we have actually found so far now
        $_TRACE("--| typedef: found node '{0}' at {1}", node->canonical(), node->range());

        // convert our details as necessary now for the incoming source
        auto range = m_utilities->range_to_client(source->range());
        response.locations.emplace_back(XLSP::Location(resource, range));
    }

    // and ensure we reply as expected now
    request.reply(std::move(response));
}
