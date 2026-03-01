/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

FORGE_MM_PARSE_INFIX(Accessor, parser, parent, assignable) {
    // prepare the snapshot to be used
    auto snapshot = parser->snapshot().offset(parent->traits()->bounds());

    // should be seeing a leading "." character
    m_assert(parser->advance(), Lexer::Kind::PUNC_PERIOD);

    // attempt gettting the underlying field now
    auto field = m_identifier(parser);
    if (field == nullptr) return nullptr;

    // prepare the getter to be output when desired now
    auto* getter = parser->allocate<Syntax::Accessor>(field, parent, snapshot.enclose(field));

    // get the current opcode value now
    auto* opcode = parser->current();

    // get the current opcode to be used now
    if (!assignable || !parser->check(Lexer::Flag::ASSIGNABLE)) return getter;

    // attempt parsing the current assignment expression
    auto* value = (parser->advance(), m_expression(parser));
    if (value == nullptr) return nullptr;  // failed to read

    // check the type of opcode to be used now
    switch (opcode->kind()) {
#define FORGE_XX_TOKEN_ASSIGN(T, ...)                                                                        \
    case Lexer::Kind::ASOP_##T:                                                                              \
        value = parser->allocate<Syntax::Binary>(Lexer::Kind::BINOP_##T, getter, value, opcode->location()); \
        break;
#include "forge/lexer/_defines/tokens.def"

        // in default situations we break suitably
        default: break;
    }

    // construct the setter to be used now
    return parser->allocate<Syntax::Assign>(getter, value, snapshot.enclose(getter));
}
