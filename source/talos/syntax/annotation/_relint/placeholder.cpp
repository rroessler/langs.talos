/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/annotation.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Placeholder, placeholder, analyzer) {
    analyzer->verify(placeholder->extends(), placeholder);
    analyzer->verify(placeholder->fallback(), placeholder);
}
