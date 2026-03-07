/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(True, , compiler, destination) { compiler->plug<Syllable::LOAD_TRUE>(destination); }
TALOS_MM_LOWER_NODE(False, , compiler, destination) { compiler->plug<Syllable::LOAD_FALSE>(destination); }
