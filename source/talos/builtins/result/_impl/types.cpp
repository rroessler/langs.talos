/// Builtin Includes
#include "talos/builtins/_inline/builtins.ipp"

/// Type Includes
#include "talos/type/_inline/type.ipp"

/// Forward Declarations
$_FWD(Talos::Builtins::Constraint, static const $::Shared::Pointer<Type::Parameter> &T())
$_FWD(Talos::Builtins::Constraint, static const $::Shared::Pointer<Type::Parameter> &E())

/// Forward Definitions
$_FWD(Talos::Builtins, using TN = Type::New)
$_FWD(Talos::Builtins, using Self = Type::Structure)

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) $_FWD(Talos::Builtins::Field, static Type::Entity N(const Self *))
#include "talos/builtins/result/_defines/fields.def"

#define TALOS_XX_STATICS_DEFINE(N, ...) $_FWD(Talos::Builtins::Static, static Type::Entity N())
#include "talos/builtins/result/_defines/statics.def"

//  PUBLIC METHODS  //

const $::Shared::Pointer<Talos::Type::Parameter> &Talos::Builtins::Constraint::T() {
  static auto s_T = TN::constraint("T", TN::any(), TN::any());
  return s_T; // define the necessary type-parameter now
}

const $::Shared::Pointer<Talos::Type::Parameter> &Talos::Builtins::Constraint::E() {
  static auto s_E = TN::constraint("E", TN::any(), TN::any());
  return s_E; // define the necessary type-parameter now
}

$::Shared::Pointer<Talos::Type::Generic> Talos::Builtins::Wrapper<Talos::Monad::Result>::generic() {
  Type::Template parameters = {Constraint::T(), Constraint::E()};
  return TN::generic(typeclass()->instantiate(), parameters);
}

$::Shared::Pointer<Talos::Type::Prototype> Talos::Builtins::Wrapper<Talos::Monad::Result>::typeclass() {
  return m_typeclass([](const $::Shared::Pointer<Type::Prototype> &prototype) {
    // bind the required constraints (Result [T = Any, E = Any])
    prototype->constraints() = {Constraint::T(), Constraint::E()};
  });
}

Talos::Type::Entity Talos::Builtins::Field::is_okay(const Self *) { return TN::function(TN::boolean()); }
Talos::Type::Entity Talos::Builtins::Field::is_error(const Self *) { return TN::function(TN::boolean()); }

Talos::Type::Entity Talos::Builtins::Field::unwrap_okay(const Self *self) {
  return TN::function(self->constraints(0), TN::optional(TN::string()));
}

Talos::Type::Entity Talos::Builtins::Field::unwrap_error(const Self *self) {
  return TN::function(self->constraints(1), TN::optional(TN::string()));
}

Talos::Type::Entity Talos::Builtins::Static::wrap() {
  auto T = TN::constraint("T", TN::future(TN::any()));
  auto result = TN::result(TN::awaited(T), TN::exception());
  return TN::generic(TN::function(result, T), T);
}

Talos::Type::Entity Talos::Builtins::Static::okay() {
  // prepare the constraints
  auto T = TN::constraint("T", TN::any(), TN::any());
  auto E = TN::constraint("E", TN::any(), TN::any());

  // prepare the result instance now
  auto signature = TN::function(TN::result(T, E), T);
  return TN::generic(signature, Type::Template({T, E}));
}

Talos::Type::Entity Talos::Builtins::Static::error() {
  // prepare the constraints
  auto T = TN::constraint("T", TN::any(), TN::any());
  auto E = TN::constraint("E", TN::any(), TN::any());

  // prepare the result instance now
  auto signature = TN::function(TN::result(T, E), E);

  // and construct the factory generic
  return TN::generic(signature, Type::Template({T, E}));
}

//  PRIVATE METHODS  //

void Talos::Builtins::Wrapper<Talos::Monad::Result>::m_typedefs(Type::World *globals) {
  // prepare the baseline details
  auto prototype = typeclass();
  auto &fields = prototype->fields();
  auto &statics = prototype->statics();

// define the fields for symbols
#define TALOS_XX_FIELDS_DEFINE(N, ...) fields.emplace(#N, Field::N);
#include "talos/builtins/result/_defines/fields.def"

// define the statics for symbols
#define TALOS_XX_STATICS_DEFINE(N, ...) statics.emplace(#N, Static::N());
#include "talos/builtins/result/_defines/statics.def"

  // define the baseline types
  globals->values().declare(name(), prototype);
  globals->types().declare(name(), generic());
}
