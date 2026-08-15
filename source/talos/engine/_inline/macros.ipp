#ifndef _TALOS_ENGINE_MACROS_IPP
#define _TALOS_ENGINE_MACROS_IPP

/// Talos Includes
#include "talos/engine/dispatch.hpp"

/// Value Includes
#include "talos/value/_inline/value.ipp"

//  MACROS  //

#define TALOS_MM_ENGINE_EXECUTE(N, T, F, I, ...)                                                             \
  template <>                                                                                                \
  $_WILLTAIL $_INLINE_FORCE Talos::Value::Any Talos::Engine::Dispatch::m_execute<Talos::Bytecode::Glyph::N>( \
      Isolate * T, Function::Frame * F, const Instruction *I                                                 \
  )

#endif
