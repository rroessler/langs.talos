/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

const Talos::Lexer::Token* Talos::Parser::Dispatch::m_label(Stream* parser) {
    // attempt matching an annotatable token
    if (parser->match(Lexer::Flag::ANNOTATION)) return parser->previous();

    // report an error here based on the reserved state of the item
    auto reserved = parser->check(Lexer::Flag::RESERVED);
    auto message = reserved ? parser->current()->lexeme() : "an identifier";
    return parser->report(reserved ? 2000102 : 2000100, message);
}

Talos::Syntax::Identifier* Talos::Parser::Dispatch::m_identifier(Stream* parser) {
    auto* token = m_label(parser);
    if (token == nullptr) return nullptr;
    return parser->allocate<Syntax::Identifier>(token);
}

Talos::Syntax::Identifier* Talos::Parser::Dispatch::m_identifier(
    Stream* parser, const $::String::View& name, const Syntax::Bounds& bounds) {
    return parser->allocate<Syntax::Identifier>(name, bounds);
}

TALOS_MM_PARSE_PREFIX(Self, parser, ) {
    auto* token = m_assert(parser->advance(), Lexer::Kind::LTRL_SELF);
    return parser->allocate<Syntax::Self>(token);  // fully validated
}

TALOS_MM_PARSE_PREFIX(Identifier, parser, assignable) {
    // parse the underlying identifier to be used
    auto* identifier = m_identifier(parser);
    if (identifier == nullptr) return nullptr;

    if (!assignable) return identifier;  // ignore if not assignable
    if (!parser->match(Lexer::Flag::ASSIGNABLE)) return identifier;

    // get the incoming assignment operator now
    auto* opcode = parser->previous();

    // get the underlying value now
    auto value = m_expression(parser);
    if (value == nullptr) return nullptr;

    // check the type of opcode that we have
    switch (opcode->kind()) {
#define TALOS_XX_TOKEN_ASSIGN(K, ...)                                                                            \
    case Lexer::Kind::ASOP_##K:                                                                                  \
        value = parser->allocate<Syntax::Binary>(Lexer::Kind::BINOP_##K, identifier, value, opcode->location()); \
        break;
#include "talos/lexer/_defines/tokens.def"

        // break for unknown opcodes given
        default: break;
    }

    // and build the resulting assignment expression
    return parser->allocate<Syntax::Assign>(identifier, value);
}
