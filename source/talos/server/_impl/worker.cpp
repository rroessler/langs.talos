/// Talos Modules
#include "talos/server/worker.hpp"
#include "talos/document/service.hpp"
#include "talos/module/service.hpp"
#include "talos/server/connection.hpp"

//  PUBLIC METHODS  //

const Talos::Server::Utilities* Talos::Server::Worker::utilities() const noexcept { return m_connection->utilities(); }

void Talos::Server::Worker::analyze(Refresh mode) const noexcept {
    // we always lock the service when it is being analyzed
    $_UNUSED $_AUTO = m_connection->guard();

    // declare that we are analyzing the incoming item
    $_TRACE("--| analyze: requested '{0}'", m_resource.relative());

    // attempt getting the document service
    auto* modules = m_connection->service<Import::Service>();
    auto* documents = m_connection->service<Document::Service>();

    // get the underlying modules to be analyzed now
    auto resources = documents->opened();

    // prepare the publisher to be used now
    auto* publisher = documents->publisher();

    // handle refreshes based on the incoming mode
    switch (mode) {
        default: break;  // ignore coordinting refreshing when stale
        case Refresh::PARTIAL: publisher->refresh(m_resource); break;

        // only in the entire case do we worry about refreshing all items
        case Refresh::FULL: {
            for (const auto& resource : resources) publisher->refresh(resource);
        } break;
    }

    // attempt analyzing each resource as needed
    auto elapsed = $::Clock::Measure([&] { modules->analyze(resources, false); });
    $_TRACE("--| analyze: elapsed time {0}", elapsed);  // show measured time

    // finally refresh the necessary diagnostics
    for (const auto& resource : resources) {
        auto* module = modules->fetch(resource);      // attempt getting
        if ($_UNLIKELY(module == nullptr)) continue;  // failed to get
        publisher->publish(resource, module->reporter()->view());
    }
}
