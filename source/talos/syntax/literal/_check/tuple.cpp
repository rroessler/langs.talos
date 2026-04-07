/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Tuple, node, analyzer) {
    // attempt reducing a suitable tuple value now
    Type::Erased inferred = Type::Builder::any();

    // attempt inferring the required tuple type here
    for (const auto& element : node->elements()) {
        auto result = analyzer->check(element);  // get next now
        if (result.type->is<Type::Failure>()) return result;
        if (inferred->unify(result.type)) inferred = result.type;
        if (inferred->is<Type::Any>()) break;  // suitably broken
    }

    // attempt resolving a suitable instance type for the list
    return Type::Builder::list(inferred);
}
