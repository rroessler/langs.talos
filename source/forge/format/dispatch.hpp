#ifndef _FORGE_FORMAT_DISPATCH_HPP
#define _FORGE_FORMAT_DISPATCH_HPP

/// Forge Modules
#include "forge/format/grammar.hpp"
#include "forge/format/pipeline.hpp"
#include "forge/syntax/grammar.hpp"
#include "forge/syntax/visitor.hpp"

//  MACROS  //

#define FORGE_MM_FORMAT_FWD(N, T, ...) \
    template <>                        \
    Forge::Format::Node* Forge::Format::Dispatch::m_##N<Forge::Syntax::T>(__VA_ARGS__)

#define FORGE_MM_FORMAT_DECL(T, R, ...) FORGE_MM_FORMAT_FWD(declaration, T, Reader* R)
#define FORGE_MM_FORMAT_STMT(T, R, ...) FORGE_MM_FORMAT_FWD(statement, T, Reader* R)
#define FORGE_MM_FORMAT_HINT(T, R, ...) FORGE_MM_FORMAT_FWD(annotation, T, Reader* R)
#define FORGE_MM_FORMAT_PREFIX(T, R, ...) FORGE_MM_FORMAT_FWD(prefix, T, Reader* R, bool)
#define FORGE_MM_FORMAT_INFIX(T, R, E, ...) FORGE_MM_FORMAT_FWD(infix, T, Reader* R, Node* E, bool)

//  NAMESPACES  //

namespace Forge::Format {

    /// @brief Handles reading/writing formats.
    class Dispatch : public $::Never {
        //  TYPEDEFS  //

        /// @brief Allow the pipeline internal access.
        friend class Pipeline;

        /// @brief Allow the generator internal access.
        friend struct Syntax::Generator;

        /// @brief Dispatch precedence.
        using Precedence = Syntax::Precedence;

        /// @brief Exit condition typing.
        using Condition = $::Functor::Unique<bool(Reader*)>;

        /// @brief Delimited Initializer.
        struct Delimited {
            //  PROPERTIES  //

            /// @brief Denotes if trailing separators are valid.
            bool trailing = false;

            Node* separator;      // Separator value.
            Callback callback;    // Callback value.
            Condition condition;  // Condition value.

            //  CONSTRUCTORS  //

            /// @brief Constructs a delimited set options.
            constexpr Delimited() : Delimited(nullptr, m_condition) {}

            /**
             * @brief Constructs delimited options.
             * @param separator             Separator to bind.
             * @param condition             Condition to bind.
             */
            constexpr Delimited(Lexer::Kind condition) : Delimited(nullptr, condition) {}
            constexpr Delimited(Condition&& condition) : Delimited(nullptr, std::move(condition)) {}

            /**
             * @brief Constructs delimited options.
             * @param separator             Separator to bind.
             * @param condition             Condition to bind.
             */
            constexpr Delimited(Node* separator, Lexer::Kind condition) : Delimited(separator, m_callback, condition) {}
            constexpr Delimited(Node* separator, Condition&& condition) :
                Delimited(separator, m_callback, std::move(condition)) {}

            /**
             * @brief Constructs delimited options.
             * @param callback              Callback to bind.
             * @param condition             Condition to bind.
             */
            constexpr Delimited(Callback&& callback, Lexer::Kind condition) :
                Delimited(nullptr, std::move(callback), condition) {}

            /**
             * @brief Constructs delimited options.
             * @param callback              Callback to bind.
             * @param condition             Condition to bind.
             */
            constexpr Delimited(Callback&& callback, Condition&& condition) :
                Delimited(nullptr, std::move(callback), std::move(condition)) {}

            /**
             * @brief Constructs delimited options.
             * @param separator             Separator to bind.
             * @param callback              Callback to bind.
             * @param condition             Condition to bind.
             */
            constexpr Delimited(Node* separator, Callback&& callback) :
                Delimited(separator, std::move(callback), m_condition) {}

            /**
             * @brief Constructs delimited options.
             * @param separator             Separator to bind.
             * @param callback              Callback to bind.
             * @param condition             Condition to bind.
             */
            constexpr Delimited(Node* separator, Callback&& callback, Condition&& condition) :
                separator(separator), callback(std::move(callback)), condition(std::move(condition)) {}

            /**
             * @brief Constructs delimited options.
             * @param separator             Separator to bind.
             * @param callback              Callback to bind.
             * @param condition             Condition to bind.
             */
            constexpr Delimited(Node* separator, Callback&& callback, Lexer::Kind condition) :
                Delimited(separator, std::move(callback), m_closing(condition)) {}

            //  PUBLIC METHODS  //

            /**
             * @brief Checks for delimited exit conditions.
             * @param reader                Format reader.
             */
            inline constexpr bool exit(Reader* reader) const noexcept { return condition(reader); }

            /**
             * @brief Consumes the next node available.
             * @param reader                Format reader.
             */
            inline constexpr Node* consume(Reader* reader) const noexcept {
                auto* node = callback(reader);  // run the initial callback instance now
                if (separator == reader->storage()->comma()) reader->match(Lexer::Kind::PUNC_COMMA);
                return node;  // and return the resulting node that was consumed now
            }

           private:
            //  PRIVATE METHODS  //

            /// @brief Default condition value.
            static inline bool m_condition(Reader*) { return false; }

            /**
             * @brief Constructs a suitable condition.
             * @param closing               Closing token.
             */
            static inline Condition m_closing(Lexer::Kind closing) {
                return [closing](Reader* reader) { return reader->check(closing); };
            }

            /// @brief Default callback value.
            static inline Node* m_callback(Reader* reader) { return m_declaration(reader); }
        };

        //  PRIVATE METHODS  //

        /**
         * @brief Handles reading annotations.
         * @param reader                Format reader.
         */
        template <std::derived_from<Syntax::Node> T>
        static Node* m_annotation(Reader* reader);
        static Node* m_annotation(Reader* reader);

        /**
         * @brief Handles parsing template parameters.
         * @param reader                Format reader.
         */
        static Node* m_template(Reader* reader);

        /**
         * @brief Handles parsing function signatures.
         * @param reader                Format reader.
         */
        static Node* m_signature(Reader* reader);
        static Node* m_parameters(Reader* reader);
        static Node* m_constructor(Reader* reader);

        /**
         * @brief Handles reading declarations.
         * @param reader                Format reader.
         */
        template <std::derived_from<Syntax::Node> T>
        static Node* m_declaration(Reader* reader);
        static Node* m_declaration(Reader* reader);

        /**
         * @brief Handles incoming import/exports.
         * @param reader                Format reader.
         */
        static Node* m_export(Reader* reader);
        static Node* m_import(Reader* reader, bool exported);

        /**
         * @brief Handles subject parsing.
         * @param reader                Format reader.
         * @param kind                  Lexical kind.
         */
        static Node* m_subject(Reader* reader);
        static Node* m_subject(Reader* reader, Lexer::Kind kind);

        /**
         * @brief Handles parsing declaration preamble.
         * @param reader                Format reader.
         */
        static Node* m_preamble(Reader* reader);

        /**
         * @brief Handles parsing declaration modifiers.
         * @param reader                Format reader.
         */
        static Node* m_modifiers(Reader* reader, Variable::Modifiers modifiers = {});

        /**
         * @brief Handles parsing declaration attributes/decorators.
         * @param reader                Format reader.
         */
        static Node* m_attribute(Reader* reader);
        static Node* m_decorator(Reader* reader);

        /**
         * @brief Handles parsing a collection of nodes.
         * @param reader                Format reader.
         * @param options               Options to bind.
         */
        static Node::List* m_collection(Reader* reader, Delimited&& options = {});
        static Node::List* m_delimited(Reader* reader, Delimited&& options = {});

        /**
         * @brief Handles reading variables.
         * @param reader                Format reader.
         * @param compress              Parameter compressed.
         */
        static Node* m_variable(Reader* reader, bool compressed = false);

        /**
         * @brief Handles reading statements.
         * @param reader                Format reader.
         * @param group                 Block header.
         */
        template <std::derived_from<Syntax::Node> T>
        static Node* m_statement(Reader* reader);
        static Node* m_statement(Reader* reader, Node::Group* group = nullptr);

        /**
         * @brief Handles parsing blocks.
         * @param reader                Format reader.
         * @param group                 Associated group.
         */
        static Node* m_block(Reader* reader, Node::Group* group = nullptr);

        /**
         * @brief Handles reading expressions.
         * @param reader                Format reader.
         */
        static Node* m_expression(Reader* reader, Precedence precedence = Precedence::ASSIGN);

        /**
         * @brief Handles parsing a condition node.
         * @param reader                Format reader.
         */
        static Node* m_conditional(Reader* reader);

        /**
         * @brief Handles parsing binary expressions.
         * @param reader                Format reader.
         * @param left                  Left-most node.
         * @param right                 Right-most callback.
         */
        static Node* m_binary(Reader* reader, Node* left, Callback&& right);

        /**
         * @brief Handles parsing prefixed expressions.
         * @param reader                Format reader.
         */
        template <std::derived_from<Syntax::Expression> T>
        static Node* m_prefix(Reader* reader, bool);

        /**
         * @brief Handles parsing infixed expressions.
         * @param reader                Format reader.
         * @param value                 Left-most value.
         */
        template <std::derived_from<Syntax::Expression> T>
        static Node* m_infix(Reader* reader, Node* value, bool = false);

        /**
         * @brief Handles assignment parsing.
         * @param reader                Format reader.
         * @param target                Target to assign.
         * @param callback              Value callback.
         */
        static Node* m_assignment(Reader* reader, Node* target);
        static Node* m_assignment(Reader* reader, Node* target, Callback&& callback);

        /**
         * @brief Handles parsing a valid identifier.
         * @param reader                Format reader.
         */
        static Node* m_identifier(Reader* reader);

        /**
         * @brief Handles parsing an identifier chain.
         * @param reader                Format reader.
         */
        static Node* m_chain(Reader* reader);

        /**
         * @brief Handles specializing a template.
         * @param reader                Format reader.
         * @param qualifier             Qualifier to specialize.
         */
        static Node* m_specialize(Reader* reader, Node* qualifier);

        /**
         * @brief Handles parsing with leading comments.
         * @param reader                Format reader.
         * @param callback              Incoming node callback.
         * @param trim                  Forcibly trim comments.
         */
        static Buffer m_leading(Reader* reader, bool trim = true);
        static Node* m_leading(Reader* reader, Callback&& callback, bool trim = true);

        /**
         * @brief Handles parsing with trailing comments.
         * @param reader                Format reader.
         */
        static Node* m_trailing(Reader* reader);
        static Node* m_trailing(Reader* reader, Node* node);
        static Node* m_trailing(Reader* reader, Callback&& callback);

        /**
         * @brief Handles terminating nodes with a semicolon.
         * @param reader                Format reader.
         * @param node                  Node to terminate.
         */
        static Node* m_terminates(Reader* reader, Node* node);

        /**
         * @brief Handles terminating declarations.
         * @param reader                Format reader.
         */
        template <std::derived_from<Syntax::Declaration> T>
        static inline Node* m_terminates(Reader* reader) {
            return m_terminates(reader, m_declaration<T>(reader));
        }

        /**
         * @brief Handles terminating statements.
         * @param reader                Format reader.
         */
        template <std::derived_from<Syntax::Statement> T>
        static inline Node* m_terminates(Reader* reader) {
            return m_terminates(reader, m_statement<T>(reader));
        }
    };

}  // namespace Forge::Format

//  SPECIALIZATIONS  //

#define X(N, ...) FORGE_MM_FORMAT_HINT(N, , );
FORGE_XX_ANNOTATION_NODES(X)
#undef X

#define X(N, ...) FORGE_MM_FORMAT_DECL(N, , );
X(Parameters);
X(Constructor);
X(Signature);

X(Declaration);
FORGE_XX_ANONYMOUS_NODES(X)
FORGE_XX_DECLARATION_NODES(X)
#undef X

#define X(N, ...) FORGE_MM_FORMAT_STMT(N, , );
FORGE_XX_STATEMENT_NODES(X)
#undef X

#endif
