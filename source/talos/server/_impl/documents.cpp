/// Talos Modules
#include "talos/document/service.hpp"
#include "talos/module/service.hpp"
#include "talos/runtime/options.hpp"
#include "talos/server/connection.hpp"

//  EVENT METHODS  //

void Talos::Server::Events::on_document_opened(const XLSP_NOTIFICATION(DOCUMENT_OPENED) & params) {
    on_document_changed(XLSP_NOTIFICATION(DOCUMENT_CHANGED)(params.document.identifier()));
}

void Talos::Server::Events::on_document_closed(const XLSP_NOTIFICATION(DOCUMENT_CLOSED) & params) {
    auto* documents = m_connection->service<Document::Service>();
    documents->remove(params.identifier.resource);  // remove now
}

void Talos::Server::Events::on_document_changed(const XLSP_NOTIFICATION(DOCUMENT_CHANGED) & params) {
    // prepare the underlying documents container here
    auto* documents = m_connection->service<Document::Service>();

    // attempt re-constructing the buffer we require now
    auto buffer = documents->resolve(params.identifier.resource);
    auto content = $::String::Buffer(buffer->view());  // copy
    auto encoding = m_connection->options()->server.encoding;

    // iteratively update the buffer as necessary
    for (const auto& change : params.changes) change.apply(content, encoding);

    // update the document (this will also reset the drafts module)
    documents->update(params.identifier.resource, content);

    // and request a rebuild of the underlying module graph
    m_connection->schedule(params.identifier.resource, [](Worker* worker) { worker->analyze(false); });
}
