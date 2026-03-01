/// Forge Modules
#include "forge/server/connection.hpp"
#include "forge/server/style.hpp"

//  EVENT METHODS  //

void Forge::Server::Events::on_document_hover(XLSP_REQUEST(DOCUMENT_HOVER) request) {
    // prepare the hove details to be used
    auto hover = request.params;

    // destructure the incoming items to be used
    auto position = hover.position;
    auto resource = hover.identifier.resource;

    // show that a format was requested
    $_TRACE("--| hover: requested '{0}:{1}'", resource, position);

    // prepare an empty response to be returned
    auto response = XLSP_RESPONSE(DOCUMENT_HOVER);

    // start by resolving the node at the resource/position now
    if (auto* mirror = m_utilities->syntax_node_at(resource, position)) {
        // trace what we actually found for debug viewing
        $_TRACE("--| hover: found node '{0}' at {1}", mirror->canonical(), mirror->range());

        // prepare the properties we use for hover outputs
        auto typing = Style::typing(mirror);

        // prepare all of the output segments to be used
        auto sections = std::vector<$::String::Buffer>();

        // prepare hover response details now
        response.range = m_utilities->range_to_client(mirror->range());
        response.contents = $::New().unique<XLSP::Markup::Formatted>();

        // attempt binding the current typing to the top of the value
        if (typing.size()) sections.emplace_back(XLSP::Markup::Code(typing, FORGE_MM_IDENTIFIER));
        if (auto comments = mirror->comments(); comments.size()) sections.emplace_back(comments);

        // and finally write each of our sections to the response
        response.contents->stream() << $::Convert::join(sections, "\n");
    }

    // and ensure we reply as expected now
    request.reply(std::move(response));
}
