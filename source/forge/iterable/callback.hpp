#ifndef _FORGE_OBJECT_ITERABLE_HPP
#define _FORGE_OBJECT_ITERABLE_HPP

/// Forge Modules
#include "forge/forward/iterable.hpp"
#include "forge/object/abstract.hpp"

namespace Forge::Iterable {

    /// @brief Iteration Callback.
    template <std::derived_from<Value::Any> T>
    using Callback = $::Functor::Unique<Value::Any(Runtime::Isolate*, T, size_t)>;

}  // namespace Forge::Iterable

#endif
