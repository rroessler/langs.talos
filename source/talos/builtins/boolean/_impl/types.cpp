/// Builtin Includes
#include "talos/builtins/_inline/builtins.ipp"

/// Type Includes
#include "talos/type/_inline/type.ipp"

/// Forward Definitions
$_FWD(Talos::Builtins, using TN = Type::New)

//  TYPEDEFS  //

#define TALOS_XX_STATICS_DEFINE(N, ...) $_FWD(Talos::Builtins::Static, static Type::Entity N())
#include "talos/builtins/boolean/_defines/statics.def"

//  PUBLIC METHODS  //

Talos::Type::Entity Talos::Builtins::Static::from() { return TN::function(TN::boolean(), TN::any()); }
Talos::Type::Entity Talos::Builtins::Static::parse() {
  auto sensitivity = TN::optional(TN::boolean()); // prepare
  return TN::function(TN::boolean(), TN::string(), sensitivity);
}

$::Shared::Pointer<Talos::Type::Prototype> Talos::Builtins::Wrapper<Talos::Value::Boolean>::typeclass() {
  return m_typeclass([](const auto &) {});
}

//  PRIVATE METHODS  //

void Talos::Builtins::Wrapper<Talos::Value::Boolean>::m_typedefs(Type::World *globals) {
  // get the underlying prototype instance
  auto prototype = typeclass();
  auto &statics = prototype->statics();

  // define the underlying statics for booleans
#define TALOS_XX_STATICS_DEFINE(N, ...) statics.emplace(#N, Static::N());
#include "talos/builtins/boolean/_defines/statics.def"

  // prepare the baseline typing to be used
  globals->values().declare(name(), prototype);
  globals->types().declare(name(), TN::boolean());

  // and generate the "True" and "False" typings as well
  globals->values().declare("True", TN::boolean());
  globals->values().declare("False", TN::boolean());
}
