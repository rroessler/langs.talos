/// Talos Modules
#include "talos/server/connection.hpp"

//  EVENT METHODS  //

void Talos::Server::Events::on_document_references(XLSP_REQUEST(DOCUMENT_REFERENCES) request) {
    // since this relies on an updated set of modules, we guard the connection
    $_UNUSED $_AUTO = m_connection->guard();

    // destructure the incoming items to be used
    auto position = request.params.position;
    auto resource = request.params.identifier.resource;

    // show that a message was requested
    $_TRACE("--| references: requested '{0}:{1}'", resource.relative(), position);

    // prepare the response to be used
    auto response = XLSP_RESPONSE(DOCUMENT_REFERENCES);

    // prepare a handler for emitting references
    auto append = [&](const Relint::Mirror* mirror) {
        auto location = m_utilities->syntax_to_client(mirror);
        response.locations.emplace_back(std::move(location));
    };

    // start by resolving the node at the resource/position now
    if (auto* node = m_utilities->anydef_node_at(resource, position)) {
        // trace what we actually found for debug viewing
        $_TRACE("--| references: found node '{0}' at {1}", node->canonical(), node->range());

        // get the available references that we have found
        auto references = (append(node), node->references());

        // if we have lots of references then we want to update the size
        response.locations.reserve(references.size() + 1);

        // get all the available node references and fill the result
        for (const auto& reference : references) append(reference);
    }

    // and ensure we reply as expected now
    request.reply(std::move(response));
}
