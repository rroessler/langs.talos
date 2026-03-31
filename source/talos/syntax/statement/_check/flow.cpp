/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Break, node, analyzer) {
    Type::Depth depth = analyzer->world()->loops();
    if (depth < 0) return analyzer->report(node, 2000601, "break");
    return analyzer->unreachable(depth, Flow::Effect::BREAKS);
}

TALOS_MM_CHECK_NODE(Continue, node, analyzer) {
    Type::Depth depth = analyzer->world()->loops();
    if (depth < 0) return analyzer->report(node, 2000601, "continue");
    return analyzer->unreachable(depth, Flow::Effect::LOOPS);
}

TALOS_MM_CHECK_NODE(Return, node, analyzer) {
    // push the necessary traces for analyzing
    $_UNUSED $_AUTO = analyzer->trace(node);

    // get the expected return typing now
    Type::Erased callee = analyzer->world()->callee();

    // handle if we are not in a valid context
    if (callee == nullptr) return analyzer->report(3000900);

    // resolve the callable instance now if we have a generic
    auto callable = Type::Builder::resolve<Type::Callable>(callee);

    // ensure the expected/inferred typings are valid
    auto expected = callable->returns(), inferred = analyzer->check(node->value()).type;

    // ensure the incoming return value is valid
    if (!expected->unify(inferred)) analyzer->report(3000300, *inferred, *expected);

    // always declare as currently unreachable now
    return analyzer->unreachable();
}
