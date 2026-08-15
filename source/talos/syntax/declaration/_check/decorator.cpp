/// Talos Includes
#include "talos/variable/visitor.hpp"

/// Talos Includes
#include "talos/type/_inline/type.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CAPTURE_NODE(Decorator, node, analyzer) { analyzer->visit(node->expression()); }

TALOS_MM_CHECK_NODE(Decorator, node, analyzer) {
  // set the current trace handler
  $_UNUSED $_AUTO = analyzer->trace(node);

  // get the current preamble target to be validated
  auto target = analyzer->preamble()->value();

  // we want to check the incoming "decorator" value
  auto candidate = analyzer->check(node->expression()).type;

  // prepare a baseline decorator callback that we expect
  auto callback = Type::New::function(target, target);

  /// TODO: conduct more rigorous type-checking for decorators

  // ensure that the incoming decorator safely type-checks
  if (callback->unify(candidate)) return analyzer->passable();

  // otherwise we have an invalid decorator context to be applied
  else return analyzer->report(3000850, *candidate);
}
