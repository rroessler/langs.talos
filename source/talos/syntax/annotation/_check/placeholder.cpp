/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/annotation.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Placeholder, node, analyzer) {
    // prepare the trace to be used
    $_UNUSED $_AUTO = analyzer->trace(node);

    // get some details about the placeholder
    auto name = node->name();
    auto location = node->traits()->location();

    // resolve the extension typing to be used
    auto extends = analyzer->check(node->extends()).type;
    auto fallback = analyzer->check(node->fallback()).type;

    // ensure the fallback fulfills the incoming extension type
    if (!fallback->is<Type::Unset>() && !extends->unify(fallback)) {
        return analyzer->report(node->fallback(), 3000304, *fallback, *extends);
    }

    // construct the type-parameter to be used
    auto type = Type::Builder::constraint(name, extends, fallback);

    // attempt declaring into the world now
    auto failed = analyzer->world()->types().declare(name, type, location) == nullptr;
    return failed ? analyzer->report(4000400, name) : analyzer->passable(type);
}
