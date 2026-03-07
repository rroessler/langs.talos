/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Lambda, lambda, analyzer) {
    // always pre-verify the signature for the lambda
    analyzer->verify(lambda->signature(), lambda);

    // and then verify the resulting body
    $_UNUSED $_AUTO = analyzer->scope();
    analyzer->verify(lambda->body(), lambda);
}
