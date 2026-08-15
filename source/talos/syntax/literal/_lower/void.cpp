/// Talos Modules
#include "talos/bytecode/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Void, , compiler, destination) { compiler->plug<Glyph::LOAD_VOID>(destination); }
