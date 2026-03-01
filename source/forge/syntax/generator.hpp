#ifndef _FORGE_SYNTAX_GENERATOR_HPP
#define _FORGE_SYNTAX_GENERATOR_HPP

/// Forge Modules
#include "forge/syntax/grammar.hpp"
#include "forge/syntax/visitor.hpp"

namespace Forge::Syntax {

    /// @brief Inline Syntax Generator.
    struct Generator {
        //  PUBLIC METHODS  //

        /// @brief Handles generating an expression generator.
        template <class T, class P, class D>
        static inline constexpr Grammar::Table<T, P>& grammar() {
            // prepare the baseline constructor to be used
            using K = Lexer::Kind;
            using R = Grammar::Rule<T, P>;

            // construct the table to be output here
            static auto s_table = Grammar::Table<T, P>();
            static constexpr auto _ = [](K kind) { return static_cast<size_t>(kind); };

            // prepare all the identifiers to be bound
            s_table[_(K::LTRL_TRUE)] = R(D::template m_prefix<True>);
            s_table[_(K::LTRL_FALSE)] = R(D::template m_prefix<False>);

            s_table[_(K::LTRL_STR)] = R(D::template m_prefix<Text>);
            s_table[_(K::LTRL_VOID)] = R(D::template m_prefix<Void>);
            s_table[_(K::LTRL_IDENT)] = R(D::template m_prefix<Identifier>);
            s_table[_(K::DECL_FUNC)] = R(D::template m_prefix<Lambda>);

            // prepare all the numerics to be bound
            s_table[_(K::LTRL_BIN)] = R(D::template m_prefix<Numeric>);
            s_table[_(K::LTRL_OCT)] = R(D::template m_prefix<Numeric>);
            s_table[_(K::LTRL_HEX)] = R(D::template m_prefix<Numeric>);
            s_table[_(K::LTRL_INT)] = R(D::template m_prefix<Numeric>);
            s_table[_(K::LTRL_FLT)] = R(D::template m_prefix<Numeric>);

            // prepare all the specialized expressions to be bound
            s_table[_(K::FLOW_PANIC)] = R(D::template m_prefix<Panic>);
            s_table[_(K::PUNC_POLICY)] = R(D::template m_infix<Spawn>, Precedence::CALL);
            s_table[_(K::PUNC_COMMA)] = R(D::template m_infix<Binary>, Precedence::COMMA);
            s_table[_(K::PUNC_PERIOD)] = R(D::template m_infix<Accessor>, Precedence::CALL);
            s_table[_(K::PUNC_QUERY)] = R(D::template m_infix<Ternary>, Precedence::TERNARY);

            s_table[_(K::PUNC_LBRACE)] = R(D::template m_prefix<Record>);
            s_table[_(K::PUNC_LPAREN)] = R(D::template m_prefix<Group>, D::template m_infix<Call>, Precedence::CALL);
            s_table[_(K::PUNC_LBRACK)] = R(D::template m_prefix<Tuple>, D::template m_infix<Typed>, Precedence::TMPL);

#define FORGE_XX_TOKEN_UNARY(N, ...) s_table[_(K::UNOP_##N)] = R(D::template m_prefix<Unary>);
#include "forge/lexer/_defines/tokens.def"

#define FORGE_XX_TOKEN_BINARY(N, S, P, ...) s_table[_(K::BINOP_##N)] = R(D::template m_infix<Binary>, Precedence::P);
#include "forge/lexer/_defines/tokens.def"

            s_table[_(K::BINOP_AS)] = R(D::template m_infix<Cast>, Precedence::CAST);
            s_table[_(K::BINOP_IS)] = R(D::template m_infix<Infer>, Precedence::INFER);

            // override the "xor" handler with a secondary prefix handler
            s_table[_(K::BINOP_XOR)].prefix = D::template m_prefix<Caret>;

            // override the "sub" handler with a secondary prefix handler
            s_table[_(K::BINOP_SUB)].prefix = D::template m_prefix<Unary>;

            // and return the resulting table now
            return s_table;
        }

        /**
         * @brief Handles parsing expressions.
         * @param parser                Parser instance.
         * @param rank                  Current precendence.
         */
        template <class R, class P, class D>
        static inline R* expression(P* parser, Precedence rank) {
            auto kind = static_cast<size_t>(parser->current()->kind());  // prepare kind
            auto rule = parser->eos() ? Grammar::Rule<R, P>() : grammar<R, P, D>().at(kind);
            if (rule.prefix == nullptr) return parser->report(2000100, "an expression");

            // check if assignment is valid now
            bool assignable = rank <= Precedence::ASSIGN;

            // get the result of the prefix handle
            auto node = rule.prefix(parser, assignable);

            // attempt parsing infix expressions now
            for (;;) {
                if (node == nullptr) return nullptr;  // failed to find
                kind = static_cast<size_t>(parser->peek(INT32_MAX)->kind());
                rule = parser->eos() ? Grammar::Rule<R, P>() : grammar<R, P, D>().at(kind);
                if (rank > rule.precedence) break;  // can safely break

                $_UNUSED auto name = Lexer::Traits::name(static_cast<Lexer::Kind>(kind));
                $_ASSERT(rule.infix, "Unknown infix rule for '{0}'", name);
                node = rule.infix(parser, node, assignable);  // call the infix handler now
            }

            auto invalid = assignable && parser->check(Lexer::Flag::ASSIGNABLE);
            return invalid ? parser->report(node, 2000500) : node;  // return now
        }
    };

}  // namespace Forge::Syntax

#endif
