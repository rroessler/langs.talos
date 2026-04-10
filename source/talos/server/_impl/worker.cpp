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
        // for stale mode refreshes we want to ignore handling
        case Refresh::STALE: break;

        // for singular refreshes we reset this resource
        case Refresh::SINGLE: publisher->refresh(m_resource); break;

        // for partial refreshes, we want to only update some items
        case Refresh::PARTIAL: publisher->refresh(resources); break;

        // for entire refreshes, we clear the underlying drafts
        case Refresh::ENTIRE: modules->drafts()->clear(); break;
    }

    // attempt analyzing each resource as needed
    auto elapsed = $::Clock::Measure([&] { modules->analyze(resources, false); });

    // show the measured time that we found for analysis
    $_TRACE("--| analyze: elapsed time {0}", elapsed);

    // finally refresh the necessary diagnostics
    for (const auto& resource : resources) {
        auto* module = modules->fetch(resource);      // attempt getting
        if ($_UNLIKELY(module == nullptr)) continue;  // failed to get
        publisher->publish(resource, module->reporter()->view());
    }
}
