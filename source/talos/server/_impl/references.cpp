/// Talos Modules
#include "talos/server/connection.hpp"

//  EVENT METHODS  //

void Talos::Server::Events::on_document_references(XLSP_REQUEST(DOCUMENT_REFERENCES) request) {
    // destructure the incoming items to be used
    auto position = request.params.position;
    auto resource = request.params.identifier.resource;

    // show that a message was requested
    $_TRACE("--| references: requested '{0}:{1}'", resource, position);

    // prepare the response to be used
    auto response = XLSP_RESPONSE(DOCUMENT_REFERENCES);

    // prepare a handler for emitting references
    auto append = [&](const Relint::Mirror* mirror) {
        auto range = m_utilities->range_to_client(mirror->range());
        auto location = XLSP::Location(resource, range);
        response.locations.emplace_back(std::move(location));
    };

    // attempt resolving the baseline syntax node
    auto* node = m_utilities->syntax_node_at(resource, position);
    if (node == nullptr) return request.reply(std::move(response));

    // attempt getting the associated definition details now
    auto definition = node ? node->definition() : Relint::Empty.get();

    // start by resolving the node at the resource/position now
    if (auto* source = node->qualified() ? definition->annotation : definition->variable) {
        // trace what we actually found for debug viewing
        $_TRACE("--| references: found node '{0}' at {1}", node->canonical(), node->range());

        // always prepend the base definition to be used
        append(source);

        // get the available references that we have found
        auto references = source->references();

        // if we have lots of references then we want to pre-build the size
        response.locations.reserve(references.size() + 1);

        // get all the available node references and fill the result
        for (const auto& reference : references) append(reference);
    }

    // and ensure we reply as expected now
    request.reply(std::move(response));
}
