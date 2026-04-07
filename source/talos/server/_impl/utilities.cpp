/// Talos Modules
#include "talos/server/utilities.hpp"
#include "talos/document/service.hpp"
#include "talos/module/service.hpp"
#include "talos/runtime/container.hpp"
#include "talos/type/metadata.hpp"

//  CONSTRUCTORS  //

Talos::Server::Utilities::Utilities() : Utilities($::Global::get<Runtime::Container>()) {}
Talos::Server::Utilities::Utilities(XI::Container* services) : m_services(services) {}

//  PUBLIC METHODS  //

XLSP::Range Talos::Server::Utilities::range_to_client(const XLSP::Range& range) const {
    if (range == XLSP::Range()) return range;  // ignore if we have base range
    return { position_to_client(range.start), position_to_client(range.end) };
}

XLSP::Range Talos::Server::Utilities::range_to_server(const XLSP::Range& range) const {
    return { position_to_server(range.start), position_to_server(range.end) };
}

XLSP::Position Talos::Server::Utilities::position_to_client(const XLSP::Position& position) const {
    if (position == XLSP::Position()) return position;
    return { position.line - 1, position.column - 1 };
}

XLSP::Position Talos::Server::Utilities::position_to_server(const XLSP::Position& position) const {
    return { position.line + 1, position.column + 1 };
}

const Talos::Relint::Metadata* Talos::Server::Utilities::syntax_view_at(const $::URI::View& resource) const {
    Import::Service* modules = *m_services;  // resolve
    auto* found = modules->drafts()->lookup(resource);
    if (found == nullptr) return nullptr;  // failed
    auto* metadata = found->metadata<Module::Phase::TYPED>();
    return metadata->context()->mirrors().get();  // resolved
}

const Talos::Relint::Mirror* Talos::Server::Utilities::syntax_node_at(
    const $::URI::View& resource, const XLSP::Position& position) const {
    auto* mirrors = syntax_view_at(resource);
    if (mirrors == nullptr) return nullptr;
    auto normalized = position_to_server(position);
    return mirrors->search(normalized);  // search
}
