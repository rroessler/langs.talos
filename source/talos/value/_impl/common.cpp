/// Value Includes
#include "talos/value/_inline/value.ipp"

//  X-MACROS  //

/// @brief Available kinds lookup.
#define XX_VALUES_LOOKUP(X) \
  X(NUM, Number::Tagged)    \
  X(BIT, Value::Boolean)    \
  X(SYM, Value::Symbol)     \
  X(NIL, Value::Void)       \
  X(STR, String::Small)

//  TYPEDEFS  //

#define X(T, ...) static_assert(sizeof(Talos::T) == Talos::Pointer::Alignment::VALUE);
TALOS_XX_VALUES_LIST(X)
#undef X

//  PRIVATE METHODS  //

bool Talos::Value::Any::m_is(const Pointer::Tagged &) { return true; }

bool Talos::Value::Any::m_truthiness() const noexcept {
#define X(K, T, ...)                                                \
  case Pointer::Kind::K: return Inspect<T>::truthiness(*m_as<T>());
  switch (m_pointer.kind()) { XX_VALUES_LOOKUP(X) default : return true; }
#undef X
}

Talos::Shape::Underlying Talos::Value::Any::m_shape() const noexcept {
#define X(K, T, ...)                                \
  case Pointer::Kind::K: return Shape::Lookup<T>();
  switch (m_pointer.kind()) { XX_VALUES_LOOKUP(X) default : break; }
#undef X

  // otherwise can resolve the header shape now
  return m_as<Object::Any>()->header()->shape();
}

$::String::View Talos::Value::Any::m_brand() const noexcept {
#define X(K, T, ...)                                \
  case Pointer::Kind::K: return Inspect<T>::name();
  switch (m_pointer.kind()) { XX_VALUES_LOOKUP(X) default : break; }
#undef X

#define X(T, ...)                                     \
  case Shape::Lookup<T>(): return Inspect<T>::name();
  switch (m_as<Object::Any>()->header()->shape()) {
    TALOS_XX_VALUES_OBJECT(X) // baseline objects here
  default: return m_as<Object::Instance>()->name().view();
  }
#undef X
}

Talos::Member::View Talos::Value::Any::m_attribute(const Symbol &symbol) const noexcept {
#define A(T, ...) Builtins::Inspect<T>::attribute(*m_as<T>(), symbol)
#define X(K, T, ...)                  \
  case Pointer::Kind::K: return A(T);
  switch (m_pointer.kind()) { XX_VALUES_LOOKUP(X) default : break; }
#undef X

#define X(T, ...)                       \
  case Shape::Lookup<T>(): return A(T);
  switch (Object::Any(m_pointer).header()->shape()) {
    TALOS_XX_VALUES_OBJECT(X)
  default: return A(Object::Instance);
  }
#undef X
#undef A
}

Talos::Member::View Talos::Value::Any::m_attribute(Operator::Kind kind) const noexcept {
#define A(T, ...) Builtins::Inspect<T>::attribute(*m_as<T>(), kind)
#define X(K, T, ...)                  \
  case Pointer::Kind::K: return A(T);
  switch (m_pointer.kind()) { XX_VALUES_LOOKUP(X) default : break; }
#undef X

#define X(T, ...)                       \
  case Shape::Lookup<T>(): return A(T);
  switch (Object::Any(m_pointer).header()->shape()) {
    TALOS_XX_VALUES_OBJECT(X)
  default: return A(Object::Instance);
  }
#undef X
#undef A
}

bool Talos::Value::Any::m_equals(const Value::Any &other) const noexcept {
  auto specialized = is<String::Any>() && other.is<String::Any>();
  if (!specialized) return m_pointer == other.m_pointer;
  return as<String::Any>().compare(other.as<String::Any>()) == 0;
}

void Talos::Value::Any::m_print(std::ostream &os, const Any &self) {
#define X(K, T, ...)                                             \
  case Pointer::Kind::K: return $_PP_IGN(os << *self.m_as<T>());
  switch (self.m_pointer.kind()) { XX_VALUES_LOOKUP(X) default : break; }
#undef X

#define X(T, ...)                                                  \
  case Shape::Lookup<T>(): return $_PP_IGN(os << *self.m_as<T>());
  switch (Object::Any(self.m_pointer).header()->shape()) {
    TALOS_XX_VALUES_OBJECT(X)
  default: X(Object::Instance);
  }
#undef X
}
