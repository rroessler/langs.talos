/// Talos Includes
#include "talos/variable/visitor.hpp"

/// Talos Includes
#include "talos/type/_inline/type.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CAPTURE_NODE(Interface, node, analyzer) {
  $_UNUSED $_AUTO = analyzer->scope();
  analyzer->visit(node->properties());
}

TALOS_MM_CHECK_NODE(Interface, node, analyzer) {
  // get the underlying record elements
  const auto &properties = node->properties();

  // stop early if they are empty
  if (properties.empty()) return Type::New::object();

  // prepare the fields to be bound now
  auto fields = $::Map::Record<Type::Entity>();

  // convert all our values as necessary now
  for (const auto *variable : properties) {
    // prepare the incoming variable details
    auto [name, expected] = analyzer->vardef(variable);

    // ensure incoming variables are not disposable
    if (variable->disposable()) analyzer->report(variable, 3000151, name);

    // and check whether the field can be emplaced or not
    if (!fields.contains(name)) fields.emplace(name, expected);
    else analyzer->report(variable, 4000404, name); // invalid
  }

  // construct the resulting record to be used
  return Type::New::interface(fields);
}
