/// Talos Modules
#include "talos/bytecode/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Text, node, compiler, destination) {
  if (destination.nowhere()) return; // ignore
  auto index = compiler->string(node->buffer());
  compiler->emit<Glyph::STRING_MAKE>(destination, index);
}
