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

XLSP::Location Talos::Server::Utilities::syntax_to_client(const Relint::Mirror* mirror) const {
    return syntax_to_client(mirror->origin());
}

XLSP::Location Talos::Server::Utilities::syntax_to_client(const Syntax::Node* node) const {
    return { node->traits()->resource().buffer(), node->traits()->range().client() };
}

const Talos::Relint::Metadata* Talos::Server::Utilities::syntax_view_at(const $::URI::View& resource) const {
    Import::Service* modules = *m_services;  // resolve
    auto* found = modules->drafts()->lookup(resource);
    if (found == nullptr) return nullptr;  // failed
    auto* metadata = found->metadata<Module::Phase::TYPED>();
    return metadata->context()->mirrors().get();  // resolved
}

const Talos::Relint::Mirror* Talos::Server::Utilities::syntax_node_at(
    const $::URI::View& resource, const XLSP::Position& position, Relint::Filter&& filter) const {
    auto* mirrors = syntax_view_at(resource);
    if (mirrors == nullptr) return nullptr;
    return mirrors->search(position.server(), std::move(filter));
}

const Talos::Relint::Mirror* Talos::Server::Utilities::vardef_node_at(
    const $::URI::View& resource, const XLSP::Position& position) const {
    auto* mirror = syntax_node_at<Syntax::Identifier, Syntax::Declaration>(resource, position);
    return mirror && !mirror->qualified() ? mirror->definition()->variable : nullptr;
}

const Talos::Relint::Mirror* Talos::Server::Utilities::typedef_node_at(
    const $::URI::View& resource, const XLSP::Position& position) const {
    auto* mirror = syntax_node_at<Syntax::Identifier, Syntax::Alias>(resource, position);
    return mirror && mirror->qualified() ? mirror->definition()->annotation : nullptr;
}

const Talos::Relint::Mirror* Talos::Server::Utilities::anydef_node_at(
    const $::URI::View& resource, const XLSP::Position& position) const {
    auto* mirror = syntax_node_at<Syntax::Identifier, Syntax::Declaration>(resource, position);
    if (mirror == nullptr) return nullptr;  // stop early when the incoming mirror is invalid at all
    return mirror->qualified() ? mirror->definition()->annotation : mirror->definition()->variable;
}
