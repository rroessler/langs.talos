/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Self, , compiler, destination) { compiler->plug<Syllable::LOAD_SELF>(destination); }

TALOS_MM_LOWER_NODE(Identifier, node, compiler, destination) {
    $_UNUSED $_AUTO = compiler->trace(node);
    auto extent = compiler->captures()->resolve(node);
    return compiler->load(node->name(), extent, destination);
}
