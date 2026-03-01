/// Forge Modules
#include "forge/bytecode/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LOWER_NODE(Void, , compiler, destination) { compiler->plug<Syllable::LOAD_VOID>(destination); }
