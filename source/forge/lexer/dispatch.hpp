#ifndef _FORGE_LEXER_DISPATCH_HPP
#define _FORGE_LEXER_DISPATCH_HPP

/// Forge Modules
#include "forge/lexer/scanner.hpp"

namespace Forge::Lexer {

    /// @brief Explicit Tail-Call Callback.
    using Callback = void (*)(Scanner&, Buffer&);

    /// @brief Dispatch Table Container.
    using Table = std::array<Callback, UINT8_MAX + 1>;

    /// @brief Dispatch Handlers.
    struct Dispatch : public $::Never {
        //  TYPEDEFS  //

        /// @brief Allow the generator internal access.
        friend struct Generator;

       private:
        //  PROPERTIES  //

        /// @brief Explicit maximum size.
        static constexpr auto size = std::tuple_size_v<Table>;

       public:
        //  PUBLIC METHODS  //

        /**
         * @brief Dispatches the next callback.
         * @param lexer                 Lexical scanner.
         * @param tokens                Tokens buffer.
         */
        static void next(Scanner& lexer, Buffer& tokens);

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Escapes a code-point to readable value.
         * @param cp                    Code-point to convert.
         */
        static $::String::Buffer m_escape(int64_t cp);

        static void m_string(Scanner& lexer, Buffer& tokens);
        static void m_invalid(Scanner& lexer, Buffer& tokens);
        static void m_numeric(Scanner& lexer, Buffer& tokens);
        static void m_identifier(Scanner& lexer, Buffer& tokens);

        template <uint8_t C>
        static void m_symbol(Scanner& lexer, Buffer& tokens);

        static Token m_comment(Scanner& lexer);
        static Token m_numeric(Scanner& lexer);
        static Token m_binary(Scanner& lexer);
        static Token m_octal(Scanner& lexer);
        static Token m_hexadecimal(Scanner& lexer);
    };

}  // namespace Forge::Lexer

//  SPECIALIZATIONS  //

#define FORGE_XX_TOKEN_SYMBOL(_, S, ...) \
    template <>                          \
    void Forge::Lexer::Dispatch::m_symbol<S[0]>(Scanner & lexer, Buffer & tokens);
#include "forge/lexer/_defines/tokens.def"

#endif
