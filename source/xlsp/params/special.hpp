#ifndef _XLSP_PARAMS_SPECIAL_HPP
#define _XLSP_PARAMS_SPECIAL_HPP

/// XLSP Includes
#include "xlsp/message/notification.hpp"

namespace XLSP::Notification {

/// @brief Cancellation parameters.
template <> struct Params<Channel::QUERY_CANCEL> {
  //  PROPERTIES  //

  /// @brief Underlying cancellation identifier.
  $::String::Buffer identifier = "";

  //  CONSTRUCTORS  //

  /// @brief Constructs the defaulted cancellation details.
  constexpr Params() = default;

  /**
   * @brief Constructs a set of cancellation details.
   * @param identifier              Identifier to bind.
   */
  constexpr Params(const $::String::Buffer &identifier) : identifier(identifier) {}

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Constructs the initialize request parameters.
   * @param json                    JSON to request.
   */
  static Params m_decode(const $::Serde::Value &value) {
    // prepare the base parameters structure
    auto params = Params();

    // get the baseline identifier value
    auto identifier = value.at("id");

    // attempt getting a suitable identifier now
    if (auto *_ = value.as<$::Serde::Text>()) params.identifier = *_;
    if (auto *_ = value.as<$::Serde::Number>()) params.identifier = fmt::to_string(*_);

    // return the resulting parameters
    return params;
  }
};

} // namespace XLSP::Notification

#endif
