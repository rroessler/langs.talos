/// Talos Modules
#include "talos/toolchain/format.hpp"
#include "talos/document/service.hpp"
#include "talos/server/connection.hpp"

//  EVENT METHODS  //

void Talos::Server::Events::on_document_format(XLSP_REQUEST(DOCUMENT_FORMAT) request) {
    m_connection->schedule(request.params.identifier.resource, [reply = std::move(request.reply)](Worker* worker) {
        auto response = XLSP_RESPONSE(DOCUMENT_FORMAT);  // prepare
        response.edits = worker->format(), reply(std::move(response));
    });
}

std::vector<XLSP::Document::Edit> Talos::Server::Worker::format() const noexcept { return format(m_crate->format()); }
std::vector<XLSP::Document::Edit> Talos::Server::Worker::format(const Format::Options& options) const noexcept {
    // show that a format was requested
    $_TRACE("--| format: requested '{0}'", m_resource.relative());

    // get some necessary services to be used
    auto* documents = m_connection->service<Document::Service>();

    // get the source to be used now
    auto source = documents->resolve(m_resource);

    // and attempt running the formatter now
    auto [result, elapsed] = $::Clock::Measure.apply([&] { return Toolchain::format(*source, options); });
    $_TRACE("--| format: elapsed time {0}", elapsed);  // show the total elapsed time formatting

    // if the result failed, then stop handling
    if (!result.has_value()) return {};

    // count the total lines of the source
    uint32_t lines = std::ranges::count(source->view(), '\n');
    XLSP::Range range = { XLSP::Position(), { lines + 1, 0 } };

    // return the final edits to be used now
    return { XLSP::Document::Edit(*result, range) };
}
