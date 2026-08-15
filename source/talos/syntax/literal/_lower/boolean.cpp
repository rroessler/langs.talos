/// Talos Modules
#include "talos/bytecode/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(True, , compiler, destination) { compiler->plug<Glyph::LOAD_TRUE>(destination); }
TALOS_MM_LOWER_NODE(False, , compiler, destination) { compiler->plug<Glyph::LOAD_FALSE>(destination); }
