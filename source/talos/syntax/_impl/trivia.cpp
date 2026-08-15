/// Talos Includes
#include "talos/syntax/trivia.hpp"
#include "talos/syntax/visitor.hpp"
#include "talos/type/mixin.hpp"
#include "talos/value/fold.hpp"

//  PRIVATE METHODS  //

$::RTTI::Tag Talos::Syntax::Trivia::m_hash() const noexcept { return m_keyid->m_hash(); }

$::Unit::Ternary Talos::Syntax::Trivia::m_truthiness() const noexcept {
  // resolve the type-level truthiness
  auto result = m_type->truthiness();
  if (!result.indeterminate()) return result;

  // otherwise attempt the value-level instead
  auto value = Value::Fold(m_keyid);
  if (!value.pointer().okay()) return result;

  // safe to convert to a basic truthiness
  return value.truthiness();
}

$::String::View Talos::Syntax::Trivia::m_name() const noexcept {
#define X(N, ...)                     \
  case $::RTTI::Hash<N>(): return #N;
  switch (m_hash()) { TALOS_XX_SYNTAX_NODES(X) default : return "Invalid"; }
#undef X
}
