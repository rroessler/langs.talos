#ifndef _TALOS_PARSER_DISPATCH_HPP
#define _TALOS_PARSER_DISPATCH_HPP

/// Talos Modules
#include "talos/parser/grammar.hpp"
#include "talos/parser/stream.hpp"
#include "talos/syntax/grammar.hpp"

//  MACROS  //

#define TALOS_MM_PARSE_FWD(N, R, T, ...) \
    template <>                          \
    Talos::Syntax::R* Talos::Parser::Dispatch::m_##N<Talos::Syntax::T>(__VA_ARGS__)

#define TALOS_MM_PARSE_DECL(T, P, ...) TALOS_MM_PARSE_FWD(declaration, T, T, Stream* P)
#define TALOS_MM_PARSE_STMT(T, P, ...) TALOS_MM_PARSE_FWD(statement, T, T, Stream* P)
#define TALOS_MM_PARSE_HINT(T, P, ...) TALOS_MM_PARSE_FWD(annotation, T, T, Stream* P)
#define TALOS_MM_PARSE_PREFIX(T, P, A, ...) TALOS_MM_PARSE_FWD(prefix, Expression, T, Stream* P, bool A)
#define TALOS_MM_PARSE_INFIX(T, P, E, A, ...) \
    TALOS_MM_PARSE_FWD(infix, Expression, T, Stream* P, Syntax::Expression* E, bool A)

//  NAMESPACES  //

namespace Talos::Parser {

    /// @brief Parsing Extent.
    enum class Extent : uint8_t {
        CLASS,    // class properties
        STATIC,   // static properties
        MODULE,   // module scoping
        SCOPING,  // function scoping
    };

    /// @brief Syntax Dispatch Methods.
    class Dispatch : public $::Never {
        //  TYPEDEFS  //

        friend struct Generics;    // Template parameters parser.
        friend class Specialized;  // Template arguments parser.

        /// @brief Allow the generator internal access.
        friend struct Syntax::Generator;

        /// @brief Alias the parser precedence.
        using Precedence = Syntax::Precedence;

       public:
        //  PUBLIC METHODS  //

        /**
         * @brief Handles launching the parser.
         * @param parser                    Parser stream.
         * @param nodes                     Statement nodes.
         */
        static inline constexpr void stream(Stream* parser, std::vector<Syntax::Node*>& nodes) {
            while (!parser->eos()) {
                auto* node = m_declaration(parser, Extent::MODULE);
                if ($_LIKELY(node)) nodes.emplace_back(node);
                if (parser->panicking()) parser->synchronize();
            }
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Parses a type-annotation.
         * @param parser                    Parser stream.
         */
        template <std::derived_from<Syntax::Annotation> T>
        static T* m_annotation(Stream* parser);
        static Syntax::Annotation* m_annotation(Stream* parser);

        /**
         * @brief Handles parsing template constraints.
         * @param parser                    Parser stream.
         */
        static std::optional<Syntax::Template> m_template(Stream* parser);

        /**
         * @brief Handles parsing function signatures/prototypes.
         * @param parser                    Parser stream.
         * @param annotated                 Annotation flag.
         */
        static Syntax::Signature* m_signature(Stream* parser, bool annotated = false);
        static Syntax::Parameters* m_parameters(Stream* parser, bool annotated = false);
        static Syntax::Constructor* m_constructor(Stream* parser, bool annotated = false);

        /**
         * @brief Handles constructing anonymous qualifiers.
         * @param parser                    Parser stream.
         * @param name                      Name of qualifier.
         */
        static Syntax::Annotation* m_qualifier(Stream* parser, const $::String::View& name);

        /**
         * @brief Parses a top-level declaration node.
         * @param parser                    Parser stream.
         */
        template <std::derived_from<Syntax::Node> T>
        static T* m_declaration(Stream* parser);

        /**
         * @brief Parses a top-level declaration node.
         * @param parser                    Parser stream.
         * @param extent                    Scoping extent.
         */
        static Syntax::Node* m_declaration(Stream* parser, Extent extent);

        /**
         * @brief Handles parsing any import/export statement.
         * @param parser                    Syntax parser.
         * @param extent                    Scoping extent.
         */
        static Syntax::Node* m_import(Stream* parser, Extent extent);
        static Syntax::Node* m_export(Stream* parser, Extent extent);

        /**
         * @brief Parses any variable declaration.
         * @param parser                    Syntax parser.
         * @param annotated                 Annotation flag.
         */
        static Syntax::Variable* m_variable(Stream* parser, bool annotated = false);

        /**
         * @brief Handles parsing implementation interfaces.
         * @param parser                    Syntax parser.
         */
        static Syntax::Specialization m_implements(Stream* parser);

        /**
         * @brief Parses a declaration subject with details.
         * @param parser                    Syntax parser.
         * @param extent                    Scoping extent.
         */
        static Syntax::Declaration* m_subject(Stream* parser, Extent extent);
        static Syntax::Declaration* m_preamble(Stream* parser, Extent extent);
        static Syntax::Declaration* m_modifiers(Stream* parser, Extent extent);

        /**
         * @brief Handles parsing attributes/decorators.
         * @param parser                    Syntax parser.
         */
        static Reflect::Category m_category(Stream* parser);
        static Syntax::Attribute* m_attribute(Stream* parser);
        static Syntax::Decorator* m_decorator(Stream* parser);

        /**
         * @brief Parses a statement node.
         * @param parser                    Parser stream.
         */
        template <std::derived_from<Syntax::Node> T>
        static T* m_statement(Stream* parser);
        static Syntax::Node* m_statement(Stream* parser);

        /**
         * @brief Handles parsing blocks.
         * @param parser                    Syntax parser.
         * @param module                    Top-level module flag.
         */
        static Syntax::Block* m_block(Stream* parser, Extent extent);

        /**
         * @brief Parses an expression with default precedence.
         * @param parser                    Syntax parser.
         * @param precedence                Precedence value.
         */
        static Syntax::Expression* m_expression(Stream* parser, Precedence precedence = Precedence::ASSIGN);

        /**
         * @brief Parses a prefix expression.
         * @param parser                    Syntax parser.
         * @param assignable                Assignability flag.
         */
        template <std::derived_from<Syntax::Expression> T>
        static Syntax::Expression* m_prefix(Stream* parser, bool assignable);

        /**
         * @brief Parses an infix expression.
         * @param parser                    Syntax parser.
         * @param lvalue                    LHS value.
         * @param assignable                Assignability flag.
         */
        template <std::derived_from<Syntax::Expression> T>
        static Syntax::Expression* m_infix(Stream* parser, Syntax::Expression* lvalue, bool assignable);

        /**
         * @brief Handles parsing names and identifiers.
         * @param parser                    Syntax parser.
         */
        static const Lexer::Token* m_label(Stream* parser);
        static Syntax::Identifier* m_identifier(Stream* parser);

        /**
         * @brief Handles terminating nodes with ';'.
         * @param parser                    Syntax parser.
         * @param node                      Node to terminate.
         * @param describe                  After description.
         */
        static Syntax::Node* m_terminates(Stream* parser, Syntax::Node* node, const $::String::View& describe);

        /**
         * @brief Handles terminating declarations with ';'.
         * @param parser                    Syntax parser.
         * @param describe                  After description.
         */
        template <std::derived_from<Syntax::Declaration> T>
        static inline Syntax::Node* m_terminates(Stream* parser, const $::String::View& describe) {
            return m_terminates(parser, m_declaration<T>(parser), describe);
        }

        /**
         * @brief Handles terminating statements with ';'.
         * @param parser                    Syntax parser.
         * @param describe                  After description.
         */
        template <std::derived_from<Syntax::Statement> T>
        static inline Syntax::Node* m_terminates(Stream* parser, const $::String::View& describe) {
            return m_terminates(parser, m_statement<T>(parser), describe);
        }

        /**
         * @brief Forces a debug assertion for certain tokens.
         * @param token                     Token received.
         * @param expected                  Expected token.
         */
        static inline const Lexer::Token* m_assert(const Lexer::Token* token, $_UNUSED Lexer::Kind expected) {
            return $_ASSERT(token->kind() == expected), token;
        }

        /**
         * @brief Forces a debug assertion for certain tokens.
         * @param token                     Token received.
         * @param flag                      Flag to be tested.
         */
        static inline const Lexer::Token* m_assert(const Lexer::Token* token, $_UNUSED Lexer::Flag flag) {
            return $_ASSERT(token->flags().test(flag)), token;
        }

        /**
         * @brief Forces a debug assertion for certain tokens.
         * @param token                     Token received.
         * @param lexeme                    Expected lexeme.
         */
        static inline const Lexer::Token* m_assert(const Lexer::Token* token, $_UNUSED const $::String::View& lexeme) {
            return $_ASSERT(token->lexeme() == lexeme), token;
        }
    };

}  // namespace Talos::Parser

#endif
