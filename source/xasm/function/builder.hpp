#ifndef _XASM_FUNCTION_BUILDER_HPP
#define _XASM_FUNCTION_BUILDER_HPP

/// XASM Modules
#include "xasm/forward/compiler.hpp"
#include "xasm/forward/function.hpp"

namespace XASM::Function {

/// @brief Constructs function signatures.
template <class R, class... As, class... Ts> inline constexpr Signature Build(Ts &&...args) {
  return Signature::build<R, As...>(std::forward<Ts>(args)...);
}

/// @brief Constructs function signatures.
template <class R, class... As, class... Ts> inline constexpr Node *Build(Compiler::Universal *compiler, Ts &&...args) {
  return compiler->add_func(Build<R, As..., Ts...>(std::forward<Ts>(args)...));
}

/// @brief Handles invoking callbacks.
template <class R, class... As> inline constexpr Callee *Invoke(Compiler::Universal *compiler, R (*callback)(As...)) {
  Callee *output = nullptr; // prepare the output node now to be used
  compiler->cc->invoke(asmjit::Out(output), callback, Build<R, As...>());
  return output; // and return the resulting output now
}

/// @brief Handles invoking callbacks with arguments.
template <std::same_as<void> R, class... As, class... Ts>
inline constexpr Callee *Invoke(Compiler::Universal *compiler, R (*callback)(As...), Ts &&...args) {
  // ensure the size of the argument is valid
  static_assert(sizeof...(As) == sizeof...(Ts), "Mismatched arguments");

  // prepare the baseline handler now to be used
  auto *callee = Invoke(compiler, callback);

  size_t index = 0; // emplace the arguments now
  ((callee->set_arg(index, args), ++index), ...);

  // and return the resulting callee
  return callee;
}

/// @brief Handles invoking callbacks with arguments and return values.
template <class R, class... As, class T, class... Ts>
  requires(!std::same_as<R, void>)
inline constexpr Callee *Invoke(Compiler::Universal *compiler, R (*callback)(As...), const T &vreg, Ts &&...args) {
  // ensure the size of the argument is valid
  static_assert(sizeof...(As) == sizeof...(Ts), "Mismatched arguments");

  // prepare the baseline handler now to be used
  auto *callee = Invoke(compiler, callback);

  // bind the return value to be used
  callee->set_ret(0, vreg);

  size_t index = 0; // emplace the arguments now
  ((callee->set_arg(index, args), ++index), ...);

  // and return the resulting callee
  return callee;
}

} // namespace XASM::Function

#endif
