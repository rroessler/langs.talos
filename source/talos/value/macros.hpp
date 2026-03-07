#ifndef _TALOS_VALUE_MACROS_HPP
#define _TALOS_VALUE_MACROS_HPP

/// Talos Includes
#include "talos/value/pointer.hpp"

//  X-MACROS  //

#define TALOS_XX_VALUES_IMMEDIATE(X) \
    X(Value::Void)                   \
    X(Value::Symbol)                 \
    X(Value::Boolean)                \
                                     \
    X(Number::Tagged)

#define TALOS_XX_VALUES_OBJECT(X) \
    X(String::Dynamic)            \
                                  \
    X(Function::Native)           \
    X(Function::Jitted)           \
    X(Function::Closure)          \
                                  \
    X(Object::Enum)               \
    X(Object::Class)              \
    X(Object::Exception)          \
                                  \
    X(Async::Future)              \
                                  \
    X(Iterable::Iterator)         \
    X(Iterable::List)             \
                                  \
    X(Monad::Result)

#define TALOS_XX_VALUES_WRAPPED(X) \
    X(String::Small)               \
    X(String::Large)               \
                                   \
    X(Object::Instance)

#define TALOS_XX_VALUES_LIST(X)  \
    TALOS_XX_VALUES_IMMEDIATE(X) \
    TALOS_XX_VALUES_OBJECT(X)    \
    TALOS_XX_VALUES_WRAPPED(X)

#endif
