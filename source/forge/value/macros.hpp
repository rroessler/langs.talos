#ifndef _FORGE_VALUE_MACROS_HPP
#define _FORGE_VALUE_MACROS_HPP

/// Forge Includes
#include "forge/value/pointer.hpp"

//  X-MACROS  //

#define FORGE_XX_VALUES_IMMEDIATE(X) \
    X(Value::Void)                   \
    X(Value::Symbol)                 \
    X(Value::Boolean)                \
                                     \
    X(Number::Tagged)

#define FORGE_XX_VALUES_OBJECT(X) \
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

#define FORGE_XX_VALUES_WRAPPED(X) \
    X(String::Small)               \
    X(String::Large)               \
                                   \
    X(Object::Instance)

#define FORGE_XX_VALUES_LIST(X)  \
    FORGE_XX_VALUES_IMMEDIATE(X) \
    FORGE_XX_VALUES_OBJECT(X)    \
    FORGE_XX_VALUES_WRAPPED(X)

#endif
