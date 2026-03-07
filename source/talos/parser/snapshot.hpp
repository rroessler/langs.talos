#ifndef _TALOS_PARSER_SNAPSHOT_HPP
#define _TALOS_PARSER_SNAPSHOT_HPP

/// Talos Modules
#include "talos/forward/parser.hpp"
#include "talos/lexer/visitor.hpp"
#include "talos/syntax/tree.hpp"

namespace Talos::Parser {

    /// @brief Parser Location Snapshot.
    class Snapshot {
        //  PROPERTIES  //

        /// @brief Snapshot offset value.
        XLSP::Range m_offset = {};

        /// @brief Tokens cache.
        const Lexer::Visitor* m_tokens;

        /// @brief Initial token value.
        const Lexer::Token* m_initial;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a snapshot.
         * @param tokens                Tokens visitor.
         * @param offset                Offset to inherit.
         */
        explicit constexpr Snapshot(const Lexer::Visitor* tokens, const XLSP::Range& offset = {}) :
            Snapshot(tokens, tokens->current(), offset) {}

        /**
         * @brief Constructs a snapshot.
         * @param tokens                Tokens visitor.
         * @param initial               Initial token.
         * @param offset                Offset to inherit.
         */
        explicit constexpr Snapshot(
            const Lexer::Visitor* tokens, const Lexer::Token* initial, const XLSP::Range& offset = {}) :
            m_offset(offset), m_tokens(tokens), m_initial(initial) {}

        //  OPERATOR METHODS  //

        /// @brief Converts this instance to a location.
        inline constexpr operator Syntax::Bounds() const noexcept { return location(); }

        //  PUBLIC METHODS  //

        /// @brief Gets the encapsulated resource value.
        inline constexpr $::URI::View resource() const noexcept { return m_initial->location().resource(); }

        /// @brief Gets the current snapshot bounds to be used.
        inline constexpr Syntax::Bounds location() const noexcept { return m_resolve(m_range()); }

        /**
         * @brief Constructs an offset snapshot.
         * @param
         */
        inline constexpr Snapshot offset(const XLSP::Range& offset) const noexcept {
            return Snapshot(m_tokens, offset);
        }

        /**
         * @brief Encloses a token range within a snapshot.
         * @param inner                 Inner token range.
         */
        inline constexpr Syntax::Bounds enclose(const Lexer::Token* inner) const noexcept {
            return enclose(inner->range());
        }

        /**
         * @brief Encloses a node range within a snapshot.
         * @param inner                 Inner node range.
         */
        inline constexpr Syntax::Bounds enclose(const Syntax::Node* inner) const noexcept {
            return enclose(inner->traits()->range());
        }

        /**
         * @brief Encloses a smaller range within a snapshot.
         * @param inner                 Inner range value.
         */
        inline constexpr Syntax::Bounds enclose(const XLSP::Range& inner) const noexcept { return m_resolve(inner); }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Resolves final snapshot values.
         * @param inner                 Inner range value.
         * @param outer                 Outer range value.
         */
        inline constexpr Syntax::Bounds m_resolve(const XLSP::Range& inner, XLSP::Range outer = {}) const noexcept {
            // resolve the outer range when necessary
            if (outer == XLSP::Range()) outer = m_range();
            if (m_offset != XLSP::Range()) m_shift(outer);

            // finally construct the resulting bounds necessary
            return Syntax::Bounds(resource(), inner, outer);
        }

        /**
         * @brief Handles shifting a range.
         * @param range                 Range to shift.
         */
        inline constexpr void m_shift(XLSP::Range& range) const noexcept {
            if (m_offset.end > range.end) range.end = m_offset.end;
            if (m_offset.start < range.start) range.start = m_offset.start;
        }

        /**
         * @brief Gets the current range value.
         * @param initial                   Initial token.
         */
        inline constexpr XLSP::Range m_range() const noexcept {
            $_ASSERT(m_initial != m_tokens->current());
            auto* ending = m_tokens->previous();  // ending
            if (m_initial == ending) return m_initial->range();
            return { m_initial->range().start, ending->range().end };
        }
    };

}  // namespace Talos::Parser

#endif
