/// Talos Modules
#include "talos/bytecode/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Caret, , compiler, destination) {
  auto index = compiler->queue()->size(); // bind current
  compiler->plug<Glyph::CLOSURE_MAKE>(destination, index);
}
