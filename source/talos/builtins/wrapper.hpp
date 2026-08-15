#ifndef _TALOS_BUILTINS_WRAPPER_HPP
#define _TALOS_BUILTINS_WRAPPER_HPP

/// Talos Includes
#include "talos/builtins/adapter.hpp"
#include "talos/member/descriptor.hpp"
#include "talos/shape/lookup.hpp"
#include "talos/type/registry.hpp"

/// Forward Definitions
$_FWD(Talos::Builtins, using Args = Function::Args)
$_FWD(Talos::Builtins, using Isolate = Runtime::Isolate)

namespace Talos::Builtins {

/// @brief Builtins Inspection Proxy.
template <class T> struct Wrapper;

/// @brief Literal Name Value.
template <size_t N> using Name = $::String::Literal<N>;

/// @brief Defines Builtin Details.
template <class T, Name N, Adapter... As> struct Define {
  //  PUBLIC METHODS  //

  /// @brief Gets the name of the builtin.
  static inline constexpr $::String::View name() { return N.view(); }

  /// @brief Gets the shape of the builtin.
  static inline constexpr Shape::Underlying shape() { return Shape::Lookup<T>(); }

  /// @brief Validates if a builtin uses some features.
  template <Adapter A> static inline constexpr bool uses() { return ((A == As) || ...); }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Helper for defining internal prototypes.
   * @param define                Definition callback.
   */
  template <class F> static inline constexpr $::Shared::Pointer<Type::Prototype> m_typeclass(F define) noexcept {
    // ignore if there are no suitable prototypes defined here
    if (!uses<Adapter::PROTOTYPE>()) return nullptr;

    // prepare the storage for the baseline prototype now
    static auto s_storage = $::Shared::Pointer<Type::Prototype>();

    // allow defining the incoming prototype instance manually
    if (s_storage == nullptr) define(s_storage = Type::New::prototype(name(), shape()));

    // and finally return the resulting prototype instance
    return s_storage;
  }
};

/// @brief Helper for defining wrappers with common adapters.
template <class T, Name N, Adapter... As>
using Blueprint = Define<T, N, Adapter::PROTOTYPE, Adapter::TYPEDEFS, Adapter::GLOBALS, Adapter::FIELDS, As...>;

} // namespace Talos::Builtins

#endif
