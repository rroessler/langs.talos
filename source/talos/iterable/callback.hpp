#ifndef _TALOS_OBJECT_ITERABLE_HPP
#define _TALOS_OBJECT_ITERABLE_HPP

/// Talos Includes
#include "talos/object/mixin.hpp"

namespace Talos::Iterable {

/// @brief Iteration Callback.
template <std::derived_from<Value::Any> T>
using Callback = $::Unique::Functor<Value::Any(Runtime::Isolate *, const T &, size_t) const>;

} // namespace Talos::Iterable

#endif
