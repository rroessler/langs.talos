#ifndef _TALOS_VALUE_MACROS_IPP
#define _TALOS_VALUE_MACROS_IPP

/// Talos Includes
#include "talos/value/pointer.hpp"

/// Value Includes
#include "talos/forward/async.hpp"
#include "talos/forward/function.hpp"
#include "talos/forward/iterable.hpp"
#include "talos/forward/monad.hpp"
#include "talos/forward/number.hpp"
#include "talos/forward/object.hpp"
#include "talos/forward/runtime.hpp"
#include "talos/forward/string.hpp"

//  X-MACROS  //

#define TALOS_XX_VALUES_IMMEDIATE(X) \
  X(Value::Void)                     \
  X(Value::Symbol)                   \
  X(Value::Boolean)                  \
  X(Number::Tagged)

#define TALOS_XX_VALUES_OBJECT(X) \
  X(String::Any)                  \
                                  \
  X(Function::Native)             \
  X(Function::Jitted)             \
  X(Function::Closure)            \
                                  \
  X(Object::Enum)                 \
  X(Object::Class)                \
  X(Object::Exception)            \
                                  \
  X(Async::Future)                \
                                  \
  X(Iterable::Iterator)           \
  X(Iterable::List)               \
                                  \
  X(Monad::Result)

#define TALOS_XX_VALUES_LIST(X) \
  TALOS_XX_VALUES_IMMEDIATE(X)  \
  X(String::Small)              \
                                \
  X(String::Large)              \
  TALOS_XX_VALUES_OBJECT(X)     \
  X(Object::Instance)

#endif
