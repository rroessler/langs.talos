#ifndef _TALOS_OBJECT_ITERABLE_HPP
#define _TALOS_OBJECT_ITERABLE_HPP

/// Talos Modules
#include "talos/forward/iterable.hpp"
#include "talos/object/abstract.hpp"

namespace Talos::Iterable {

    /// @brief Iteration Callback.
    template <std::derived_from<Value::Any> T>
    using Callback = $::Functor::Unique<Value::Any(Runtime::Isolate*, T, size_t)>;

}  // namespace Talos::Iterable

#endif
