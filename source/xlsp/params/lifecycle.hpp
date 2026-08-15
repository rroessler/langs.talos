#ifndef _XLSP_PARAMS_LIFECYCLE_HPP
#define _XLSP_PARAMS_LIFECYCLE_HPP

/// XLSP Includes
#include "xlsp/message/notification.hpp"
#include "xlsp/message/request.hpp"
#include "xlsp/protocol/process.hpp"
#include "xlsp/protocol/workspace.hpp"

namespace XLSP::Notification {

/// @brief Denotes Lifecycle Readiness.
template <> struct Params<Channel::LIFECYCLE_READY> : public Empty<Channel::LIFECYCLE_READY> {};

/// @brief Denotes Lifecycle Shutdown.
template <> struct Params<Channel::LIFECYCLE_EXIT> : public Empty<Channel::LIFECYCLE_EXIT> {};

} // namespace XLSP::Notification

namespace XLSP::Request {

/// @brief Denotes Lifecycle Shutdown.
template <> struct Params<Channel::LIFECYCLE_SHUTDOWN> : Empty<Channel::LIFECYCLE_SHUTDOWN> {};
template <> struct Result<Channel::LIFECYCLE_SHUTDOWN> : Nullish<Channel::LIFECYCLE_SHUTDOWN> {};

/// @brief Lifecycle Initialize Parameters.
template <> struct Params<Channel::LIFECYCLE_INIT> {
  //  PROPERTIES  //

  /// @brief Process ID of the parent process that started the server.
  int64_t ppid = -1;

  /// @brief The locale the client is currently showing the user-interface in.
  $::String::Buffer locale = "";

  /// @brief Available workspace folders.
  std::vector<Workspace::Folder> workspaces = {};

  /// @brief Client capabilities.
  $::Serde::Object capabilities = $::Serde::Object();

  /// @brief Client information.
  std::optional<Process::Information> client = std::nullopt;

  //  CONSTRUCTORS  //

  /// @brief Constructs a defaulted initialize request.
  explicit Params() = default;

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Constructs the initialize request parameters.
   * @param json                          JSON to request.
   */
  static Params m_decode(const $::Serde::Value &value) {
    // prepare the base parameters structure
    auto params = Params();

    // ensure we have the base information now
    auto info = value.at("clientInfo");
    auto capabilities = value.at("capabilities");

    // attempt assigning each of our details
    if (auto *locale = value.at<$::Serde::Text>("locale")) params.locale = *locale;
    if (auto *ppid = value.at<$::Serde::Number>("processId")) params.ppid = static_cast<int64_t>(*ppid);

    // some items require larger details to be parsed now
    if (auto *result = capabilities.as<$::Serde::Object>()) params.capabilities = *result;
    if (info.is<$::Serde::Object>()) params.client = $::Serde::Decode<Process::Information>(info);

    // return the resulting parameters
    return params;
  }
};

/// @brief Lifecycle Initialize Result.
template <> struct Result<Channel::LIFECYCLE_INIT> {
  //  PROPERTIES  //

  /// @brief Server capabilities.
  $::Serde::Object capabilities = $::Serde::Object();

  /// @brief Server Information.
  std::optional<Process::Information> server = std::nullopt;

  //  CONSTRUCTORS  //

  /// @brief Constructs the defaulted initialize response.
  explicit Result() = default;

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Constructs the initialize response JSON.
   * @param response                      Response to encode.
   */
  static $::Serde::Value m_encode(const Result &response) {
    $::Serde::Object structure = {{"capabilities", response.capabilities}};
    if (response.server.has_value()) structure["serverInfo"] = $::Serde::Encode(*response.server);
    return structure; // return the final structure to be used now
  }
};

} // namespace XLSP::Request

#endif
