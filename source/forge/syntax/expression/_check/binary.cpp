/// Forge Modules
#include "forge/type/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_CHECK_NODE(Binary, binary, analyzer) {
    // trace from the unary node
    $_UNUSED $_AUTO = analyzer->trace(binary);

    // prepare the sides that are available
    auto left = analyzer->check(binary->left()).type;
    auto right = analyzer->check(binary->right()).type;

    // prepare the base deduction to be used
    auto deduction = analyzer->passable(Type::Builder::fail());

    // if either operand is invalid, then fail immediately
    if (left->is<Type::Failure>() || right->is<Type::Failure>()) return deduction;

    // otherwise attempt running the transformation now
    deduction.type = left->apply(binary->opcode(), right);

    if (!deduction.type->is<Type::Unset>()) return deduction;
    return analyzer->report(3000801, binary->symbol(), *left, *right);
}
