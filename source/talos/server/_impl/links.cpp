/// Talos Modules
#include "talos/module/service.hpp"
#include "talos/relint/metadata.hpp"
#include "talos/server/connection.hpp"
#include "talos/server/style.hpp"

//  EVENT METHODS  //

void Talos::Server::Events::on_document_links(XLSP_REQUEST(DOCUMENT_LINKS) request) {
    // prepare the links details to be used
    auto resource = request.params.identifier.resource;

    // show that a format was requested
    $_TRACE("--| links: requested '{0}'", resource.relative());

    // get the incoming modules service to use
    auto* modules = m_connection->service<Import::Service>();

    // prepare an empty response to be returned
    auto response = XLSP_RESPONSE(DOCUMENT_LINKS);

    // start by resolving the node at the resource/position now
    if (auto* mirrors = m_utilities->syntax_view_at(resource)) {
        // prepare all the available import statements
        auto imports = mirrors->filter<Syntax::Import>();

        // pre-size the response (assuming all imports succeed)
        response.links.reserve(imports.size());

        // iterate over them to collapse into suitable links
        for (const auto* import : imports) {
            auto result = modules->resolve(import->path(), resource.body());
            if (!result.has_value() || result->scheme() != $::URI::Scheme::FILE) continue;

            auto range = import->traits()->range().client();  // resolve
            response.links.emplace_back(XLSP::Anchor(*result, range));
        }
    }

    // and ensure we reply as expected now
    request.reply(std::move(response));
}
