#ifndef _FORGE_FORMAT_READER_HPP
#define _FORGE_FORMAT_READER_HPP

/// Forge Modules
#include "forge/diagnostic/view.hpp"
#include "forge/format/comments.hpp"
#include "forge/format/storage.hpp"
#include "forge/lexer/visitor.hpp"

namespace Forge::Format {

    /// @brief Format Reader Implementation.
    class Reader : public Lexer::Visitor {
        //  PROPERTIES  //

        /// @brief Format options available.
        const Options* m_options;

        /// @brief Format Node Storage.
        $::Ptr::Unique<Storage> m_storage;

        /// @brief Currently encapsulated comment tokens.
        $::Ptr::Unique<Comments> m_comments = $::New().unique<Comments>();

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a format reader.
         * @param tokens                Tokens visitor.
         * @param options               Format options.
         */
        explicit Reader(const Lexer::Buffer* tokens);
        explicit Reader(const Lexer::Buffer* tokens, const Options* options);

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying node storage.
        inline constexpr Storage* storage() const noexcept { return m_storage.get(); }

        /// @brief Gets the underlying formatter options.
        inline constexpr const Options* options() const noexcept { return m_options; }

        /// @brief Gets the underlying comments buffer.
        inline constexpr const Comments* comments() const noexcept { return m_comments.get(); }

        /**
         * @brief Flushes the currently queued comments.
         * @param trim                      Force trimming.
         */
        inline constexpr Buffer flush(bool trim = false) {
            return $::Ranges::To<Node*>(
                std::views::transform(m_comments->flush(trim), [&](const $::String::View& comment) {
                    return comment.empty() ? m_storage->empty() : m_storage->comment(comment);
                }));
        }

        /// @brief Handles skipping leading whitespace.
        inline constexpr void skip() {
            m_until([](const Lexer::Token* token) { return !token->flags().test(Lexer::Flag::WHITESPACE); });
        }

        /// @brief Denotes if we have a trailing comment
        inline constexpr Node* trailing() noexcept {
            // get the previous and current token values now
            const Lexer::Token *before = previous(), *after = current();

            // stop if we fail certain conditions
            if (before->kind() == Lexer::Kind::MISC_CMT) return nullptr;
            if (after->kind() != Lexer::Kind::MISC_CMT) return nullptr;

            // since a valid trailing comment, we want to eat (even if empty)
            auto comment = advance()->lexeme();

            // we trail with a line when empty, or a space when a comment exists
            return comment.size() ? m_storage->comment(comment) : nullptr;
        }

        /**
         * @brief Checks for an incoming token.
         * @param kinds                 Token to expect.
         */
        template <std::same_as<Lexer::Kind>... Ks>
        inline constexpr bool check(const Ks&... kinds) {
            return m_until([kinds...](const Lexer::Token* token) { return ((kinds == token->kind()) || ...); });
        }

        /**
         * @brief Checks for an incoming token.
         * @param flags                 Flag to expect.
         */
        template <std::same_as<Lexer::Flag>... Fs>
        inline constexpr bool check(const Fs&... flags) {
            return m_until([flags...](const Lexer::Token* token) { return token->flags().test(flags...); });
        }

        /**
         * @brief Checks for an incoming token.
         * @param kinds                 Token to expect.
         */
        template <std::same_as<Lexer::Kind>... Ks>
        inline constexpr bool match(const Ks&... kinds) {
            return check(kinds...) ? advance(), true : false;
        }

        /**
         * @brief Checks for an incoming token.
         * @param flags                 Flag to expect.
         */
        template <std::same_as<Lexer::Flag>... Fs>
        inline constexpr bool match(const Fs&... flags) {
            return check(flags...) ? advance(), true : false;
        }

        /**
         * @brief Handles reporting formatting errors.
         * @param args                  Error arguments.
         */
        template <class... As>
        inline constexpr std::nullptr_t report(As&&...) {
            return nullptr;
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Attempts skipping to a desired token.
         * @param condition             Condition to skip.
         */
        template <class C>
        inline constexpr bool m_until(C condition) {
            // get the original position now
            auto index = m_tell();

            // prepare the comments to
            auto pending = Comments::View();

            // attempt iterating over the current token now
            for (auto* token = current(); !condition(token); advance(), token = current()) {
                // stop early if we did not receive a comment here
                if (!token->flags().test(Lexer::Flag::WHITESPACE)) return m_rewind(index), false;

                // otherwise push the comment onto the incoming ones (ignore terminators)
                if (token->kind() == Lexer::Kind::MISC_CMT) pending.emplace_back(token->lexeme());
            }

            // validate all the pending comments to be appended
            return m_comments->append(pending), true;
        }
    };

}  // namespace Forge::Format

#endif
