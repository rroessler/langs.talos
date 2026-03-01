/// Forge Modules
#include "forge/bytecode/visitor.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/builtins.ipp"

/// Syntax Modules
#include "forge/syntax/_inline/annotation.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LOWER_NODE(Interface, , compiler, destination) {
    static auto s_name = Value::Symbol(Value::Proxy<Object::Any>::name());  // prepare the name to be used now
    if (!destination.nowhere()) compiler->emit<Syllable::LOAD_GLOBAL>(destination, compiler->constant(s_name));
}
