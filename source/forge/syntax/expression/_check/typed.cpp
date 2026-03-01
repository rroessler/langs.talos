/// Forge Modules
#include "forge/type/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_CHECK_NODE(Typed, node, analyzer) {
    $_UNUSED $_AUTO = analyzer->trace(node);
    auto result = analyzer->check(node->value());
    if (result.type->is<Type::Any>()) return result;
    return analyzer->instantiate(result.type, node->types());
}
