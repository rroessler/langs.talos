/// Forge Modules
#include "forge/bytecode/visitor.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/builtins.ipp"

/// Syntax Modules
#include "forge/syntax/_inline/annotation.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LOWER_NODE(Signature, , compiler, destination) {
    static auto s_name = Value::Symbol(Value::Proxy<Function::Dynamic>::name());  // prepare the name to be used
    if (!destination.nowhere()) compiler->emit<Syllable::LOAD_GLOBAL>(destination, compiler->constant(s_name));
}
