#ifndef _XLSP_MESSAGE_TRAITS_HPP
#define _XLSP_MESSAGE_TRAITS_HPP

/// XLSP Modules
#include "xlsp/message/json.hpp"

//  X-MACROS  //

#define XX_INTERNAL_LIST(X)                       \
    X(DOCUMENT_POSITION, "textDocument/position") \
    X(DOCUMENT_IDENTIFIER, "textDocument/identifier")

#define XX_NOTIFICATIONS_LIST(X)                                 \
    X($_CANCEL, "$/cancelRequest")                               \
    X($_PROGRESS, "$/progress")                                  \
                                                                 \
    X(TRACE_SET, "$/setTrace")                                   \
    X(TRACE_LOG, "$/logTrace")                                   \
                                                                 \
    X(LIFECYCLE_INITIALIZED, "initialized")                      \
    X(LIFECYCLE_EXIT, "exit")                                    \
                                                                 \
    X(DOCUMENT_OPENED, "textDocument/didOpen")                   \
    X(DOCUMENT_CLOSED, "textDocument/didClose")                  \
    X(DOCUMENT_CHANGED, "textDocument/didChange")                \
                                                                 \
    X(PUBLISH_DIAGNOSTICS, "textDocument/publishDiagnostics")    \
                                                                 \
    X(WORKSPACE_FILE_CHANGED, "workspace/didChangeWatchedFiles") \
    X(WORKSPACE_CONFIG_CHANGED, "workspace/didChangeConfiguration")

#define XX_REQUESTS_LIST(X)                                    \
    X(LIFECYCLE_INITIALIZE, "initialize")                      \
    X(LIFECYCLE_SHUTDOWN, "shutdown")                          \
                                                               \
    X(DOCUMENT_HOVER, "textDocument/hover")                    \
    X(DOCUMENT_LINKS, "textDocument/documentLink")             \
    X(DOCUMENT_FORMAT, "textDocument/formatting")              \
    X(DOCUMENT_SYMBOLS, "textDocument/documentSymbol")         \
    X(DOCUMENT_REFERENCES, "textDocument/references")          \
    X(DOCUMENT_COMPLETIONS, "textDocument/completion")         \
    X(DOCUMENT_DECLARATION, "textDocument/declaration")        \
    X(DOCUMENT_IMPLEMENTATION, "textDocument/implementation")  \
    X(DOCUMENT_TYPE_DEFINITION, "textDocument/typeDefinition") \
    X(DOCUMENT_VARIABLE_DEFINITION, "textDocument/definition")

#define XX_MESSAGES_LIST(X)                     \
    XX_NOTIFICATIONS_LIST(X)                    \
    X($_NOTIFICATION, "separator/notification") \
    XX_INTERNAL_LIST(X)                         \
    X($_REQUEST, "separator/request")           \
    XX_REQUESTS_LIST(X)

//  MACROS  //

#define XLSP_MESSAGE_TYPE(T, ...) ::XLSP::Message::Type::T
#define XLSP_MESSAGE_CHANNEL(T, ...) ::XLSP::Message::Channel<XLSP_MESSAGE_TYPE(T)>()
#define XLSP_MESSAGE_EMPTY(B, T, ...) XLSP_MESSAGE_INTERNAL(B, T, Empty, ::XLSP::B<XLSP_MESSAGE_TYPE(T)>)
#define XLSP_MESSAGE_NULLISH(B, T, ...) XLSP_MESSAGE_INTERNAL(B, T, Nullish, ::XLSP::B<XLSP_MESSAGE_TYPE(T)>)

#define XLSP_MESSAGE_INTERNAL(B, T, E, ...) \
    template <>                             \
    struct ::XLSP::B<XLSP_MESSAGE_TYPE(T)> : public ::XLSP::Message::E<XLSP_MESSAGE_TYPE(T) $_PP_VARGS(__VA_ARGS__)>

#define XLSP_MESSAGE_EXTENDS(B, T, E, ...) \
    template <>                            \
    struct ::XLSP::B<XLSP_MESSAGE_TYPE(T)> : public ::XLSP::Message::Layout<XLSP_MESSAGE_TYPE(E)>

//  NAMESPACES  //

namespace XLSP::Message {

    /// @brief The available message types.
    $_XX_ENUM_CLASS(Type, size_t, XX_MESSAGES_LIST);

    /// @brief Defines empty parameters.
    template <Type, class B>
    struct Empty {
       protected:
        //  PRIVATE METHODS  //

        /// @brief Underlying fallback encoder/decoder.
        static inline B m_decode(const $::Serde::Value&) { return B(); }
        static inline $::Serde::Value m_encode(const B&) { return $::Serde::Object(); }
    };

    /// @brief Defines nullish parameters.
    template <Type, class B>
    struct Nullish {
       protected:
        //  PRIVATE METHODS  //

        /// @brief Underlying fallback value.
        static inline B m_decode(const $::Serde::Value&) { return B(); }
        static inline $::Serde::Value m_encode(const B&) { return $::Serde::Null(); }
    };

    /// @brief Inheritance messages.
    template <Type>
    struct Layout;

    /// @brief Gets the associated method channel.
    template <Type T>
    static consteval Method Channel() {
#define X(N, M, ...) \
    case Type::N: return M;
        switch (T) { XX_MESSAGES_LIST(X) default : return "$/unknown"; }
#undef X
    }

}  // namespace XLSP::Message

//  UNDEFINES  //

#undef XX_MESSAGES_LIST
#undef XX_INTERNAL_LIST
#undef XX_REQUESTS_LIST
#undef XX_NOTIFICATIONS_LIST

#endif
