/// Forge Modules
#include "forge/bytecode/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LOWER_NODE(Return, returns, compiler, ) { compiler->returns(returns->value()); }
FORGE_MM_LOWER_NODE(Break, , compiler, ) { compiler->emit<Syllable::JUMP_TO>(compiler->labels()->breaks()); }
FORGE_MM_LOWER_NODE(Continue, , compiler, ) { compiler->emit<Syllable::JUMP_TO>(compiler->labels()->continues()); }
