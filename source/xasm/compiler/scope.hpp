#ifndef _XASM_COMPILER_SCOPE_HPP
#define _XASM_COMPILER_SCOPE_HPP

/// XASM Modules
#include "xasm/forward/compiler.hpp"
#include "xasm/forward/runtime.hpp"

namespace XASM::Compiler {

/// @brief Unviversal Compiler Wrapper.
template <class T> class Typed : public asmjit::ujit::UniCompiler {
  //  TYPDEFS  //

  /// @brief Allow scopes internal access.
  template <class> friend class Scope;

  //  PROPERTIES  //

  /// @brief The underlying arena.
  Arena *m_arena = nullptr;

  /// @brief The bound runtime target.
  Runtime::Target *m_target = nullptr;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a universal compiler.
   * @param target            Target runtime.
   * @param arena             Arena code holder.
   * @param backend           Backend compiler.
   */
  explicit Typed(Runtime::Target *target, Arena *arena, Backend *backend) :
      UniCompiler(backend, target->_cpu_features, target->_cpu_hints), m_arena(arena), m_target(target) {}

  //  PUBLIC METHODS  //

  /// @brief Handles safely finalizing functions.
  T finish() {
    // prepare the output functor
    T functor = {};

#define MM_EXPECT(...)                                                                                                \
  if (auto errc = __VA_ARGS__; errc != asmjit::Error::kOk) $_ABORT("{0}", asmjit::DebugUtils::error_as_string(errc));

    // attempt finalizing the incoming callback
    MM_EXPECT(end_func());
    MM_EXPECT(finalize());
    MM_EXPECT(m_target->add(&functor, m_arena));

#undef MM_EXPECT

    // and finally declare as a success
    return functor;
  }
};

} // namespace XASM::Compiler

#endif
