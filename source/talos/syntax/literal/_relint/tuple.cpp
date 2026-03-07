/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Tuple, tuple, analyzer) { analyzer->verify(tuple->elements(), tuple); }
