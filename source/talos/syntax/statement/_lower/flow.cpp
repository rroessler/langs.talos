/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Return, node, compiler, ) { compiler->returns(node->value()); }
TALOS_MM_LOWER_NODE(Break, , compiler, ) { compiler->emit<Syllable::JUMP_TO>(compiler->labels()->breaks()); }
TALOS_MM_LOWER_NODE(Continue, , compiler, ) { compiler->emit<Syllable::JUMP_TO>(compiler->labels()->continues()); }
