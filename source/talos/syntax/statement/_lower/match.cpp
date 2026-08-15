/// Talos Modules
#include "talos/bytecode/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Fallback, , , ) { /** fallbacks are type-system only */ }
TALOS_MM_LOWER_NODE(Query, , , ) { /** queries are type-system only */ }

TALOS_MM_LOWER_NODE(Match, node, compiler, ) {
  // prepare some suitable labels to be used
  auto *labels = compiler->labels();
  auto exit = labels->reserve();

  // prepare some labels for each of the queries
  const auto &queries = node->queries();
  auto matched = std::vector<Bytecode::Label>(queries.size());

  $_PP_SCOPE() {
    // prepare a scoped register for the value (so no clobbering occurs)
    auto value = compiler->registers()->temporary();

    // lower the value to be matched against to the accumulator
    compiler->lower(node->value(), value);

    // iterate over the queries guards to be emitted
    for (size_t ii = 0; ii < queries.size(); ++ii) matched[ii] = compiler->match(queries[ii]->guards(), value);
  }

  // if no guard is matched, then we jump to the exit
  compiler->emit<Glyph::JUMP_TO>(exit);

  // finally construct all the queries statements
  for (size_t ii = 0; ii < queries.size(); ++ii) {
    // bind the jump that was successful
    labels->patch(matched[ii]);

    // lower the incoming statement now
    compiler->lower(node->queries()[ii]->statement());

    // jump to the exit condition now
    compiler->emit<Glyph::JUMP_TO>(exit);
  }

  // on completion we bind the exit label
  labels->patch(exit);
}
