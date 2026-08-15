#ifndef _XLSP_PROTOCOL_WORKSPACE_HPP
#define _XLSP_PROTOCOL_WORKSPACE_HPP

/// XLSP Includes
#include "xlsp/forward/protocol.hpp"

namespace XLSP::Workspace {

/// @brief Designates a file, folder or any workspace operation.
enum class Operation : uint8_t {
  UNUSED = 0, // ignorable operation
  CREATE = 1, // a creation event
  CHANGE = 2, // a change event
  DELETE = 3, // a deletion event
};

/// @brief Encapsulates a file-change event.
struct File {
  //  PROPERTIES  //

  /// @brief The associated URI of a file.
  $::URI::Buffer resource;

  /// @brief The associated file-operation.
  Operation operation = Operation::UNUSED;

  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a workspace folder.
   * @param uri                       Resource URI.
   */
  explicit constexpr File(const $::URI::Buffer &uri) : resource(uri) {}
  explicit constexpr File(const $::URI::Buffer &uri, Operation type) : resource(uri), operation(type) {}

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles decoding workspace folders.
   * @param value                         Value to decode.
   */
  static File m_decode(const $::Serde::Value &value) {
    auto uri = $::Serde::Decode<$::URI::Buffer>(value.at("uri"));
    auto type = value.at<Operation>("type", Operation::UNUSED);
    return File(uri, type); // and construct the resulting file
  }
};

/// @brief Workspace Folders Structure.
struct Folder {
  //  PROPERTIES  //

  /// @brief Associated URI of the workspace folder.
  $::URI::Buffer resource;

  /// @brief Name of the workspace folder.
  $::String::Buffer name;

  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a workspace folder.
   * @param uri                           URI value.
   * @param identifier                    Workspace name.
   */
  explicit constexpr Folder(const $::URI::Buffer &uri, const $::String::Buffer &identifier) :
      resource(uri), name(identifier) {}

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles decoding workspace folders.
   * @param value                         Value to decode.
   */
  static Folder m_decode(const $::Serde::Value &value) {
    return Folder($::Serde::Decode<$::URI::Buffer>(value.at("uri")), *value.at<$::Serde::Text>("name"));
  }
};

} // namespace XLSP::Workspace

#endif
