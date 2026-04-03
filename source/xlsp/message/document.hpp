#ifndef _XLSP_MESSAGE_DOCUMENT_HPP
#define _XLSP_MESSAGE_DOCUMENT_HPP

/// XLSP Modules
#include "xlsp/message/notification.hpp"
#include "xlsp/message/request.hpp"
#include "xlsp/protocol/document.hpp"
#include "xlsp/protocol/format.hpp"
#include "xlsp/protocol/markup.hpp"

//  MACROS  //

/// @brief Helper for defining document extensions.
#define XLSP_MESSAGE_DOCUMENT(T, E, ...)                                                                 \
    XLSP_MESSAGE_EXTENDS(Request::Params, T, E) {                                                        \
        using Layout<XLSP_MESSAGE_TYPE(E)>::Layout;                                                      \
        explicit Params(const Layout& layout) : Layout(layout) {}                                        \
                                                                                                         \
       protected:                                                                                        \
        static Params m_decode(const $::Serde::Value& value) { return Params(Layout::m_decode(value)); } \
    }

//  NAMESPACES  //

namespace XLSP {

    /// @brief Document Identifier Message.
    template <>
    struct Message::Layout<Message::Type::DOCUMENT_IDENTIFIER> {
        //  PROPERTIES  //

        /// @brief Underlying text-document.
        Document::Identifier identifier;

        //  CONSTRUCTORS  //

        /// @brief Do not allow default construction.
        explicit Layout() = delete;

        /**
         * @brief Constructs a document message.
         * @param identifier                Document identifier.
         */
        explicit Layout(const Document::Identifier& identifier) : identifier(identifier) {}

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Constructs the document position.
         * @param json                          JSON to request.
         */
        static Layout m_decode(const $::Serde::Value& value) {
            return Layout($::Reflect::decode<Document::Identifier>(value.at("textDocument")));
        }
    };

    /// @brief Document Position Message.
    XLSP_MESSAGE_EXTENDS(Message::Layout, DOCUMENT_POSITION, DOCUMENT_IDENTIFIER) {
        //  PROPERTIES  //

        /// @brief Associated document position.
        Position position = {};

        //  CONSTRUCTORS  //

        /// @brief Do not allow default construction.
        explicit Layout() = delete;

        /**
         * @brief Constructs a document message.
         * @param identifier                Document identifier.
         * @param position                  Position to bind.
         */
        explicit Layout(const Document::Identifier& identifier, const Position& position = {}) :
            Layout<Message::Type::DOCUMENT_IDENTIFIER>(identifier), position(position) {}

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Constructs the document position.
         * @param json                          JSON to request.
         */
        static Layout m_decode(const $::Serde::Value& value) {
            auto position = $::Reflect::decode<Position>(value.at("position"));  // get position
            auto identifier = $::Reflect::decode<Document::Identifier>(value.at("textDocument"));
            return Layout(identifier, position);  // and construct the resulting parameters now
        }
    };

    /// @brief Document Opened Parameters.
    template <>
    struct Notification::Params<Message::Type::DOCUMENT_OPENED> {
        //  PROPERTIES  //

        /// @brief Underlying text-document.
        Document document;

        //  CONSTRUCTORS  //

        /**
         * @brief Constructs document open parameters.
         * @param document                      Document to bind.
         */
        explicit Params(const Document& document) : document(document) {}

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Constructs the initialize request parameters.
         * @param json                          JSON to request.
         */
        static Params m_decode(const $::Serde::Value& value) {
            return Params($::Reflect::decode<Document>(value.at("textDocument")));
        }
    };

    /// @brief Document Closed Parameters.
    XLSP_MESSAGE_EXTENDS(Notification::Params, DOCUMENT_CLOSED, DOCUMENT_IDENTIFIER) {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Layout<XLSP_MESSAGE_TYPE(DOCUMENT_IDENTIFIER)>::Layout;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Constructs the document parameters.
         * @param value                         Value to decode.
         */
        static Params m_decode(const $::Serde::Value& value) {
            return Params($::Reflect::decode<Document::Identifier>(value.at("textDocument")));
        }
    };

    /// @brief Document Changed Parameters.
    template <>
    struct Notification::Params<Message::Type::DOCUMENT_CHANGED> {
        //  PROPERTIES  //

        /// @brief Underlying text-document.
        Document::Identifier identifier;

        /// @brief Available document modifications.
        std::vector<Document::Change> changes = {};

        //  CONSTRUCTORS  //

        /**
         * @brief Constructs document open parameters.
         * @param identifier                    Document to bind.
         * @param changes                       Changes to bind.
         */
        explicit Params(const Document::Identifier& identifier, const std::vector<Document::Change>& changes = {}) :
            identifier(identifier), changes(changes) {}

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Constructs the document parameters.
         * @param value                         Value to decode.
         */
        static Params m_decode(const $::Serde::Value& value) {
            auto identifier = $::Reflect::decode<Document::Identifier>(value.at("textDocument"));
            auto changes = $::Reflect::decode<Document::Change>(*value.at<$::Serde::Array>("contentChanges"));
            return Params(identifier, changes);  // and construct the resulting parameters now
        }
    };

    /// @brief Document Hover Parameters.
    XLSP_MESSAGE_DOCUMENT(DOCUMENT_HOVER, DOCUMENT_POSITION);

    /// @brief Constructs a hover response.
    template <>
    struct Response::Value<Message::Type::DOCUMENT_HOVER> {
        //  PROPERTIES  //

        /// @brief Optional highlighting range value.
        std::optional<Range> range = std::nullopt;

        /// @brief The outgoing hover contents to be shown.
        $::Ptr::Unique<Markup::Content> contents = nullptr;

        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted result.
        explicit Value() = default;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Constructs the outgoing hover result.
         * @param response                      Response to encode.
         */
        static $::Serde::Value m_encode(const Value& response) {
            if (response.contents == nullptr) return $::Serde::Null();
            $::Serde::Object hover = { { "contents", $::Reflect::encode(*response.contents) } };
            if (response.range.has_value()) hover["range"] = $::Reflect::encode(*response.range);
            return hover;  // return the resulting hover details to be shown now
        }
    };

    /// @brief Document Links Parameters.
    XLSP_MESSAGE_DOCUMENT(DOCUMENT_LINKS, DOCUMENT_IDENTIFIER);

    /// @brief Constructs a links response.
    template <>
    struct Response::Value<Message::Type::DOCUMENT_LINKS> {
        //  PROPERTIES  //

        /// @brief The available document links.
        std::vector<Document::Link> links = {};

        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted result.
        explicit Value() = default;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Constructs the outgoing links result.
         * @param response                      Response to encode.
         */
        static $::Serde::Value m_encode(const Value& response) { return $::Reflect::encode(response.links); }
    };

    /// @brief Document Symbols Parameters.
    XLSP_MESSAGE_DOCUMENT(DOCUMENT_SYMBOLS, DOCUMENT_IDENTIFIER);

    /// @brief Constructs a symbols response.
    template <>
    struct Response::Value<Message::Type::DOCUMENT_SYMBOLS> {
        //  PROPERTIES  //

        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted result.
        explicit Value() = default;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Constructs the outgoing links result.
         * @param response                      Response to encode.
         */
        static $::Serde::Value m_encode(const Value&) { return {}; }
    };

    /// @brief Document Format Parameters.
    XLSP_MESSAGE_EXTENDS(Request::Params, DOCUMENT_FORMAT, DOCUMENT_IDENTIFIER) {
        //  PROPERTIES  //

        /// @brief Encapsulated formatting options.
        Format::Options options = {};

        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Layout<XLSP_MESSAGE_TYPE(DOCUMENT_IDENTIFIER)>::Layout;

        /**
         * @brief Constructs hover parameters from the base layout.
         * @param layout                        Layout to inherit.
         * @param options                       Formatting options.
         */
        explicit Params(const Layout& layout, const Format::Options& options = {}) : Layout(layout), options(options) {}

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Constructs the document parameters.
         * @param value                         Value to decode.
         */
        static Params m_decode(const $::Serde::Value& value) {
            auto options = $::Reflect::decode<Format::Options>(value.at("options"));
            return Params($::Reflect::decode<Layout>(value), options);  // construct
        }
    };

    /// @brief Constructs a format response.
    template <>
    struct Response::Value<Message::Type::DOCUMENT_FORMAT> {
        //  PROPERTIES  //

        /// @brief Optional highlighting range value.
        std::vector<Document::Edit> edits = {};

        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted result.
        explicit Value() = default;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Constructs the outgoing format result.
         * @param response                      Response to encode.
         */
        static $::Serde::Value m_encode(const Value& response) { return $::Reflect::encode(response.edits); }
    };

    /// @brief Document Completion Parameters.
    XLSP_MESSAGE_DOCUMENT(DOCUMENT_COMPLETIONS, DOCUMENT_IDENTIFIER);

    /// @brief Constructs a completions response.
    template <>
    struct Response::Value<Message::Type::DOCUMENT_COMPLETIONS> {
        //  PROPERTIES  //

        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted result.
        explicit Value() = default;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Constructs the outgoing completions result.
         * @param response                      Response to encode.
         */
        static $::Serde::Value m_encode(const Value&) { return {}; }
    };

    /// @brief Document Type-Definition Parameters.
    XLSP_MESSAGE_DOCUMENT(DOCUMENT_TYPE_DEFINITION, DOCUMENT_POSITION);

    /// @brief Constructs a type-definition response.
    template <>
    struct Response::Value<Message::Type::DOCUMENT_TYPE_DEFINITION> {
        //  PROPERTIES  //

        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted result.
        explicit Value() = default;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Constructs the outgoing type-definition result.
         * @param response                      Response to encode.
         */
        static $::Serde::Value m_encode(const Value&) { return {}; }
    };

    /// @brief Document Variable-Definition Parameters.
    XLSP_MESSAGE_DOCUMENT(DOCUMENT_VARIABLE_DEFINITION, DOCUMENT_POSITION);

    /// @brief Constructs a variable-definition response.
    template <>
    struct Response::Value<Message::Type::DOCUMENT_VARIABLE_DEFINITION> {
        //  PROPERTIES  //

        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted result.
        explicit Value() = default;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Constructs the outgoing variable-definition result.
         * @param response                      Response to encode.
         */
        static $::Serde::Value m_encode(const Value&) { return {}; }
    };

}  // namespace XLSP

#endif
