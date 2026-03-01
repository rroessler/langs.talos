/// Forge Modules
#include "forge/type/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_CHECK_NODE(Unary, unary, analyzer) {
    // trace from the unary node
    $_UNUSED $_AUTO = analyzer->trace(unary);

    // prepare the sides that are available
    auto operand = analyzer->check(unary->operand()).type;

    // prepare the base deduction to be used
    auto deduction = analyzer->passable(Type::Builder::fail());

    // if the operand is invalid, then fail immediately
    if (operand->is<Type::Failure>()) return deduction;

    // otherwise attempt running the transformation now
    deduction.type = operand->apply(unary->opcode());

    if (!deduction.type->is<Type::Unset>()) return deduction;
    return analyzer->report(3000800, unary->symbol(), *operand);
}
