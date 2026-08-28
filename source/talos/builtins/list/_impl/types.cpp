/// Builtin Includes
#include "talos/builtins/_inline/apply.ipp"
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
#include "talos/builtins/list/_defines/fields.def"

#define TALOS_XX_STATICS_DEFINE(N, ...) $_FWD(Talos::Builtins::Static, static Type::Entity N())
#include "talos/builtins/list/_defines/statics.def"

//  PUBLIC METHODS  //

const $::Shared::Pointer<Talos::Type::Parameter> &Talos::Builtins::Constraint::T() {
  static auto s_T = TN::constraint("T", TN::any(), TN::any());
  return s_T; // define the necessary type-parameter now
}

$::Shared::Pointer<Talos::Type::Generic> Talos::Builtins::Wrapper<Talos::Iterable::List>::generic() {
  return TN::generic(typeclass()->instantiate(), Constraint::T());
}

$::Shared::Pointer<Talos::Type::Prototype> Talos::Builtins::Wrapper<Talos::Iterable::List>::typeclass() {
  return m_typeclass([](const $::Shared::Pointer<Type::Prototype> &prototype) {
    // bind the required constraints (List [T = Any])
    prototype->constraints() = {Constraint::T()};
  });
}

Talos::Type::Entity Talos::Builtins::Field::size(const Self *) { return TN::function(TN::number()); }
Talos::Type::Entity Talos::Builtins::Field::empty(const Self *) { return TN::function(TN::boolean()); }

Talos::Type::Entity Talos::Builtins::Field::get(const Self *self) {
  return TN::function(self->constraints(0), TN::number());
}

Talos::Type::Entity Talos::Builtins::Field::set(const Self *self) {
  return TN::function(self->constraints(0), TN::number(), self->constraints(0));
}

Talos::Type::Entity Talos::Builtins::Field::front(const Self *self) { return back(self); }
Talos::Type::Entity Talos::Builtins::Field::back(const Self *self) { return TN::function(self->constraints(0)); }

Talos::Type::Entity Talos::Builtins::Field::map(const Self *self) {
  // prepare the constraint
  auto V = TN::constraint("V", TN::any(), TN::any());

  // prepare the incoming values now
  auto index = TN::optional(TN::number());
  auto value = TN::optional(self->constraints(0));

  // prepare the mapping signature
  auto callback = TN::function(V, value, index);
  auto signature = TN::function(TN::list(V), callback);

  // and construct the resulting generic now
  return TN::generic(signature, V);
}

Talos::Type::Entity Talos::Builtins::Field::fold(const Self *self) {
  auto V = TN::constraint("V", TN::any(), TN::any());
  auto callback = TN::function(V, V, self->constraints(0));
  return TN::generic(TN::function(V, V, callback), V);
}

Talos::Type::Entity Talos::Builtins::Field::clear(const Self *self) {
  return TN::function(TN::list(self->constraints(0)));
}

Talos::Type::Entity Talos::Builtins::Field::drop(const Self *self) {
  return TN::function(TN::list(self->constraints(0)), TN::number());
}

Talos::Type::Entity Talos::Builtins::Field::erase(const Self *self) {
  return TN::function(TN::list(self->constraints(0)), TN::number(), TN::number());
}

Talos::Type::Entity Talos::Builtins::Field::slice(const Self *self) {
  auto start = TN::optional(TN::number()), end = TN::optional(TN::number());
  return TN::function(TN::list(self->constraints(0)), start, end);
}

Talos::Type::Entity Talos::Builtins::Field::filter(const Self *self) {
  auto value = TN::optional(self->constraints(0));
  auto callback = TN::optional(TN::function(TN::boolean(), value));
  return TN::function(TN::list(self->constraints(0)), callback);
}

Talos::Type::Entity Talos::Builtins::Field::reverse(const Self *self) {
  return {TN::function(TN::list(self->constraints(0)))};
}

Talos::Type::Entity Talos::Builtins::Field::push_front(const Self *self) { return push_back(self); }
Talos::Type::Entity Talos::Builtins::Field::push_back(const Self *self) {
  return TN::variadic(TN::number(), self->constraints(0));
}

Talos::Type::Entity Talos::Builtins::Field::pop_front(const Self *self) { return TN::function(self->constraints(0)); }
Talos::Type::Entity Talos::Builtins::Field::pop_back(const Self *self) { return TN::function(self->constraints(0)); }

Talos::Type::Entity Talos::Builtins::Field::first_index_of(const Self *self) { return last_index_of(self); }
Talos::Type::Entity Talos::Builtins::Field::last_index_of(const Self *self) {
  return TN::function(TN::number(), self->constraints(0));
}

Talos::Type::Entity Talos::Builtins::Static::from() {
  auto T = TN::constraint("T"); // bind "T"
  auto R = TN::list(TN::iterable(T, false));
  return TN::generic(TN::function(R, T), T);
}

Talos::Type::Entity Talos::Builtins::Static::empty() {
  auto T = TN::constraint("T", TN::any(), TN::any());
  return TN::generic(TN::function(TN::list(T)), T);
}

Talos::Type::Entity Talos::Builtins::Static::range() {
  auto index = TN::optional(TN::number());
  auto instance = TN::list(TN::number());
  auto args = std::vector<Type::Entity>({index, index, index});
  return TN::function(instance, args); // bind the function
}

Talos::Type::Entity Talos::Builtins::Static::filled() {
  auto V = TN::constraint("V"); // prepare the baseline constraint
  return TN::generic(TN::function(TN::list(V), TN::number(), V), V);
}

template <>
Talos::Type::Erased
Talos::Builtins::Apply<Talos::Iterable::List>::unary(const Type::Structure *self, Operator::Kind kind) {
  switch (kind) {
  case Operator::Kind::ITER: return self->constraints(0);
  default: return TN::unset(); // resolve accordingly
  }
}

template <>
Talos::Type::Erased
Talos::Builtins::Apply<Talos::Iterable::List>::binary(const Type::Structure *, Operator::Kind, const Type::Erased &) {
  return TN::unset();
}

//  PRIVATE METHODS  //

void Talos::Builtins::Wrapper<Talos::Iterable::List>::m_typedefs(Type::World *globals) {
  // prepare the baseline details
  auto prototype = typeclass();
  auto &fields = prototype->fields();
  auto &statics = prototype->statics();

  // bind the decision tree for operators
  prototype->operators() = Apply<Iterable::List>::decide;

// define the fields for symbols
#define TALOS_XX_FIELDS_DEFINE(N, ...) fields.emplace(#N, Field::N);
#include "talos/builtins/list/_defines/fields.def"

// define the statics for symbols
#define TALOS_XX_STATICS_DEFINE(N, ...) statics.emplace(#N, Static::N());
#include "talos/builtins/list/_defines/statics.def"

  // define the baseline types
  globals->values().declare(name(), prototype);
  globals->types().declare(name(), generic());
}
