#ifndef _FORGE_PARSER_STREAM_HPP
#define _FORGE_PARSER_STREAM_HPP

/// Forge Modules
#include "forge/diagnostic/reporter.hpp"
#include "forge/parser/snapshot.hpp"

namespace Forge::Parser {

    /// @brief Parser Constructor Options.
    struct Options {
        Syntax::Tree* storage = nullptr;
        Diagnostic::Reporter* reporter = nullptr;
    };

    /// @brief Syntax Parser Implementation.
    class Stream : public Lexer::Visitor {
        //  PROPERTIES  //

        /// @brief Denotes if a synchronizable error occured.
        bool m_panicking = false;

        /// @brief The outgoing syntax buffer.
        Syntax::Tree* m_storage = nullptr;

        /// @brief Diagnostics emitter instance.
        Diagnostic::Reporter* m_reporter = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a parser stream.
         * @param tokens                    Tokens visitor.
         * @param options                   Stream options.
         */
        explicit Stream(const Lexer::Buffer* tokens, const Options& options = {}) :
            Lexer::Visitor(tokens), m_storage(options.storage), m_reporter(options.reporter) {}

        //  PUBLIC METHODS  //

        /// @brief Denotes if the stream is currently panicking.
        inline constexpr bool panicking() const noexcept { return m_panicking; }

        /// @brief Gets a snapshot of the stream.
        inline constexpr Snapshot snapshot() const noexcept { return Snapshot(this); }

        /// @brief Checks the current token against various kinds.
        template <std::same_as<Lexer::Kind>... As>
        inline bool check(const As&... kinds) const {
            return ((kinds == current()->kind()) || ...);
        }

        /// @brief Checks the current token against various flags.
        template <std::same_as<Lexer::Flag>... Fs>
        inline bool check(const Fs&... flags) const {
            return current()->flags().test(flags...);
        }

        /// @brief Attempts matching a token and advances the visitor if it does.
        template <std::same_as<Lexer::Kind>... As>
        inline bool match(const As&... kinds) {
            return check(kinds...) ? advance(), true : false;
        }

        /// @brief Attempts matching a token and advances the visitor if it does.
        template <std::same_as<Lexer::Flag>... Fs>
        inline bool match(const Fs&... flags) {
            return check(flags...) ? advance(), true : false;
        }

        /**
         * @brief Consumes a valid current token.
         * @param kind                  Kind to consume.
         * @param code                  Diagnostic code.
         * @param args                  Format arguments.
         */
        template <class... As>
        inline bool consume(Lexer::Kind kind, Diagnostic::Code code, As&&... args) {
            return $_LIKELY(match(kind)) ? true : (report(code, std::forward<As>(args)...), false);
        }

        /**
         * @brief Forces a token to be expected.
         * @param kind                  Kind of token.
         * @param args                  Format arguments.
         */
        template <class... As>
        inline bool expect(Lexer::Kind kind, As&&... args) {
            // stop early if necessary to do so
            if ($_LIKELY(match(kind))) return true;

            // prepare the quoted symbol to be used
            auto symbol = Lexer::Traits::symbol(kind);
            auto quoted = fmt::format("'{0}'", symbol);

            // and return the resulting failure that occured
            return report(sizeof...(As) ? 2000101 : 2000100, quoted, std::forward<As>(args)...), false;
        }

        /// @brief Handles forcing the parser into a suitable state after panicking.
        inline void synchronize() {
            // declare as not currently panicking
            m_panicking = false;

            // attempt advancing the instance now
            for (; !eos(); advance()) {
                if (match(Lexer::Kind::PUNC_TERM)) break;  // terminators or syncable
                else if (current()->flags().test(Lexer::Flag::SYNCABLE)) break;
            }
        }

        /**
         * @brief Handles allocating a syntax-node.
         * @param args                  Node arguments.
         */
        template <std::derived_from<Syntax::Node> T, class... As>
        inline constexpr T* allocate(As&&... args) {
            return m_storage->m_allocate<T, As...>(std::forward<As>(args)...);
        }

        /**
         * @brief Handles reporting errors.
         * @param location              Source location.
         * @param code                  Diagnostic code.
         * @param args                  Message arguments.
         */
        template <class... As>
        inline std::nullptr_t report(const Resource::Location& location, Diagnostic::Code code, As&&... args) {
            // ignore if currently panicking
            if (m_panicking) return nullptr;

            if (m_reporter) m_panicking = m_reporter->emit(location, code, std::forward<As>(args)...);
            else m_panicking = Diagnostic::Traits::severity(code) == Diagnostic::Severity::ERROR;

            // and return an empty storage value for use
            return nullptr;
        }

        /**
         * @brief Handles reporting errors.
         * @param code                  Diagnostic code.
         * @param args                  Message arguments.
         */
        template <class... As>
        inline std::nullptr_t report(Diagnostic::Code code, As&&... args) {
            return report(eos() ? previous() : current(), code, std::forward<As>(args)...);
        }

        /**
         * @brief Handles reporting errors.
         * @param token                 Token of error.
         * @param code                  Diagnostic code.
         * @param args                  Message arguments.
         */
        template <class... As>
        inline std::nullptr_t report(const Lexer::Token* token, Diagnostic::Code code, As&&... args) {
            if ($_UNLIKELY(token == nullptr)) return nullptr;  // ignore invalid
            else return report(token->location(), code, std::forward<As>(args)...);
        }

        /**
         * @brief Handles reporting errors.
         * @param node                  Node of error.
         * @param code                  Diagnostic code.
         * @param args                  Message arguments.
         */
        template <class... As>
        inline std::nullptr_t report(const Syntax::Node* node, Diagnostic::Code code, As&&... args) {
            if (node == nullptr) return nullptr;  // ignore if the node is currently empty
            return report(node->traits()->location(), code, std::forward<As>(args)...);
        }
    };

}  // namespace Forge::Parser

#endif
