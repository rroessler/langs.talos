/// Talos Modules
#include "talos/format/dispatch.hpp"
#include "talos/variable/modifiers.hpp"

//  X-MACROS  //

#define XX_VARIABLE_MODIFIERS(X) \
    X(EXPORT, "export")          \
    X(STATIC, "static")          \
    X(PUBLIC, "public")          \
    X(PRIVATE, "private")        \
    X(PROTECTED, "protected")

//  PRIVATE METHODS  //

Talos::Format::Node* Talos::Format::Dispatch::m_declaration(Reader* reader) {
    switch (auto kind = reader->current()->kind()) {
        // handle decorators, attributes differently
        case Lexer::Kind::PUNC_DECOR: $_FALLTHROUGH;
        case Lexer::Kind::PUNC_ATTRIB: return m_terminates(reader, m_preamble(reader));

        // handle baseline modifiers for declarations
        case Lexer::Kind::MOD_STATIC: $_FALLTHROUGH;
        case Lexer::Kind::MOD_PUBLIC: $_FALLTHROUGH;
        case Lexer::Kind::MOD_PRIVATE: $_FALLTHROUGH;
        case Lexer::Kind::MOD_PROTECTED: return m_terminates(reader, m_modifiers(reader));

        // handle imports/exports as necessary
        case Lexer::Kind::MOD_IMPORT: return m_terminates<Syntax::Import>(reader);
        case Lexer::Kind::MOD_EXPORT: return m_terminates(reader, m_export(reader));

        // handle any potential subjects here
        case Lexer::Kind::DECL_LET: $_FALLTHROUGH;
        case Lexer::Kind::DECL_USE: $_FALLTHROUGH;
        case Lexer::Kind::DECL_MUT: $_FALLTHROUGH;
        case Lexer::Kind::DECL_TYPE: $_FALLTHROUGH;
        case Lexer::Kind::DECL_ENUM: $_FALLTHROUGH;
        case Lexer::Kind::DECL_CLASS: $_FALLTHROUGH;
        case Lexer::Kind::DECL_SPACE: return m_terminates(reader, m_subject(reader, kind));

        // otherwise attempt matching a suitable statement instead
        default: return m_statement(reader);
    }
}

Talos::Format::Node* Talos::Format::Dispatch::m_subject(Reader* reader) {
    return m_subject(reader, reader->peek(INT32_MAX)->kind());
}

Talos::Format::Node* Talos::Format::Dispatch::m_subject(Reader* reader, Lexer::Kind kind) {
    switch (kind) {
        case Lexer::Kind::DECL_LET: $_FALLTHROUGH;
        case Lexer::Kind::DECL_USE: $_FALLTHROUGH;
        case Lexer::Kind::DECL_MUT: return m_declaration<Syntax::Variable>(reader);

        case Lexer::Kind::DECL_TYPE: return m_declaration<Syntax::Alias>(reader);
        case Lexer::Kind::DECL_ENUM: return m_declaration<Syntax::Enum>(reader);
        case Lexer::Kind::DECL_CLASS: return m_declaration<Syntax::Class>(reader);
        case Lexer::Kind::DECL_SPACE: return m_declaration<Syntax::Namespace>(reader);
        default: return nullptr;  // stop if we have an invalid subject here
    }
}

Talos::Format::Node* Talos::Format::Dispatch::m_modifiers(Reader* reader, Variable::Modifiers modifiers) {
    // attempt matching modifiers whilst possible to do so
    while (reader->match(Lexer::Flag::MODIFIER)) {
#define TALOS_XX_TOKEN_MODIFIER(K, N, ...) \
    case Lexer::Kind::MOD_##K: modifiers.set(Variable::Flag::K); break;
        switch (reader->previous()->kind()) {
#include "talos/lexer/_defines/tokens.def"
            default: break;
        }
    }

    // stop if the modifiers are currently empty
    if (modifiers.none()) return m_subject(reader);

    // otherwise we want to build the callback to be used now
    auto callback = [modifiers](Reader* reader) -> Node* {
        auto* subject = m_subject(reader);
        if (subject == nullptr) return nullptr;

        // prepare the list to be output now
        auto* storage = reader->storage();
        auto* group = storage->group();

        // and construct our desired output as necessary
#define X(N, T, ...) \
    if (modifiers.test(Variable::Flag::N)) storage->append(group, storage->unicode(T " "));
        XX_VARIABLE_MODIFIERS(X)
#undef X

        // and construct the result now
        return storage->append(group, subject);
    };

    // and attempt flushing leading space now as necessary
    return m_leading(reader, Callback(callback));
}
