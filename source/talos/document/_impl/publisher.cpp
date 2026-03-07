/// Talos Modules
#include "talos/document/publisher.hpp"
#include "talos/crate/service.hpp"
#include "talos/module/service.hpp"
#include "talos/server/connection.hpp"

//  PUBLIC METHODS  //

void Talos::Document::Publisher::clear(const $::URI::View& resource) {
    publish(resource, {});  // remove resource here now
    if (auto* drafts = m_drafts()) drafts->remove(resource);
}

void Talos::Document::Publisher::update(const $::URI::View& resource) {
    if (auto* drafts = m_drafts()) drafts->remove(resource);
}

void Talos::Document::Publisher::publish(
    const $::URI::View& resource, const std::vector<XLSP::Diagnostic>& diagnostics) {
    using Notification = typename XLSP_NOTIFICATION(PUBLISH_DIAGNOSTICS);  // prepare typing now
    if (auto* connection = m_connection()) connection->notify(Notification(resource, diagnostics));
}

//  PRIVATE METHODS  //

Talos::Import::Drafts* Talos::Document::Publisher::m_drafts() {
    // ensure the underlying services container is valid first
    if (m_services == nullptr) return nullptr;

    // then ensure the services has a server connection
    if (!m_services->exists<Import::Service>()) return nullptr;

    // attempt resolving the final connection now
    return m_services->get<Import::Service>()->drafts();
}

Talos::Server::Connection* Talos::Document::Publisher::m_connection() {
    return m_services ? m_services->when<Server::Connection>() : nullptr;
}
