/// Forge Modules
#include "forge/format/dispatch.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_FORMAT_INFIX(Call, reader, callee) {
    // stop if there is no suitable parenthesis for the value
    if (!reader->match(Lexer::Kind::PUNC_LPAREN)) return nullptr;

    // check for final "function" arguments now
    Node* minimize = nullptr;

    // prepare the callback with minimization handler
    auto callback = [&](Reader* reader) -> Node* {
        auto cache = reader->check(Lexer::Kind::DECL_FUNC);
        auto* argument = m_expression(reader);  // read next
        return minimize = cache ? argument : nullptr, argument;
    };

    // attempt parsing all the incoming arguments now
    auto* arguments = m_delimited(reader, { std::move(callback), Lexer::Kind::PUNC_RPAREN });
    if (arguments == nullptr || !reader->match(Lexer::Kind::PUNC_RPAREN)) return nullptr;

    // prepare the underlying storage instance
    auto* storage = reader->storage();

    // if minimizing, then we zero the final nodes width now (but need to find it first)
    for (auto iter = arguments->nodes().rbegin(); minimize && iter != arguments->nodes().rend(); ++iter) {
        // attempt finding the required item
        if (*iter != minimize) continue;

        *iter = storage->minimize(minimize);
        break;  // stop handling since found
    }

    // prepare the necessary indenation and grouping to be used now
    arguments = storage->indent(storage->line().soft(), arguments);

    // construct the resulting parameters group
    return storage->group(callee, storage->paren().left(), arguments, storage->line().soft(), storage->paren().right());
}
