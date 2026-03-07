#ifndef _TALOS_SYNTAX_METADATA_HPP
#define _TALOS_SYNTAX_METADATA_HPP

/// Talos Modules
#include "talos/lexer/buffer.hpp"
#include "talos/module/metadata.hpp"
#include "talos/syntax/tree.hpp"

namespace Talos::Module {

    /// @brief Constructs a set of syntax metadata.
    template <>
    class Metadata::Attributes<Phase::PARSED> : public Metadata {
        //  PROPERTIES  //

        /// @brief Associated tokens buffer.
        Lexer::Buffer m_tokens = Lexer::Buffer();

        /// @brief Associated syntax tree.
        $::Ptr::Unique<Syntax::Tree> m_tree = $::New().unique<Syntax::Tree>();

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a set of exports.
        explicit Attributes() = default;

        //  PUBLIC METHODS  //

        inline constexpr Lexer::Buffer& tokens() noexcept { return m_tokens; }
        inline constexpr const Lexer::Buffer& tokens() const noexcept { return m_tokens; }

        inline constexpr $::Ptr::Unique<Syntax::Tree>& tree() noexcept { return m_tree; }
        inline constexpr const Syntax::Tree* tree() const noexcept { return m_tree.get(); }
    };

}  // namespace Talos::Module

#endif
