/// Forge Modules
#include "forge/bytecode/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LOWER_NODE(True, , compiler, destination) { compiler->plug<Syllable::LOAD_TRUE>(destination); }
FORGE_MM_LOWER_NODE(False, , compiler, destination) { compiler->plug<Syllable::LOAD_FALSE>(destination); }
