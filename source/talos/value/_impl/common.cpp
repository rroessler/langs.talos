/// Talos Modules
#include "talos/builtins/proxy.hpp"

/// Inline Modules
#include "talos/builtins/_inline/builtins.ipp"
#include "talos/value/_inline/value.ipp"

//  X-MACROS  //

/// @brief Available kinds lookup.
#define XX_VALUES_LOOKUP(X) \
    X(NUM, Number::Tagged)  \
    X(BIT, Value::Boolean)  \
    X(SYM, Value::Symbol)   \
    X(VOID, Value::Void)    \
    X(SSTR, String::Small)

//  TYPEDEFS  //

#define X(T, ...) static_assert(sizeof(Talos::T) == Talos::Pointer::Alignment::VALUE);
TALOS_XX_VALUES_LIST(X)
#undef X

//  PUBLIC METHODS  //

bool Talos::Value::Any::truthiness() const noexcept {
#define X(K, T, ...) \
    case Pointer::Kind::K: return Proxy<T>::truthiness(m_as<T>());
    switch (traits().kind()) { XX_VALUES_LOOKUP(X) default : return true; }
#undef X
}

Talos::Shape::Underlying Talos::Value::Any::shape() const noexcept {
#define X(K, T, ...) \
    case Pointer::Kind::K: return Shape::Lookup<T>();
    switch (traits().kind()) { XX_VALUES_LOOKUP(X) default : break; }
#undef X

    // otherwise can resolve the header shape now
    return Object::Any(m_pointer).header()->shape();
}

$::String::View Talos::Value::Any::type_name() const noexcept {
#define X(K, T, ...) \
    case Pointer::Kind::K: return Proxy<T>::name();
    switch (traits().kind()) { XX_VALUES_LOOKUP(X) default : break; }
#undef X

#define X(T, ...) \
    case Shape::Lookup<T>(): return Proxy<T>::name();
    switch (Object::Any(m_pointer).header()->shape()) {
        TALOS_XX_VALUES_OBJECT(X)  // baseline objects here
        default: return m_as<Object::Instance>().name().view();
    }
#undef X
}

Talos::Member::View Talos::Value::Any::attribute(const Symbol& symbol) const noexcept {
#define A(T, ...) Builtins::Proxy<T>::attribute(m_as<T>(), symbol)
#define X(K, T, ...) \
    case Pointer::Kind::K: return A(T);
    switch (traits().kind()) { XX_VALUES_LOOKUP(X) default : break; }
#undef X

#define X(T, ...) \
    case Shape::Lookup<T>(): return A(T);
    switch (Object::Any(m_pointer).header()->shape()) {
        TALOS_XX_VALUES_OBJECT(X)
        default: return A(Object::Instance);
    }
#undef X
#undef A
}

Talos::Member::View Talos::Value::Any::attribute(Operator::Kind kind) const noexcept {
#define A(T, ...) Builtins::Proxy<T>::attribute(m_as<T>(), kind)
#define X(K, T, ...) \
    case Pointer::Kind::K: return A(T);
    switch (traits().kind()) { XX_VALUES_LOOKUP(X) default : break; }
#undef X

#define X(T, ...) \
    case Shape::Lookup<T>(): return A(T);
    switch (Object::Any(m_pointer).header()->shape()) {
        TALOS_XX_VALUES_OBJECT(X)
        default: return A(Object::Instance);
    }
#undef X
#undef A
}

//  PRIVATE METHODS  //

void Talos::Value::Any::m_stringify($::Stream::Output& os, const Any& self) { m_print(os, self); }
void Talos::Value::Any::m_print($::Stream::Output& os, const Any& self) {
#define X(K, T, ...) \
    case Pointer::Kind::K: return Proxy<T>::print(os, self.m_as<T>());
    switch (self.traits().kind()) { XX_VALUES_LOOKUP(X) default : break; }
#undef X
#define X(T, ...) \
    case Shape::Lookup<T>(): return Proxy<T>::print(os, self.m_as<T>());
    switch (Object::Any(self.m_pointer).header()->shape()) {
        TALOS_XX_VALUES_OBJECT(X)
        default: X(Object::Instance);
    }
#undef X
}
