#ifndef _XLSP_MESSAGE_CHANNEL_HPP
#define _XLSP_MESSAGE_CHANNEL_HPP

/// XLSP Includes
#include "xlsp/forward/event.hpp"
#include "xlsp/forward/message.hpp"
#include "xlsp/protocol/error.hpp"

/// Forward Definitions
$_FWD(XLSP::Message, template <class T> using Result = std::variant<T, Error>)
$_FWD(XLSP::Message, template <size_t N> using Channel = $::String::Literal<N>)

//  X-MACROS  //

#define XLSP_XX_NOTIFICATION_CHANNELS(X)                          \
  X(QUERY_CANCEL, "$/cancel")                                     \
  X(QUERY_PROGRESS, "$/progress")                                 \
                                                                  \
  X(TRACE_SET, "$/setTrace")                                      \
  X(TRACE_LOG, "$/logTrace")                                      \
                                                                  \
  X(LIFECYCLE_READY, "initialized")                               \
  X(LIFECYCLE_EXIT, "exit")                                       \
                                                                  \
  X(DOCUMENT_OPENED, "textDocument/didOpen")                      \
  X(DOCUMENT_CLOSED, "textDocument/didClose")                     \
  X(DOCUMENT_CHANGED, "textDocument/didChange")                   \
                                                                  \
  X(DIAGNOSTICS_PUBLISH, "textDocument/publishDiagnostics")       \
                                                                  \
  X(WORKSPACE_FILE_CHANGED, "workspace/didChangeWatchedFiles")    \
  X(WORKSPACE_CONFIG_CHANGED, "workspace/didChangeConfiguration")

#define XLSP_XX_REQUEST_CHANNELS(X)                         \
  X(LIFECYCLE_INIT, "initialize")                           \
  X(LIFECYCLE_SHUTDOWN, "shutdown")                         \
                                                            \
  X(DOCUMENT_HOVER, "textDocument/hover")                   \
  X(DOCUMENT_LINKS, "textDocument/documentLink")            \
  X(DOCUMENT_FORMAT, "textDocument/formatting")             \
  X(DOCUMENT_SYMBOLS, "textDocument/documentSymbol")        \
  X(DOCUMENT_VARDEF, "textDocument/definition")             \
  X(DOCUMENT_TYPEDEF, "textDocument/typeDefinition")        \
  X(DOCUMENT_REFERENCES, "textDocument/references")         \
  X(DOCUMENT_COMPLETIONS, "textDocument/completion")        \
  X(DOCUMENT_DECLARATION, "textDocument/declaration")       \
  X(DOCUMENT_IMPLEMENTATION, "textDocument/implementation")

//  NAMESPACES  //

namespace XLSP::Message {

/// @brief Denotes Empty Parameters.
template <class B> struct Empty {
protected:
  //  PRIVATE METHODS  //

  static inline B m_decode(const $::Serde::Value &) { return B(); }
  static inline $::Serde::Value m_encode(const B &) { return $::Serde::Object(); }
};

/// @brief Denotes Nullish Parameters.
template <class B> struct Nullish {
protected:
  //  PRIVATE METHODS  //

  static inline B m_decode(const $::Serde::Value &) { return B(); }
  static inline $::Serde::Value m_encode(const B &) { return $::Serde::Null(); }
};

} // namespace XLSP::Message

#define X(C, M, ...) static constexpr Message::Channel C = M;

namespace XLSP::Notification::Channel {
XLSP_XX_NOTIFICATION_CHANNELS(X)
}

namespace XLSP::Request::Channel {
XLSP_XX_REQUEST_CHANNELS(X)
}

#undef X

#endif
