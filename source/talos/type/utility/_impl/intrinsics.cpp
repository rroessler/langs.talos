/// Builtins Includes
#include "talos/builtins/_inline/builtins.ipp"

/// Talos Includes
#include "talos/type/_inline/type.ipp"

//  PUBLIC METHODS  //

Talos::Type::Entity Talos::Type::Any::lookup(const $::String::View &) const { return m_self(); }
Talos::Type::Entity Talos::Type::Unset::lookup(const $::String::View &) const { return m_self(); }

Talos::Type::Erased Talos::Type::Any::apply(Operator::Kind kind) const {
  switch (kind) {
  case Operator::Kind::NOT: return New::boolean();
  default: return m_self(); // default to "Any" type
  }
}

Talos::Type::Erased Talos::Type::Any::apply(Operator::Kind kind, const Erased &) const {
  switch (kind) {
  case Operator::Kind::EQ: $_FALLTHROUGH;
  case Operator::Kind::NE: $_FALLTHROUGH;
  case Operator::Kind::LOR: $_FALLTHROUGH;
  case Operator::Kind::LAND: return New::boolean();
  default: return m_self(); // default to "Any" type
  }
}

void Talos::Type::None::m_print(std::ostream &os, const None &) { os << Builtins::Inspect<Value::Void>::name(); }
