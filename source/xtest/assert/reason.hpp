#ifndef _XTEST_ASSERT_REASON_HPP
#define _XTEST_ASSERT_REASON_HPP

/// Vendor Includes
#include <xtdlib/xtdlib.hpp>

namespace XT::Assert {

/// @brief Encapsulates a timeout error.
struct Timeout : public std::runtime_error {
  explicit Timeout() : std::runtime_error("Test timed out") {}
};

/// @brief Handles translation current exceptions.
static inline $::String::Buffer Reason() {
  // handle violations in mix-mode projects for MSVC exceptions
  if (std::current_exception() == nullptr) return "Non C++ exception. Possibly a CLR exception";

  // clang-format off
        try { std::rethrow_exception(std::current_exception()); }
        catch (const std::exception& exception) { return exception.what(); }
        catch (const $::String::Buffer& message) { return message; }
        catch (const char* message) { return message; }
        catch (...) { return "Unknown exception"; }
  // clang-format on
}

} // namespace XT::Assert

#endif
