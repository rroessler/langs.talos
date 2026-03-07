/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Spawn, node, analyzer) {
    // attempt checking the underlying call
    auto result = analyzer->check(node->invocation());

    // if the result is a failure, then pass onwards
    if (result.type->is<Type::Failure>()) return result;

    // get the return typing now
    auto awaited = Type::Builder::awaited(result.type);

    // we want to attempt converting this value into a future
    return analyzer->passable(Type::Builder::future(awaited));
}
