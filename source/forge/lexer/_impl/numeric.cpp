/// Forge Includes
#include "forge/lexer/dispatch.hpp"

//  PRIVATE METHODS  //

void Forge::Lexer::Dispatch::m_numeric(Scanner& lexer, Buffer& tokens) {
    // check for a leading '0' character
    auto zero = lexer.advance() == '0';

    // handle as necessary now
    if (zero && lexer.match('b', 'B')) tokens.append(m_binary(lexer));
    else if (zero && lexer.match('o', 'O')) tokens.append(m_octal(lexer));
    else if (zero && lexer.match('x', 'X')) tokens.append(m_hexadecimal(lexer));
    else tokens.append(m_numeric(lexer));  // regular numeric value to scan

    // and tail to the next item now
    $_MUSTTAIL return Dispatch::next(lexer, tokens);
}

Forge::Lexer::Token Forge::Lexer::Dispatch::m_binary(Scanner& lexer) {
    // attempt eating binary tokens now
    for (size_t length; $::Encoding::ASCII::is_bin(lexer.read(length));) lexer.jump(length);

    // return the final token now
    return lexer.token(Kind::LTRL_BIN);
}

Forge::Lexer::Token Forge::Lexer::Dispatch::m_octal(Scanner& lexer) {
    // attempt eating octal tokens now
    for (size_t length; $::Encoding::ASCII::is_oct(lexer.read(length));) lexer.jump(length);

    // return the final token now
    return lexer.token(Kind::LTRL_OCT);
}

Forge::Lexer::Token Forge::Lexer::Dispatch::m_hexadecimal(Scanner& lexer) {
    // attempt eating hexadecimal tokens now
    for (size_t length; $::Encoding::HEX::is(lexer.read(length));) lexer.jump(length);

    // return the final token now
    return lexer.token(Kind::LTRL_HEX);
}

Forge::Lexer::Token Forge::Lexer::Dispatch::m_numeric(Scanner& lexer) {
    for (size_t length; $::Encoding::ASCII::is_digit(lexer.read(length));) lexer.jump(length);
    if (!lexer.match('.')) return lexer.token(Kind::LTRL_INT);  // stop early since invalid

    for (size_t length; $::Encoding::ASCII::is_digit(lexer.read(length));) lexer.jump(length);
    return lexer.token(Kind::LTRL_FLT);  // and should be a valid float
}
