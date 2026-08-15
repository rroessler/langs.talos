/// Talos Includes
#include "talos/engine/dispatch.hpp"
#include "talos/runtime/isolate.hpp"

/// Engine Includes
#include "talos/engine/_inline/execute.ipp"

//  PUBLIC METHODS  //

$_WILLTAIL Talos::Value::Any
Talos::Engine::Dispatch::tailcall(Runtime::Isolate *isolate, Function::Frame *frame, const Instruction *unqualified) {
  // prepare the callback typing to be used
  using Callback = decltype(&tailcall);

  // prepare the available dispatch table now
  static constexpr Callback s_table[] = {
#define TALOS_XX_GLYPH_BASE(N, ...) m_execute<Bytecode::Glyph::N>,
#include "talos/bytecode/_defines/glyphs.def"
  };

  // update the instruction to be dispatched here now
  unqualified = std::bit_cast<Bytecode::Instruction *>(frame->advance());
  $_MUSTTAIL return s_table[unqualified->glyph().encoded()](isolate, frame, unqualified);
}
