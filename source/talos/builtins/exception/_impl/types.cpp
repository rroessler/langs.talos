/// Builtin Includes
#include "talos/builtins/_inline/builtins.ipp"

/// Type Includes
#include "talos/type/_inline/type.ipp"

/// Forward Definitions
$_FWD(Talos::Builtins, using TN = Type::New)

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) $_FWD(Talos::Builtins::Field, static Type::Entity N())
#include "talos/builtins/exception/_defines/fields.def"

#define TALOS_XX_STATICS_DEFINE(N, ...) $_FWD(Talos::Builtins::Static, static Type::Entity N())
#include "talos/builtins/exception/_defines/statics.def"

//  PUBLIC METHODS  //

$::Shared::Pointer<Talos::Type::Prototype> Talos::Builtins::Wrapper<Talos::Object::Exception>::typeclass() {
  return m_typeclass([](const auto &) {});
}

Talos::Type::Entity Talos::Builtins::Field::name() { return TN::function(TN::string()); }
Talos::Type::Entity Talos::Builtins::Field::message() { return TN::function(TN::string()); }

Talos::Type::Entity Talos::Builtins::Static::from() {
  return TN::variadic(TN::exception(), TN::optional(TN::string()), TN::any());
}

Talos::Type::Entity Talos::Builtins::Static::named() {
  auto format = TN::optional(TN::string()); // optional format argument
  auto args = std::vector<Type::Entity>({TN::string(), format, TN::any()});
  return TN::variadic(TN::exception(), args); // construct the result
}

//  PRIVATE METHODS  //

void Talos::Builtins::Wrapper<Talos::Object::Exception>::m_typedefs(Type::World *globals) {
  // prepare the baseline details
  auto prototype = typeclass();
  auto &fields = prototype->fields();
  auto &statics = prototype->statics();

// define the fields for symbols
#define TALOS_XX_FIELDS_DEFINE(N, ...) fields.emplace(#N, Field::N());
#include "talos/builtins/exception/_defines/fields.def"

// define the statics for symbols
#define TALOS_XX_STATICS_DEFINE(N, ...) statics.emplace(#N, Static::N());
#include "talos/builtins/exception/_defines/statics.def"

  // define the baseline types
  globals->values().declare(name(), prototype);
  globals->types().declare(name(), TN::exception());
}
