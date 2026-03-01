/// Forge Modules
#include "forge/server/utilities.hpp"
#include "forge/document/service.hpp"
#include "forge/module/service.hpp"
#include "forge/runtime/container.hpp"
#include "forge/type/metadata.hpp"

//  CONSTRUCTORS  //

Forge::Server::Utilities::Utilities() : Utilities($::Global::get<Runtime::Container>()) {}
Forge::Server::Utilities::Utilities(XI::Container* services) : m_services(services) {}

//  PUBLIC METHODS  //

XLSP::Range Forge::Server::Utilities::range_to_client(const XLSP::Range& range) const {
    if (range == XLSP::Range()) return range;  // ignore if we have base range
    return { position_to_client(range.start), position_to_client(range.end) };
}

XLSP::Range Forge::Server::Utilities::range_to_server(const XLSP::Range& range) const {
    return { position_to_server(range.start), position_to_server(range.end) };
}

XLSP::Position Forge::Server::Utilities::position_to_client(const XLSP::Position& position) const {
    if (position == XLSP::Position()) return position;
    return { position.line - 1, position.column - 1 };
}

XLSP::Position Forge::Server::Utilities::position_to_server(const XLSP::Position& position) const {
    return { position.line + 1, position.column + 1 };
}

const Forge::Relint::Metadata* Forge::Server::Utilities::syntax_view_at(const $::URI::View& resource) const {
    auto* imports = m_services->get<Import::Service>();
    auto* module = imports->drafts()->lookup(resource);
    if (module == nullptr) return nullptr;  // failed

    auto* metadata = module->metadata<Module::Phase::TYPED>();
    return metadata->context()->mirrors().get();  // resolved
}

const Forge::Relint::Mirror* Forge::Server::Utilities::syntax_node_at(
    const $::URI::View& resource, const XLSP::Position& position) const {
    auto* mirrors = syntax_view_at(resource);
    if (mirrors == nullptr) return nullptr;
    auto normalized = position_to_server(position);
    return mirrors->search(normalized);  // search
}
