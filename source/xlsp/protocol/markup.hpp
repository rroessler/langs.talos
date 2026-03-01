#ifndef _XLSP_PROTOCOL_MARKUP_HPP
#define _XLSP_PROTOCOL_MARKUP_HPP

/// XLSP Modules
#include "xlsp/forward/protocol.hpp"

namespace XLSP::Markup {

    /// @brief Markup Content Container.
    class Content {
        //  PROPERTIES  //

        /// @brief Streamed content value.
        $::String::Stream m_value = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted set of markup content.
        constexpr Content() = default;

        /// @brief Allow default construction.
        virtual ~Content() = default;

        //  PUBLIC METHODS  //

        /// @brief The associated markup kind.
        virtual inline constexpr $::String::View kind() const noexcept { return "plaintext"; }

        /// @brief Gets the underlying stream value.
        inline constexpr $::String::Stream& stream() noexcept { return m_value; }

        /// @brief Gets a view of the markup stream buffer.
        inline constexpr $::String::Buffer buffer() const noexcept { return m_value.str(); }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles encoding markup content.
         * @param self                      Content to encode.
         */
        static $::Serde::Object m_encode(const Content& self) {
            return { { "kind", self.kind() }, { "value", self.buffer() } };
        }
    };

    /// @brief Denotes "markdown" Content.
    struct Formatted : public Content {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Content::Content;

        //  PUBLIC METHODS  //

        /// @brief Gets the associated markup kind.
        inline constexpr $::String::View kind() const noexcept final { return "markdown"; }
    };

    //  PUBLIC METHODS  //

    /**
     * @brief Constructs a code-block.
     * @param content               Code content.
     * @param language              Optional language.
     */
    inline constexpr $::String::Buffer Code(const $::String::Buffer& content, const $::String::Buffer& language = "") {
        return "```" + language + '\n' + content + "\n```";
    }

}  // namespace XLSP::Markup

#endif
