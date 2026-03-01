/// Forge Modules
#include "forge/syntax/generator.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PRIVATE METHODS   //

FORGE_MM_PARSE_INFIX(Binary, parser, left, ) {
    // prepare the snapshot to be used
    auto snapshot = parser->snapshot().offset(left->traits()->bounds());

    // cache the operator now
    auto opcode = parser->current();

    // prepare the grammar to be inherited
    static auto &grammar = Syntax::Generator::grammar<Syntax::Expression, Stream, Dispatch>();

    // ensure we have a valid opcode to be used now
    switch (opcode->kind()) {
#define FORGE_XX_TOKEN_BINARY(N, ...) \
    case Lexer::Kind::BINOP_##N: parser->advance(); break;
#include "forge/lexer/_defines/tokens.def"
        default: return parser->report(opcode, 2000100, "a binary operator");
    }

    // attempt getting the suitable rule to be used now
    auto rule = grammar.at(static_cast<size_t>(opcode->kind()));
    auto level = static_cast<size_t>(rule.precedence) + 1;

    // parse the incoming RHS of the binary operation
    auto right = m_expression(parser, static_cast<Precedence>(level));
    if (!right) return nullptr;  // invalid RHS found

    // and return the resulting binary node now
    return parser->allocate<Syntax::Binary>(opcode, left, right, snapshot.enclose(opcode));
}
