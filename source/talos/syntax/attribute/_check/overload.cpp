/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Overload, attribute, analyzer) {
    return analyzer->report(attribute, 9000002, "Unimplemented Analyzer.check(Syntax::Overload)");
}
