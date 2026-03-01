/// Forge Modules
#include "forge/format/dispatch.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

FORGE_MM_FORMAT_PREFIX(Numeric, reader) {
    switch (auto* numeric = reader->advance(); numeric->kind()) {
        case Lexer::Kind::LTRL_FLT: $_FALLTHROUGH;
        case Lexer::Kind::LTRL_INT: $_FALLTHROUGH;
        case Lexer::Kind::LTRL_BIN: $_FALLTHROUGH;
        case Lexer::Kind::LTRL_OCT: $_FALLTHROUGH;
        case Lexer::Kind::LTRL_HEX: return reader->storage()->unicode(numeric->lexeme());
        default: $_ABORT("Unexpected numeric token");  // invalid token received
    }
}
