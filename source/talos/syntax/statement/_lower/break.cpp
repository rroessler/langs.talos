/// Talos Modules
#include "talos/bytecode/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Break, , compiler, ) { compiler->emit<Glyph::JUMP_TO>(compiler->labels()->breaks()); }
