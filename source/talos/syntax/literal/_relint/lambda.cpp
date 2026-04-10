/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Lambda, node, analyzer) {
    // bind this declaration now as a suitable symbol
    $_UNUSED $_AUTO = analyzer->symbol("<function>", node, XLSP::Symbol::Kind::FUNCTION);

    // prepare the scoping to be used for this lambda
    $_UNUSED $_AUTO = analyzer->scope();

    // always pre-verify the signature for the lambda
    analyzer->verify(node->signature(), node);

    // and then verify the resulting body
    analyzer->verify(node->body(), node);
}
