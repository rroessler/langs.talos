/// Forge Includes
#include "forge/lexer/dispatch.hpp"

//  PRIVATE METHODS  //

void Forge::Lexer::Dispatch::m_identifier(Scanner& lexer, Buffer& tokens) {
    // prepare a list of available keywords now
    static $::Record<Kind> keywords = {
#define FORGE_XX_TOKEN_KEYWORD(N, S, ...) { S, Kind::N },
#include "forge/lexer/_defines/tokens.def"
    };

    // prepare a simple reader to be used
    static constexpr auto is_ident = [](int64_t cp) {
        return $::Encoding::ASCII::is_ident(cp) || $::Encoding::ASCII::is_digit(cp);
    };

    // attempt eating values whilst possible to do so
    for (size_t length; is_ident(lexer.read(length));) lexer.jump(length);

    auto lexeme = lexer.buffer();  // attempt classifying the buffer now
    auto kind = keywords.contains(lexeme) ? keywords.at(lexeme) : Kind::LTRL_IDENT;
    tokens.append(lexer.token(kind));  // and emplace the associated value

    // and tail to the next item now
    $_MUSTTAIL return Dispatch::next(lexer, tokens);
}
