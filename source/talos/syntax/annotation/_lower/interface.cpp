/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/builtins.ipp"

/// Syntax Modules
#include "talos/syntax/_inline/annotation.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Interface, , compiler, destination) {
    static auto s_name = Value::Symbol(Value::Proxy<Object::Any>::name());  // prepare the name to be used now
    if (!destination.nowhere()) compiler->emit<Syllable::LOAD_GLOBAL>(destination, compiler->constant(s_name));
}
