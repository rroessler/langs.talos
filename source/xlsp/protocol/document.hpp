#ifndef _XLSP_PROTOCOL_DOCUMENT_HPP
#define _XLSP_PROTOCOL_DOCUMENT_HPP

/// XLSP Modules
#include "xlsp/protocol/range.hpp"

//  X-MACROS  //

/// @brief Document Sync Kinds.
#define XX_DOCUMENT_SYNC(X) \
    X(NONE) /** 0 */        \
    X(FULL) /** 1 */        \
    X(INCR) /** 2 */

//  NAMESPACES  //

namespace XLSP {

    /// @brief Text Document Symbol.
    struct Symbol {
        //  TYPEDEFS  //

        /// @brief Available Symbol Kinds.
        enum class Kind : uint8_t {
            UNKNOWN = 0,
            FILE = 1,
            MODULE = 2,
            NAMESPACE = 3,
            PACKAGE = 4,
            CLASS = 5,
            METHOD = 6,
            PROPERTY = 7,
            FIELD = 8,
            CONSTRUCTOR = 9,
            ENUM = 10,
            INTERFACE = 11,
            FUNCTION = 12,
            VARIABLE = 13,
            CONSTANT = 14,
            STRING = 15,
            NUMBER = 16,
            BOOLEAN = 17,
            ARRAY = 18,
            OBJECT = 19,
            KEY = 20,
            VOID = 21,
            VARIANT = 22,
            STRUCT = 23,
            EVENT = 24,
            OPERATOR = 25,
            TPARAM = 26,
        };

        //  PROPERTIES  //

        /// @brief Kind of symbol.
        Kind kind = Kind::UNKNOWN;

        /// @brief Deprecation state.
        bool deprecated = false;

        /// @brief Base range of symbol.
        Range range = {};

        /// @brief Selection range of symbol.
        Range selection = {};

        /// @brief Name of the symbol.
        $::String::Buffer name = {};

        //  CONSTRUCTORS  //

        /// @brief Constructs invalid symbols.
        constexpr Symbol() = default;

        /**
         * @brief Constructs a document symbol.
         * @param name                      Name of symbol.
         * @param kind                      Kind of symbol.
         */
        constexpr Symbol(const $::String::View& name, Kind kind = Kind::UNKNOWN) : kind(kind), name(name) {}

        //  OPERATOR METHODS  //

        inline constexpr operator bool() const noexcept { return kind != Kind::UNKNOWN; }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles encoding a document symbol.
         * @param self                      Symbol to encode.
         */
        static $::Serde::Value m_encode(const Symbol& self) {
            // construct the basis of our symbol
            $::Serde::Object symbol = {
                { "name", self.name },
                { "kind", self.kind },
                { "range", $::Reflect::encode(self.range) },
                { "selectionRange", $::Reflect::encode(self.selection) },
            };

            // bind the deprecation status as well
            if (self.deprecated) symbol["tags"] = { 1 };

            // and resolve our symbol
            return symbol;
        }
    };

    /// @brief Document Link (eg: Internal/External Website).
    struct Anchor {
        //  PROPERTIES  //

        /// @brief Document Link Range.
        Range range = {};

        /// @brief The resource target to link.
        $::URI::Buffer target;

        /// @brief Link text to show on hover.
        $::String::Buffer tooltip = "";

        //  CONSTRUCTORS  //

        /// @brief Do not allow default construction.
        constexpr Anchor() = delete;

        /**
         * @brief Constructs an empty document.
         * @param resource                  Document resource.
         * @param range                     Range to bind.
         */
        constexpr Anchor(const $::URI::Buffer& resource, const Range& range = {}) : range(range), target(resource) {}

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles encoding a document link.
         * @param self                      Link to encode.
         */
        static $::Serde::Value m_encode(const Anchor& self) {
            // construct the basis of our link
            $::Serde::Object link = {
                { "range", $::Reflect::encode(self.range) },
                { "target", $::Reflect::encode(self.target) },
            };

            // bind the resulting tooltip if it has a size
            if (self.tooltip.size()) link["tooltip"] = self.tooltip;

            // return the reslting link
            return link;
        }
    };

    /// @brief Text Document Completion.
    struct Completion {
        //  TYPEDEFS  //

        /// @brief Available completion kinds.
        enum class Kind : uint8_t {
            TEXT = 1,
            METHOD = 2,
            FUNCTION = 3,
            CONSTRUCTOR = 4,
            FIELD = 5,
            VARIABLE = 6,
            CLASS = 7,
            INTERFACE = 8,
            MODULE = 9,
            PROPERTY = 10,
            UNIT = 11,
            VALUE = 12,
            ENUM = 13,
            KEYWORD = 14,
            SNIPPET = 15,
            COLOR = 16,
            FILE = 17,
            REFERENCE = 18,
            FOLDER = 19,
            VARIANT = 20,
            CONSTANT = 21,
            STRUCT = 22,
            EVENT = 23,
            OPERATOR = 24,
            TPARAM = 25
        };

        //  PROPERTIES  //

        /// @brief The kind of completion.
        Kind kind = Kind::TEXT;

        /// @brief Label of the completion item.
        $::String::Buffer label;

        //  CONSTRUCTORS  //

        /// @brief Do not allow empty completion items.
        constexpr Completion() = delete;

        /**
         * @brief Constructs an empty completion.
         * @param label             Completion label.
         * @param kind              Kind of completion.
         */
        constexpr Completion(const $::String::Buffer& label, Kind kind = Kind::TEXT) : kind(kind), label(label) {}

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles encoding a completion.
         * @param self                      Completion to encode.
         */
        static $::Serde::Value m_encode(const Completion& self) {
            return { { "kind", self.kind }, { "label", self.label } };
        }
    };

    /// @brief Text Document Item.
    struct Document {
        //  TYPEDEFS  //

        /// @brief Document Synchronization Kinds.
        $_XX_ENUM_CLASS(Sync, uint8_t, XX_DOCUMENT_SYNC);

        /// @brief Document Edit Structure.
        struct Edit {
            //  PROPERTIES  //

            /// @brief Range to edit.
            Range range = {};

            /// @brief Replacement text to use.
            $::String::Buffer text = "";

            //  CONSTRUCTORS  //

            /// @brief Constructs an empty edit.
            explicit Edit() = default;

            /**
             * @brief Constructs a document edit.
             * @param text              Text replacement.
             * @param range             Range of replacement.
             */
            explicit Edit(const $::String::Buffer& text, const Range& range) : range(range), text(text) {}

           protected:
            //  PRIVATE METHODS  //

            /**
             * @brief Handles encoding a document edit.
             * @param self                      Edit to encode.
             */
            static $::Serde::Value m_encode(const Edit& self) {
                return { { "range", $::Reflect::encode(self.range) }, { "newText", self.text } };
            }
        };

        /// @brief Content Change Event.
        struct Change {
            //  PROPERTIES  //

            /// @brief Text being replaced.
            $::String::Buffer text = "";

            /// @brief Range the document modifies.
            std::optional<Range> range = std::nullopt;

            //  CONSTRUCTORS  //

            /// @brief Constructs a default change value.
            explicit Change() = default;

            //  PUBLIC METHODS  //

            /**
             * @brief Applies a change to the given content.
             * @param content                   Content to update.
             * @param encoding                  Encoding to use.
             */
            void apply($::String::Buffer& content, const Encoding::Type& encoding) const;

           protected:
            //  PRIVATE METHODS  //

            /**
             * @brief Handles decoding a document change
             * @param value                     Value to decode.
             */
            static Change m_decode(const $::Serde::Value& value) {
                // prepare the base change
                auto change = Change();

                // attempt updating our various items
                change.text = *value.at<$::Serde::Text>("text");

                // handle the optional values
                if (value.has("range")) change.range = $::Reflect::decode<Range>(value.at("range"));

                // and return the resulting change
                return change;
            }
        };

        /// @brief Text Document Identifier.
        struct Identifier {
            //  PROPERTIES  //

            /// @brief Document URI value.
            $::URI::Buffer resource;

            /// @brief Versioned identifier value.
            std::optional<int64_t> version = std::nullopt;

            //  CONSTRUCTORS  //

            /// @brief Do not allow default construction.
            explicit constexpr Identifier() = delete;

            /**
             * @brief Constructs an empty document.
             * @param resource                  Document resource.
             */
            explicit constexpr Identifier(const $::URI::Buffer& resource) : resource(resource) {}

           protected:
            //  PRIVATE METHODS  //

            /**
             * @brief Handles encoding a document identifier.
             * @param self                      Identifier to encode.
             */
            static $::Serde::Value m_encode(const Identifier& self) {
                $::Serde::Object value = { { "uri", $::Reflect::encode(self.resource) } };
                if (self.version.has_value()) value["version"] = *self.version;
                return value;  // return the resulting identifier value
            }

            /**
             * @brief Handles decoding a document identifier.
             * @param value                     Value to decode.
             */
            static Identifier m_decode(const $::Serde::Value& value) {
                auto identifier = Identifier($::Reflect::decode<$::URI::Buffer>(value.at("uri")));
                if (auto* v = value.at<$::Serde::Number>("version")) identifier.version = static_cast<int64_t>(*v);
                return identifier;  // return the resulting identifier now
            }
        };

       private:
        //  PROPERTIES  //

        /// @brief Document identifier value.
        Identifier m_identifier;

        /// @brief Current document text.
        $::String::Buffer m_text = "";

        /// @brief Language identifier.
        $::String::Buffer m_language = "plaintext";

       public:
        //  CONSTRUCTORS  //

        /// @brief Do not allow default construction.
        explicit constexpr Document() = delete;

        /**
         * @brief Constructs an empty document.
         * @param resource          Document resource.
         */
        explicit constexpr Document(const $::URI::Buffer& resource) : m_identifier(resource) {}

        /**
         * @brief Constructs an empty document.
         * @param identifier        Document identifier.
         */
        explicit constexpr Document(const Identifier& identifier) : m_identifier(identifier) {}

        //  PUBLIC METHODS  //

        inline constexpr $::String::Buffer& text() noexcept { return m_text; }
        inline constexpr const $::String::Buffer& text() const noexcept { return m_text; }
        inline constexpr $::URI::View resource() const noexcept { return m_identifier.resource; }
        inline constexpr $::String::View language() const noexcept { return m_language; }
        inline constexpr const Identifier& identifier() const noexcept { return m_identifier; }
        inline constexpr std::optional<int64_t> version() const noexcept { return m_identifier.version; }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles decoding a document value.
         * @param value                     Value to decode.
         */
        static Document m_decode(const $::Serde::Value& value) {
            // construct the document from the URI value
            auto document = Document($::Reflect::decode<Identifier>(value));

            // prepare the other fields to be set
            document.m_text = *value.at<$::Serde::Text>("text");
            document.m_language = *value.at<$::Serde::Text>("languageId");

            // return the resulting document now
            return document;
        }
    };

}  // namespace XLSP

//  UNDEFINES  //

#undef XX_DOCUMENT_SYNC

#endif
