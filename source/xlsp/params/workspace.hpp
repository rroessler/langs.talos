#ifndef _XLSP_PARAMS_WORKSPACE_HPP
#define _XLSP_PARAMS_WORKSPACE_HPP

/// XLSP Includes
#include "xlsp/message/notification.hpp"
#include "xlsp/protocol/workspace.hpp"

namespace XLSP::Notification {

/// @brief Cancellation parameters.
template <> struct Params<Channel::WORKSPACE_FILE_CHANGED> {
  //  PROPERTIES  //

  /// @brief Current workspace file changes.
  std::vector<Workspace::File> changes = {};

  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a workspace changed event.
   * @param changes               Changes that occured.
   */
  constexpr Params(const std::vector<Workspace::File> &changes = {}) : changes(changes) {}

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Constructs the initialize request parameters.
   * @param json                    JSON to request.
   */
  static Params m_decode(const $::Serde::Value &value) {
    auto changes = value.at("changes", $::Serde::Array());
    return $::Serde::Decode<Workspace::File>(changes);
  }
};

} // namespace XLSP::Notification

#endif
