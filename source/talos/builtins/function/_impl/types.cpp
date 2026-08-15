/// Builtin Includes
#include "talos/builtins/_inline/builtins.ipp"

/// Type Includes
#include "talos/type/_inline/type.ipp"

/// Forward Definitions
$_FWD(Talos::Builtins, using TN = Type::New)

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) $_FWD(Talos::Builtins::Field, static Type::Entity N())
#include "talos/builtins/function/_defines/fields.def"

#define TALOS_XX_STATICS_DEFINE(N, ...) $_FWD(Talos::Builtins::Static, static Type::Entity N())
#include "talos/builtins/function/_defines/statics.def"

//  PUBLIC METHODS  //

$::Shared::Pointer<Talos::Type::Prototype> Talos::Builtins::Wrapper<Talos::Function::Any>::typeclass() {
  return m_typeclass([](const auto &) {});
}

Talos::Type::Entity Talos::Builtins::Field::arity() { return TN::function(TN::number()); }
Talos::Type::Entity Talos::Builtins::Field::adicity() { return TN::function(TN::number()); }
Talos::Type::Entity Talos::Builtins::Field::receiver() { return TN::function(TN::any()); }

Talos::Type::Entity Talos::Builtins::Static::vlimit() { return TN::function(TN::number()); }

Talos::Type::Entity Talos::Builtins::Static::bind() {
  auto F = TN::constraint("F", TN::variadic());
  return TN::generic(TN::function(F, F, TN::any()), F);
}

Talos::Type::Entity Talos::Builtins::Static::call() {
  auto F = TN::constraint("F", TN::variadic());
  return TN::generic(TN::invocation(F, false), F);
}

Talos::Type::Entity Talos::Builtins::Static::apply() {
  auto passthrough = TN::optional(TN::list(TN::any()));
  return TN::function(TN::any(), TN::variadic(), passthrough);
}

//  PRIVATE METHODS  //

void Talos::Builtins::Wrapper<Talos::Function::Any>::m_typedefs(Type::World *globals) {
  // prepare the baseline details
  auto prototype = typeclass();
  auto &fields = prototype->fields();
  auto &statics = prototype->statics();

// define the fields for symbols
#define TALOS_XX_FIELDS_DEFINE(N, ...) fields.emplace(#N, Field::N());
#include "talos/builtins/function/_defines/fields.def"

// define the statics for symbols
#define TALOS_XX_STATICS_DEFINE(N, ...) statics.emplace(#N, Static::N());
#include "talos/builtins/function/_defines/statics.def"

  // define the baseline types
  globals->values().declare(name(), prototype);
  globals->types().declare(name(), TN::variadic());
}
