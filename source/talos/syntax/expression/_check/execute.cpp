/// Talos Includes
#include "talos/variable/visitor.hpp"

/// Talos Includes
#include "talos/type/_inline/type.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CAPTURE_NODE(Execute, node, analyzer) { analyzer->visit(node->invocation()); }
TALOS_MM_CHECK_NODE(Execute, node, analyzer) {
  // attempt checking the underlying call
  auto result = analyzer->check(node->invocation());

  // if the result is a failure, then pass onwards
  if (result.type->is<Type::Poison>()) return result;

  // handle based on the incoming execution policy
  switch (node->policy()) {
  // for asynchronous results, we construct a suitable future
  case Function::Policy::ASYNC: {
    auto awaited = Type::New::awaited(result.type);
    return analyzer->passable(Type::New::future(awaited));
  }

  // for normal function policies, we return the base result
  case Function::Policy::CALL: return result;

  // otherwise we need to declare the policy as invalid
  default: return analyzer->report(node, 9000002, "Analyzer.check(Syntax::Execute)");
  }
}
