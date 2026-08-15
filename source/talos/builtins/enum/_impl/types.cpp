/// Builtin Includes
#include "talos/builtins/_inline/builtins.ipp"

/// Type Includes
#include "talos/type/_inline/type.ipp"

/// Forward Definitions
$_FWD(Talos::Builtins, using TN = Type::New)

//  TYPEDEFS  //

#define TALOS_XX_STATICS_DEFINE(N, ...) $_FWD(Talos::Builtins::Static, static Type::Entity N())
#include "talos/builtins/enum/_defines/statics.def"

//  PUBLIC METHODS  //

$::Shared::Pointer<Talos::Type::Prototype> Talos::Builtins::Wrapper<Talos::Object::Enum>::typeclass() {
  return m_typeclass([](const $::Shared::Pointer<Type::Prototype> &prototype) {
    // update the underlying super-type to be used
    prototype->super() = Wrapper<Number::Tagged>::typeclass();
  });
}

Talos::Type::Entity Talos::Builtins::Static::name() { return label(); }
Talos::Type::Entity Talos::Builtins::Static::label() {
  auto E = TN::constraint("E"); // prepare the constraint
  auto signature = TN::function(TN::string(), E, TN::number());
  return TN::generic(signature, E); // build the generic now
}

Talos::Type::Entity Talos::Builtins::Static::value() {
  auto E = TN::constraint("E"); // prepare the constraint
  auto signature = TN::function(TN::number(), E, TN::number());
  return TN::generic(signature, E); // build the generic now
}

//  PRIVATE METHODS  //

void Talos::Builtins::Wrapper<Talos::Object::Enum>::m_typedefs(Type::World *globals) {
  // get the underlying prototype instance
  auto prototype = typeclass();
  auto instance = prototype->instantiate();
  auto &statics = prototype->statics();

// define the underlying statics for enumerations
#define TALOS_XX_STATICS_DEFINE(N, ...) statics.emplace(#N, Static::N());
#include "talos/builtins/enum/_defines/statics.def"

  // and define the baseline typings now
  globals->values().declare(name(), prototype);
  globals->types().declare(name(), instance);
}
