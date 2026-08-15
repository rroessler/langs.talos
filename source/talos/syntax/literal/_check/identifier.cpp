/// Talos Includes
#include "talos/variable/visitor.hpp"

/// Talos Includes
#include "talos/type/_inline/type.ipp"

/// Forward Declarations
$_FWD(Talos::Type::Dispatch, template <std::derived_from<Syntax::Node> T> Deduction identifier(Analyzer *, const T *))

//  PUBLIC METHODS  //

template <std::derived_from<Talos::Syntax::Node> T>
Talos::Type::Deduction Talos::Type::Dispatch::identifier(Analyzer *analyzer, const T *node) {
  // get the underlying node name
  auto name = node->name();

  // attempt getting a type for the current identifier
  auto *entity = analyzer->world()->lookup(name);

  // declare an error if the variable does not exist or not a value
  if (entity == nullptr) return analyzer->report(node, 4000301, name);
  if (!entity->opaque()) return analyzer->report(node, 3000200, name);

  // attempt deprecating the node if possible
  if constexpr (std::same_as<T, Syntax::Identifier>) analyzer->deprecated(entity, node);

  // update the current entity as used and return the value
  return entity->value();
}

TALOS_MM_CAPTURE_NODE(Self, , ) {}
TALOS_MM_CAPTURE_NODE(Identifier, node, analyzer) { analyzer->mark(node); }

TALOS_MM_CHECK_NODE(Self, node, analyzer) { return Type::Dispatch::identifier(analyzer, node); }
TALOS_MM_CHECK_NODE(Identifier, node, analyzer) { return Type::Dispatch::identifier(analyzer, node); }
