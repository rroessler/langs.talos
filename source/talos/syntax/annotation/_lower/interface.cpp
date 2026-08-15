/// Talos Modules
#include "talos/bytecode/visitor.hpp"
#include "talos/object/common.hpp"

/// Builtins Includes
#include "talos/builtins/_inline/builtins.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Interface, , compiler, destination) {
  static auto s_name = Value::Symbol(Value::Inspect<Object::Any>::name()); // prepare the name to show
  if (!destination.nowhere()) compiler->emit<Glyph::LOAD_GLOBAL>(destination, compiler->constant(s_name));
}
