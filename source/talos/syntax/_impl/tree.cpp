/// Talos Modules
#include "talos/syntax/tree.hpp"
#include "talos/bytecode/visitor.hpp"
#include "talos/relint/visitor.hpp"
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/annotation/qualifier.hpp"

//  CONSTRUCTORS  //

Talos::Syntax::Tree::Tree(const $::URI::View& resource) : m_resource(resource) {
    // prepare the empty return typing to be used
    auto* empty = m_allocate<Identifier>("Void");
    auto* returns = m_allocate<Qualifier>(empty);

    // construct the prototype and the signature for the tree
    auto* prototype = m_allocate<Constructor>();
    auto* signature = m_allocate<Signature>(prototype, returns);

    // finally construct the resulting instance
    m_main = m_allocate<Lambda>(signature, m_block = m_allocate<Block>());
}

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Tree, tree, analyzer) {
    $_ASSERT(analyzer->depth() == -1);  // ensure at global-depth
    auto world = analyzer->scope();     // scope the incoming world
    $_ASSERT(analyzer->depth() == 0);   // and ensure now exporting

    auto& exports = analyzer->exports();  // prepare exports
    auto result = analyzer->check(tree->statements());

    auto retval = Type::Builder::none();  // prepare return value
    tree->main()->traits()->type() = Type::Builder::function(retval);

    // bind all the available exports now
    for (const auto& [name, entity] : world->entities()) {
        if (entity.exported()) exports.emplace(name, entity);
    }

    // always declare as suitably passable now
    return result.flow->passable() ? analyzer->passable(retval) : analyzer->unreachable();
}

TALOS_MM_LINT_NODE(Tree, tree, analyzer) {
    $_UNUSED $_AUTO = analyzer->scope();
    analyzer->verify(tree->statements(), tree);
}

TALOS_MM_LOWER_NODE(Tree, tree, compiler, ) { compiler->enqueue(tree->main()); }
