/// Talos Includes
#include "talos/variable/visitor.hpp"

/// Talos Includes
#include "talos/type/_inline/type.ipp"

/// Forward Declarations
$_FWD(Talos::Type::Dispatch, Control query(Analyzer *, const Syntax::Query *, Match &))

//  PUBLIC METHODS  //

Talos::Type::Control Talos::Type::Dispatch::query(Analyzer *analyzer, const Syntax::Query *node, Match &match) {
  // prepare a baseline flow to be used
  auto flow = $::Unique::New<Flow::Passable>();

  // iterate over our guards for the query given
  for (const auto *guard : node->guards()) {
    // validate the incoming guard now for the branching type
    auto branch = analyzer->check(guard).type;

    /// TODO: use the result of the guard against the match value

    // branching guards should be handled specially for matching

    // we then update the flow based on whether a guard always fails
    if (!branch->unify(match.result.type)) {}

    // ignore handling further if we do not have a fallback guard
    if (!guard->is<Syntax::Fallback>()) continue;

    // ensure we can latch the incoming fallback
    if (!match.fallback) match.fallback = true;
    else analyzer->report(guard, 2000650);
  }

  // finally determine the result of our statement
  return analyzer->check(node->statement()).flow;
}

TALOS_MM_CAPTURE_NODE(Fallback, , ) {}

TALOS_MM_CAPTURE_NODE(Query, node, analyzer) {
  analyzer->visit(node->guards());
  analyzer->visit(node->statement());
}

TALOS_MM_CAPTURE_NODE(Match, node, analyzer) {
  $_UNUSED $_AUTO = analyzer->scope();
  analyzer->visit(node->value());
  analyzer->visit(node->queries());
}

TALOS_MM_CHECK_NODE(Query, , analyzer) { return analyzer->passable(); }
TALOS_MM_CHECK_NODE(Fallback, , analyzer) { return analyzer->passable(Type::New::any()); }

TALOS_MM_CHECK_NODE(Match, node, analyzer) {
  // validate the incoming value to be switched over
  Type::Match match = {.result = analyzer->check(node->value())};

  // prepare the branch constructor to be used
  auto branch = [&](const Syntax::Query *node) { return Type::Dispatch::query(analyzer, node, match); };

  // iterate over each of the incoming queries
  for (const auto *query : node->queries()) {
    // update the current flow to be used for the resulting match output
    match.result.flow = analyzer->merge(std::move(match.result.flow), branch(query));
  }

  // if no fallback has been seen, declare a warning and bind a passable flow
  if (!match.fallback) match.result.flow = $::Unique::New<Flow::Passable>();

  // return based on the flow of each of the queries given
  return std::move(match.result);
}
