#ifndef _XLSP_SERVER_OPTIONS_HPP
#define _XLSP_SERVER_OPTIONS_HPP

/// XLSP Includes
#include "xlsp/forward/server.hpp"
#include "xlsp/protocol/encoding.hpp"

namespace XLSP::Server {

/// @brief Server Options.
struct Options {
  //  PROPERTIES  //

  /// @brief Server based options.
  struct {
    $::String::Buffer title = "xlsp";    // Connection title.
    $::String::Buffer version = "0.0.0"; // Server versioning.

    /// @brief Underlying server encoding.
    Encoding::Type encoding = Encoding::Type::INVALID;
  } server;

  /// @brief Event options.
  struct {
    size_t threshold = 100;
  } events;
};

} // namespace XLSP::Server

#endif
