/// Builtin Includes
#include "talos/builtins/_inline/builtins.ipp"

/// Type Includes
#include "talos/type/_inline/type.ipp"

/// Forward Declarations
$_FWD(Talos::Builtins::Constraint, static const $::Shared::Pointer<Type::Parameter> &T())

/// Forward Definitions
$_FWD(Talos::Builtins, using TN = Type::New)
$_FWD(Talos::Builtins, using Self = Type::Structure)

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) $_FWD(Talos::Builtins::Field, static Type::Entity N(const Self *))
#include "talos/builtins/future/_defines/fields.def"

#define TALOS_XX_STATICS_DEFINE(N, ...) $_FWD(Talos::Builtins::Static, static Type::Entity N())
#include "talos/builtins/future/_defines/statics.def"

//  PUBLIC METHODS  //

const $::Shared::Pointer<Talos::Type::Parameter> &Talos::Builtins::Constraint::T() {
  static auto s_T = TN::constraint("T", TN::any(), TN::any());
  return s_T; // define the necessary type-parameter now
}

$::Shared::Pointer<Talos::Type::Generic> Talos::Builtins::Wrapper<Talos::Async::Future>::generic() {
  return TN::generic(typeclass()->instantiate(), Constraint::T());
}

$::Shared::Pointer<Talos::Type::Prototype> Talos::Builtins::Wrapper<Talos::Async::Future>::typeclass() {
  return m_typeclass([](const $::Shared::Pointer<Type::Prototype> &prototype) {
    // bind the required constraints (List [T = Any])
    prototype->constraints() = {Constraint::T()};
  });
}

Talos::Type::Entity Talos::Builtins::Field::then(const Self *self) {
  // prepare a value constraint to convert to
  auto V = TN::constraint("V");

  // prepare a future-like value now
  auto returns = TN::future(V);
  auto either = TN::merge(V, returns);

  // prepare an incoming callback now
  auto value = TN::optional(self->constraints(0));
  auto callback = TN::function(either, value);

  // and now construct the resulting signature
  return TN::generic(TN::function(returns, callback), V);
}

Talos::Type::Entity Talos::Builtins::Field::fails(const Self *self) {
  // prepare the incoming return-typing
  auto value = self->constraints(0);
  auto returns = TN::future(value);
  auto either = TN::merge(value, returns);

  // prepare the incoming callback now
  auto exception = TN::optional(TN::any());
  auto callback = TN::function(either, exception);

  // and construct the resulting signature to be used
  return TN::function(returns, callback);
}

Talos::Type::Entity Talos::Builtins::Field::await(const Self *self) { return TN::function(self->constraints(0)); }
Talos::Type::Entity Talos::Builtins::Field::state(const Self *) { return TN::function(TN::number()); }

Talos::Type::Entity Talos::Builtins::Static::async() {
  auto F = TN::constraint("F", TN::variadic());
  return TN::generic(TN::invocation(F, true), F);
}

Talos::Type::Entity Talos::Builtins::Static::delay() {
  auto duration = TN::optional(TN::number());
  auto callback = TN::optional(TN::function(TN::none()));
  return TN::function(TN::future(TN::none()), duration, callback);
}

Talos::Type::Entity Talos::Builtins::Static::resolve() {
  auto T = TN::constraint("T", TN::any(), TN::none());
  return TN::generic(TN::function(TN::future(T), T), T);
}

Talos::Type::Entity Talos::Builtins::Static::reject() {
  auto T = TN::constraint("T", TN::any(), TN::any());
  return TN::generic(TN::function(TN::future(T), TN::any()), T);
}

//  PRIVATE METHODS  //

void Talos::Builtins::Wrapper<Talos::Async::Future>::m_typedefs(Type::World *globals) {
  // prepare the baseline details
  auto prototype = typeclass();
  auto &fields = prototype->fields();
  auto &statics = prototype->statics();

// define the fields for symbols
#define TALOS_XX_FIELDS_DEFINE(N, ...) fields.emplace(#N, Field::N);
#include "talos/builtins/future/_defines/fields.def"

// define the statics for symbols
#define TALOS_XX_STATICS_DEFINE(N, ...) statics.emplace(#N, Static::N());
#include "talos/builtins/future/_defines/statics.def"

  // define the baseline types
  globals->values().declare(name(), prototype);
  globals->types().declare(name(), generic());
}
