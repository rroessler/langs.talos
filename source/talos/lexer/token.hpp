#ifndef _TALOS_LEXER_TOKEN_HPP
#define _TALOS_LEXER_TOKEN_HPP

/// Talos Modules
#include "talos/lexer/traits.hpp"
#include "talos/resource/location.hpp"
#include "talos/string/intern.hpp"

//  X-MACROS  //

#define XX_TOKEN_FLAGS(X)                               \
    X(ASSIGNABLE) /** Assignment tokens. */             \
    X(RESERVED)   /** Reserved keywords. */             \
    X(SYNCABLE)   /** Can be synchronized on. */        \
    X(VARIABLE)   /** Denotes variable declarations. */ \
    X(ANNOTATION) /** Could be an annotation. */        \
    X(MODIFIER)   /** Potential modifier keyword. */    \
    X(DECORATES)  /** Adds decoration to variables. */  \
    X(LEADING)    /** Valid leading tokens. */          \
    X(TRAILING)   /** Valid panic trailing tokens. */   \
    X(WHITESPACE) /** Any whitespace tokens. */         \
    X(NUMERIC)    /** For all numeric literals. */      \
    X(BOOLEAN)    /** For all boolean literals. */

//  NAMESPACES  //

namespace Talos::Lexer {

    /// @brief Available Token Flags.
    $_XX_ENUM_CLASS(Flag, uint16_t, XX_TOKEN_FLAGS);

    /// @brief Token Structure.
    class Token : public $::Printable {
        //  PROPERTIES  //

        Kind m_kind;                    // Kind of token.
        $::String::Buffer m_lexeme;     // Raw lexeme value.
        Resource::Location m_location;  // Resource location.

#define TALOS_XX_TOKEN_BASE(_, ...) $::Enum::Flags<Flag>(__VA_ARGS__),
        static constexpr size_t m_maximum = static_cast<size_t>(Kind::MISC_MAX) + 1;
        static constexpr std::array<$::Enum::Flags<Flag>, m_maximum> m_flags = {
#include "talos/lexer/_defines/tokens.def"
        };

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a default invalid token.
        constexpr Token() : Token(Kind::MISC_MAX) {}

        /**
         * @brief Constructs a token value.
         * @param kind                  Token kind.
         * @param location              Resource location.
         */
        constexpr Token(Kind kind, const Resource::Location& location = {}) :
            m_kind(kind), m_lexeme(Traits::symbol(kind)), m_location(location) {}

        /**
         * @brief Constructs a token value.
         * @param kind                  Token kind.
         * @param lexeme                Lexeme value.
         * @param location              Resource location.
         */
        constexpr Token(Kind kind, const $::String::View& lexeme, const Resource::Location& location = {}) :
            m_kind(kind), m_lexeme(lexeme), m_location(location) {}

        //  PUBLIC METHODS  //

        inline constexpr Kind kind() const noexcept { return m_kind; }
        inline constexpr $::String::View lexeme() const noexcept { return m_lexeme; }
        inline constexpr const XLSP::Range& range() const noexcept { return m_location.range(); }
        inline constexpr const Resource::Location& location() const noexcept { return m_location; }
        inline constexpr $::Enum::Flags<Flag> flags() const noexcept { return m_flags.at(static_cast<size_t>(m_kind)); }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles printing tokens.
         * @param os                    Output stream.
         * @param self                  Token to print.
         */
        static inline void m_print($::Stream::Output& os, const Token& self) {
            auto name = Traits::name(self.m_kind);
            auto position = self.m_location.range().start;

            // print the resulting token now for debug viewing
            os << fmt::format("[{0} / {1}] = '{2}'", name, position, self.m_lexeme);
        }
    };

}  // namespace Talos::Lexer

//  UNDEFINES  //

#undef XX_TOKEN_FLAGS

#endif
