/// Talos Includes
#include "talos/document/publisher.hpp"
#include "talos/import/service.hpp"
#include "talos/runtime/container.hpp"
#include "talos/server/connection.hpp"

//  CONSTRUCTORS  //

Talos::Document::Publisher::Publisher() : Publisher($::Global::get<Runtime::Container>()) {}
Talos::Document::Publisher::Publisher(XI::Container *services) :
    m_services(services), m_connection(services->when<Server::Connection>()) {}

//  PUBLIC METHODS  //

void Talos::Document::Publisher::clear(const $::URI::View &resource) {
  publish(resource, {}); // remove resource here now as needed
}

void Talos::Document::Publisher::refresh(const $::URI::View &resource) {
  if (auto *modules = m_modules()) modules->storage()->remove(resource);
}

void Talos::Document::Publisher::refresh(const std::vector<$::URI::View> &resources) {
  for (const auto &resource : resources) refresh(resource);
}

void Talos::Document::Publisher::refresh(const std::vector<$::URI::Buffer> &resources) {
  for (const auto &resource : resources) refresh(resource);
}

void Talos::Document::Publisher::publish(
    const $::URI::View &resource, const std::vector<XLSP::Diagnostic> &diagnostics
) {
  using Notification = Server::Notification::DIAGNOSTICS_PUBLISH; // prepare typing
  if (m_connection) m_connection->notify(Notification(resource.buffer(), diagnostics));
}

//  PRIVATE METHODS  //

Talos::Import::Service *Talos::Document::Publisher::m_modules() noexcept {
  return m_services && m_connection ? m_services->get<Import::Service>() : nullptr;
}
