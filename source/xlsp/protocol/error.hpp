#ifndef _XLSP_PROTOCOL_ERROR_HPP
#define _XLSP_PROTOCOL_ERROR_HPP

/// XLSP Includes
#include "xlsp/forward/protocol.hpp"

namespace XLSP {

/// @brief Response Error Structure.
struct Error {
  //  TYPEDEFS  //

  /// @brief Available error codes.
  struct Code : private $::Ensure::Static {
    static constexpr int64_t PARSE_ERROR = -32700;
    static constexpr int64_t REQUEST_INVALID = -32600;
    static constexpr int64_t METHOD_MISSING = -32601;
    static constexpr int64_t PARAMS_INVALID = -32602;
    static constexpr int64_t INTERNAL_ERROR = -32603;

    static constexpr int64_t SERVER_DETACHED = -32002;
    static constexpr int64_t UNKNOWN_ERROR = -32001;

    static constexpr int64_t REQUEST_FAILED = -32803;
    static constexpr int64_t SERVER_CANCELLED = -32802;
    static constexpr int64_t CONTENT_MODIFIED = -32801;
    static constexpr int64_t REQUEST_CANCELLED = -32800;
  };

private:
  //  PROPERTIES  //

  /// @brief Bound error code.
  int64_t m_code;

  /// @brief Detailed error message.
  $::String::Buffer m_message;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a response error.
   * @param code                Code to bind.
   * @param message             Error message.
   */
  constexpr Error(int64_t code = Code::UNKNOWN_ERROR, const $::String::Buffer &message = {}) :
      m_code(code), m_message(m_describe(m_code, message)) {}

  //  PUBLIC METHODS  //

  /// @brief Gets the associated error code.
  inline constexpr int64_t code() const noexcept { return m_code; }

  /// @brief Gets the associated error message.
  inline constexpr $::String::View message() const noexcept { return m_message; }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles describing errors.
   * @param code                  Code to describe.
   * @param incoming              Incoming message.
   */
  static inline constexpr $::String::Buffer m_describe(int64_t code, const $::String::Buffer &incoming = {}) {
    // ignore if the incoming message has some data
    if (incoming.size()) return incoming;

    // otherwise prepare some alternative messages
    switch (code) {
    case Code::PARSE_ERROR: return "Invalid JSON as received by the server.";
    case Code::REQUEST_INVALID: return "The JSON sent is not a valid request.";
    case Code::METHOD_MISSING: return "The given method does not exist.";
    case Code::PARAMS_INVALID: return "Invalid method parameter(s).";
    case Code::INTERNAL_ERROR: return "An internal JSON-RPC error occured.";

    case Code::SERVER_DETACHED: return "Server has not finished intializing.";

    case Code::REQUEST_FAILED: return "Request failed for unknown reasons.";
    case Code::SERVER_CANCELLED: return "Server has cancelled the request.";
    case Code::CONTENT_MODIFIED: return "Document contains modified content.";
    case Code::REQUEST_CANCELLED: return "Request cancellation detected.";

    // otherwise default to a suitable basic message
    default: return "An unknown error occured.";
    }
  }

  /**
   * @brief Handles constructing error JSON.
   * @param self                  Error to encode.
   */
  static inline $::Serde::Value m_encode(const Error &self) {
    return {{"code", self.m_code}, {"message", self.m_message}};
  }

  /**
   * @brief Handles decoding response-errors.
   * @param jvalue                JSON value to decode.
   */
  static inline Error m_decode(const $::Serde::Value &value) {
    auto code = value.at<int64_t>("code", Code::UNKNOWN_ERROR);
    return {code, value.at<$::Serde::Text>("message", m_describe(code))};
  }

  /**
   * @brief Handles printing errors.
   * @param os                    Output stream.
   * @param self                  Error instance.
   */
  static inline void m_print(std::ostream &os, const Error &self) {
    os << "Error [" << self.m_code << "]: " << self.m_message;
  }
};

} // namespace XLSP

#endif
