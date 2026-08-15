/// Talos Modules
#include "talos/bytecode/visitor.hpp"
#include "talos/function/common.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/builtins.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Signature, , compiler, destination) {
  static auto s_name = Value::Symbol(Value::Inspect<Function::Any>::name()); // prepare the name to be used
  if (!destination.nowhere()) compiler->emit<Glyph::LOAD_GLOBAL>(destination, compiler->constant(s_name));
}
