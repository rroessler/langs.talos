/// Talos Includes
#include "talos/number/tagged.hpp"

/// Builtin Includes
#include "talos/builtins/_inline/apply.ipp"
#include "talos/builtins/_inline/builtins.ipp"

/// Type Includes
#include "talos/type/_inline/type.ipp"

/// Forward Definitions
$_FWD(Talos::Builtins, using TN = Type::New)

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) $_FWD(Talos::Builtins::Field, static Type::Entity N())
#include "talos/builtins/number/_defines/fields.def"

#define TALOS_XX_STATICS_DEFINE(N, ...) $_FWD(Talos::Builtins::Static, static Type::Entity N())
#include "talos/builtins/number/_defines/statics.def"

//  PUBLIC METHODS  //

$::Shared::Pointer<Talos::Type::Prototype> Talos::Builtins::Wrapper<Talos::Number::Tagged>::typeclass() {
  return m_typeclass([](const auto &) {});
}

Talos::Type::Entity Talos::Builtins::Field::sign() { return TN::function(TN::number()); }
Talos::Type::Entity Talos::Builtins::Field::abs() { return TN::function(TN::number()); }
Talos::Type::Entity Talos::Builtins::Field::ceil() { return TN::function(TN::number()); }
Talos::Type::Entity Talos::Builtins::Field::floor() { return TN::function(TN::number()); }
Talos::Type::Entity Talos::Builtins::Field::round() { return TN::function(TN::number()); }
Talos::Type::Entity Talos::Builtins::Field::trunc() { return TN::function(TN::number()); }
Talos::Type::Entity Talos::Builtins::Field::clamp() {
  auto minimum = TN::optional(TN::number());
  auto maximum = TN::optional(TN::number());
  return TN::function(TN::number(), minimum, maximum);
}

Talos::Type::Entity Talos::Builtins::Field::is_nan() { return TN::function(TN::boolean()); }
Talos::Type::Entity Talos::Builtins::Field::is_fin() { return TN::function(TN::boolean()); }
Talos::Type::Entity Talos::Builtins::Field::is_inf() { return TN::function(TN::boolean()); }

Talos::Type::Entity Talos::Builtins::Field::to_precision() { return to_scientific(); }
Talos::Type::Entity Talos::Builtins::Field::to_scientific() {
  return TN::function(TN::string(), TN::optional(TN::number()));
}

Talos::Type::Entity Talos::Builtins::Static::parse() {
  return TN::function(TN::number(), TN::any(), TN::optional(TN::number()));
}

template <>
Talos::Type::Erased Talos::Builtins::Apply<Talos::Number::Tagged>::unary(const Type::Structure *, Operator::Kind kind) {
  switch (kind) {
  case Operator::Kind::INV: $_FALLTHROUGH;
  case Operator::Kind::NEG: return TN::number();
  default: return TN::unset(); // resolve now
  }
}

template <>
Talos::Type::Erased Talos::Builtins::Apply<Talos::Number::Tagged>::binary(
    const Type::Structure *, Operator::Kind kind, const Type::Erased &right
) {
  // if we do not have a secondary "Number" typing, then ignore
  if (!right->is<Number::Tagged>()) return TN::unset();

  // attempt resolving a suitable kind to be used now
  switch (kind) {
  case Operator::Kind::ADD:
  case Operator::Kind::SUB: $_FALLTHROUGH;
  case Operator::Kind::MUL: $_FALLTHROUGH;
  case Operator::Kind::DIV: $_FALLTHROUGH;
  case Operator::Kind::MOD: $_FALLTHROUGH;
  case Operator::Kind::POW: $_FALLTHROUGH;

  case Operator::Kind::SHL: $_FALLTHROUGH;
  case Operator::Kind::SHR: $_FALLTHROUGH;
  case Operator::Kind::XOR: $_FALLTHROUGH;
  case Operator::Kind::BOR: $_FALLTHROUGH;
  case Operator::Kind::BAND: return TN::number();

  case Operator::Kind::LT: $_FALLTHROUGH;
  case Operator::Kind::GT: $_FALLTHROUGH;
  case Operator::Kind::LE: $_FALLTHROUGH;
  case Operator::Kind::GE: return TN::boolean();

  // otherwise use the default handler
  default: return TN::unset();
  }
}

//  PRIVATE METHODS  //

void Talos::Builtins::Wrapper<Talos::Number::Tagged>::m_typedefs(Type::World *globals) {
  // prepare the baseline details
  auto prototype = typeclass();
  auto &fields = prototype->fields();
  auto &statics = prototype->statics();

  // bind the required operators now
  prototype->operators() = Apply<Number::Tagged>::decide;

// define the fields for symbols
#define TALOS_XX_FIELDS_DEFINE(N, ...) fields.emplace(#N, Field::N());
#include "talos/builtins/number/_defines/fields.def"

// define the statics for symbols
#define TALOS_XX_STATICS_DEFINE(N, ...) statics.emplace(#N, Static::N());
#include "talos/builtins/number/_defines/statics.def"

  // define the baseline types
  globals->values().declare(name(), prototype);
  globals->types().declare(name(), TN::number());

  // and generate the "NaN" and "Infinity" typings as well
  globals->values().declare("NaN", TN::boolean());
  globals->values().declare("Infinity", TN::boolean());
}
