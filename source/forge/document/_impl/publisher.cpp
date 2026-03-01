/// Forge Modules
#include "forge/document/publisher.hpp"
#include "forge/crate/service.hpp"
#include "forge/module/service.hpp"
#include "forge/server/connection.hpp"

//  PUBLIC METHODS  //

void Forge::Document::Publisher::clear(const $::URI::View& resource) {
    publish(resource, {});  // remove resource here now
    if (auto* drafts = m_drafts()) drafts->remove(resource);
}

void Forge::Document::Publisher::update(const $::URI::View& resource) {
    if (auto* drafts = m_drafts()) drafts->remove(resource);
}

void Forge::Document::Publisher::publish(
    const $::URI::View& resource, const std::vector<XLSP::Diagnostic>& diagnostics) {
    using Notification = typename XLSP_NOTIFICATION(PUBLISH_DIAGNOSTICS);  // prepare typing now
    if (auto* connection = m_connection()) connection->notify(Notification(resource, diagnostics));
}

//  PRIVATE METHODS  //

Forge::Import::Drafts* Forge::Document::Publisher::m_drafts() {
    // ensure the underlying services container is valid first
    if (m_services == nullptr) return nullptr;

    // then ensure the services has a server connection
    if (!m_services->exists<Import::Service>()) return nullptr;

    // attempt resolving the final connection now
    return m_services->get<Import::Service>()->drafts();
}

Forge::Server::Connection* Forge::Document::Publisher::m_connection() {
    return m_services ? m_services->when<Server::Connection>() : nullptr;
}
