/// Talos Includes
#include "talos/server/utilities.hpp"
#include "talos/document/service.hpp"
#include "talos/import/service.hpp"
#include "talos/runtime/container.hpp"
#include "talos/type/metadata.hpp"

//  CONSTRUCTORS  //

Talos::Server::Utilities::Utilities() : Utilities($::Global::get<Runtime::Container>()) {}
Talos::Server::Utilities::Utilities(XI::Container *services) : m_services(services) {}

//  PUBLIC METHODS  //

XLSP::Reference Talos::Server::Utilities::syntax_to_client(const Relint::Mirror *mirror) const {
  auto *tree = mirror->parent<Syntax::Tree>(); // resolve the tree node
  if ($_UNLIKELY(tree == nullptr)) return syntax_to_client(mirror->origin());
  else return syntax_to_client(mirror->origin(), tree->resource().buffer());
}

XLSP::Reference
Talos::Server::Utilities::syntax_to_client(const Syntax::Node *node, const $::URI::Buffer &resource) const {
  return {resource, node->trivia()->range().client()};
}

const Talos::Relint::Exports *Talos::Server::Utilities::syntax_view_at(const $::URI::View &resource) const {
  Import::Service *modules = *m_services; // resolve
  auto *found = modules->storage()->lookup(resource);
  if (found == nullptr) return nullptr; // failed
  auto *metadata = found->metadata<Module::Phase::TYPED>();
  return metadata->mirrors().get(); // resolve exports
}

const Talos::Relint::Mirror *Talos::Server::Utilities::syntax_node_at(
    const $::URI::View &resource, const XLSP::Position &position, Relint::Filter &&filter
) const {
  auto *mirrors = syntax_view_at(resource);
  if (mirrors == nullptr) return nullptr;
  return mirrors->search(position.server(), std::move(filter));
}

Talos::Relint::Comments Talos::Server::Utilities::comments_view_at(const Relint::Mirror *mirror) const {
  if (mirror == nullptr) return Relint::Comments();
  auto *definition = anydef_node_at(mirror);
  return definition ? definition->comments() : Relint::Comments();
}

const Talos::Relint::Mirror *Talos::Server::Utilities::vardef_node_at(const Relint::Mirror *mirror) const {
  return mirror && !mirror->qualified() ? mirror->definition()->variable : nullptr;
}

const Talos::Relint::Mirror *
Talos::Server::Utilities::vardef_node_at(const $::URI::View &resource, const XLSP::Position &position) const {
  return vardef_node_at(syntax_node_at<Syntax::Identifier, Syntax::Declaration>(resource, position));
}

const Talos::Relint::Mirror *Talos::Server::Utilities::typedef_node_at(const Relint::Mirror *mirror) const {
  return mirror && mirror->qualified() ? mirror->definition()->annotation : nullptr;
}

const Talos::Relint::Mirror *
Talos::Server::Utilities::typedef_node_at(const $::URI::View &resource, const XLSP::Position &position) const {
  return typedef_node_at(syntax_node_at<Syntax::Identifier, Syntax::Alias>(resource, position));
}

const Talos::Relint::Mirror *Talos::Server::Utilities::anydef_node_at(const Relint::Mirror *mirror) const {
  if (mirror == nullptr) return nullptr; // stop early when the incoming mirror is invalid at all
  return mirror->qualified() ? mirror->definition()->annotation : mirror->definition()->variable;
}

const Talos::Relint::Mirror *
Talos::Server::Utilities::anydef_node_at(const $::URI::View &resource, const XLSP::Position &position) const {
  return anydef_node_at(syntax_node_at<Syntax::Identifier, Syntax::Declaration>(resource, position));
}
