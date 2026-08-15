#ifndef _TALOS_BUILTINS_INLINE_IPP
#define _TALOS_BUILTINS_INLINE_IPP

/// Talos Includes
#include "talos/builtins/storage.hpp"

/// Builtins Includes
#include "talos/builtins/boolean/traits.hpp"
#include "talos/builtins/class/traits.hpp"
#include "talos/builtins/debug/traits.hpp"
#include "talos/builtins/enum/traits.hpp"
#include "talos/builtins/exception/traits.hpp"
#include "talos/builtins/function/traits.hpp"
#include "talos/builtins/future/traits.hpp"
#include "talos/builtins/iterator/traits.hpp"
#include "talos/builtins/list/traits.hpp"
#include "talos/builtins/number/traits.hpp"
#include "talos/builtins/object/traits.hpp"
#include "talos/builtins/result/traits.hpp"
#include "talos/builtins/string/traits.hpp"
#include "talos/builtins/symbol/traits.hpp"
#include "talos/builtins/todo/traits.hpp"
#include "talos/builtins/utility/traits.hpp"
#include "talos/builtins/void/traits.hpp"

//  X-MACROS  //

#define TALOS_XX_BUILTINS_CUSTOM(X) \
  X(Builtins::Custom::Todo)         \
  X(Builtins::Custom::Debug)        \
  X(Builtins::Custom::Utility)

#define TALOS_XX_BUILTINS_LIST(X) \
  TALOS_XX_VALUES_IMMEDIATE(X)    \
  TALOS_XX_VALUES_OBJECT(X)       \
  X(Object::Instance)             \
  TALOS_XX_BUILTINS_CUSTOM(X)

#endif
