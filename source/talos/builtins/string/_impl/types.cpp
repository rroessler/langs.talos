/// Talos Includes
#include "talos/string/common.hpp"

/// Builtin Includes
#include "talos/builtins/_inline/apply.ipp"
#include "talos/builtins/_inline/builtins.ipp"

/// Type Includes
#include "talos/type/_inline/type.ipp"

/// Forward Definitions
$_FWD(Talos::Builtins, using TN = Type::New)

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) $_FWD(Talos::Builtins::Field, static Type::Entity N())
#include "talos/builtins/string/_defines/fields.def"

#define TALOS_XX_STATICS_DEFINE(N, ...) $_FWD(Talos::Builtins::Static, static Type::Entity N())
#include "talos/builtins/string/_defines/statics.def"

//  PUBLIC METHODS  //

$::Shared::Pointer<Talos::Type::Prototype> Talos::Builtins::Wrapper<Talos::String::Any>::typeclass() {
  return m_typeclass([](const auto &) {});
}

Talos::Type::Entity Talos::Builtins::Field::size() { return TN::function(TN::number()); }
Talos::Type::Entity Talos::Builtins::Field::bytes() { return TN::function(TN::number()); }
Talos::Type::Entity Talos::Builtins::Field::empty() { return TN::function(TN::boolean()); }
Talos::Type::Entity Talos::Builtins::Field::symbol() { return TN::function(TN::symbol()); }
Talos::Type::Entity Talos::Builtins::Field::fmt() { return TN::variadic(TN::string()); }

Talos::Type::Entity Talos::Builtins::Field::at() { return TN::function(TN::maybe(TN::string()), TN::number()); }

Talos::Type::Entity Talos::Builtins::Field::slice() {
  auto index = TN::optional(TN::number());
  return TN::function(TN::string(), index, index);
}

Talos::Type::Entity Talos::Builtins::Field::compare() { return TN::function(TN::number(), TN::string()); }
Talos::Type::Entity Talos::Builtins::Field::contains() {
  return TN::function(TN::boolean(), TN::string(), TN::optional(TN::number()));
}

Talos::Type::Entity Talos::Builtins::Field::starts_with() { return ends_with(); }
Talos::Type::Entity Talos::Builtins::Field::ends_with() { return TN::function(TN::boolean(), TN::string()); }

Talos::Type::Entity Talos::Builtins::Field::to_lower() { return TN::function(TN::string()); }
Talos::Type::Entity Talos::Builtins::Field::to_upper() { return TN::function(TN::string()); }

Talos::Type::Entity Talos::Builtins::Field::trim_both() { return TN::function(TN::string()); }
Talos::Type::Entity Talos::Builtins::Field::trim_leading() { return TN::function(TN::string()); }
Talos::Type::Entity Talos::Builtins::Field::trim_trailing() { return TN::function(TN::string()); }

Talos::Type::Entity Talos::Builtins::Field::pad_leading() { return pad_trailing(); }
Talos::Type::Entity Talos::Builtins::Field::pad_trailing() {
  return TN::function(TN::string(), TN::number(), TN::optional(TN::string()));
}

Talos::Type::Entity Talos::Builtins::Static::from() { return TN::function(TN::string(), TN::any()); }
Talos::Type::Entity Talos::Builtins::Static::codepoint() { return TN::function(TN::string(), TN::number()); }

template <>
Talos::Type::Erased Talos::Builtins::Apply<Talos::String::Any>::unary(const Type::Structure *, Operator::Kind kind) {
  switch (kind) {
  case Operator::Kind::ITER: return TN::string();
  default: return TN::unset(); // resolve now
  }
}

template <>
Talos::Type::Erased Talos::Builtins::Apply<Talos::String::Any>::binary(
    const Type::Structure *, Operator::Kind kind, const Type::Erased &right
) {
  // if we do not have a secondary "String" typing, then ignore
  if (!right->is<String::Any>()) return TN::unset();

  // attempt matching as necessary now
  switch (kind) {
  // check against the basic addition handler
  case Operator::Kind::ADD: return TN::string();

  // allow checking against comparison handlers
  case Operator::Kind::LT: $_FALLTHROUGH;
  case Operator::Kind::GT: $_FALLTHROUGH;
  case Operator::Kind::LE: $_FALLTHROUGH;
  case Operator::Kind::GE: return TN::boolean();

  // fallback to the default handler
  default: return TN::unset();
  }
}

//  PRIVATE METHODS  //

void Talos::Builtins::Wrapper<Talos::String::Any>::m_typedefs(Type::World *globals) {
  // prepare the baseline details
  auto prototype = typeclass();
  auto &fields = prototype->fields();
  auto &statics = prototype->statics();

  // bind the decision tree for operators
  prototype->operators() = Apply<String::Any>::decide;

// define the fields for symbols
#define TALOS_XX_FIELDS_DEFINE(N, ...) fields.emplace(#N, Field::N());
#include "talos/builtins/string/_defines/fields.def"

// define the statics for symbols
#define TALOS_XX_STATICS_DEFINE(N, ...) statics.emplace(#N, Static::N());
#include "talos/builtins/string/_defines/statics.def"

  // define the baseline types
  globals->values().declare(name(), prototype);
  globals->types().declare(name(), TN::string());
}
