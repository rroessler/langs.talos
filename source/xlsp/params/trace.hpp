#ifndef _XLSP_PARAMS_TRACE_HPP
#define _XLSP_PARAMS_TRACE_HPP

/// XLSP Includes
#include "xlsp/message/notification.hpp"
#include "xlsp/protocol/trace.hpp"

namespace XLSP::Notification {

/// @brief Incoming Set Trace Parameters.
template <> struct Params<Channel::TRACE_SET> {
  //  PROPERTIES  //

  /// @brief Underlying trace-value.
  Trace::Value value = Trace::Value::OFF;

  //  CONSTRUCTORS  //

  /// @brief Constructs the defaulted trace parameters.
  constexpr Params(const Trace::Value &value = Trace::Value::OFF) : value(value) {}

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Constructs the initialize request parameters.
   * @param json                          JSON to request.
   */
  static inline Params m_decode(const $::Serde::Value &value) {
    return Trace::resolve(*value.at<$::Serde::Text>("value"));
  }
};

/// @brief Outgoing Log Trace Parameters.
template <> struct Params<Channel::TRACE_LOG> {
  //  PROPERTIES  //

  /// @brief Message to be logged.
  $::String::Buffer message = "";

  /// @brief Additional tracing details.
  std::optional<$::String::Buffer> verbose = std::nullopt;

  //  CONSTRUCTORS  //

  /// @brief Constructs the defaulted trace parameters.
  explicit Params() = default;

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles encoding trace logs.
   * @param trace                     Trace details.
   */
  static $::Serde::Value m_encode(const Params &trace) {
    $::Serde::Object value = {{"message", trace.message}};
    if (trace.verbose.has_value()) value.emplace("verbose", *trace.verbose);
    return value; // and return the resulting trace log parameters
  }
};

} // namespace XLSP::Notification

#endif
