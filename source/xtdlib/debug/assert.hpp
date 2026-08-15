#ifndef _XTDLIB_DEBUG_ASSERT_HPP
#define _XTDLIB_DEBUG_ASSERT_HPP

/// Library Includes
#include "xtdlib/debug/location.hpp"
#include "xtdlib/debug/logger.hpp"
#include "xtdlib/system/abort.hpp"
#include "xtdlib/system/debugbreak.hpp"

//  MACROS  //

#define $_ASSERT_IMPL(E, L, T, ...)                                                                                 \
  ($_LIKELY(!!(E)) ? $_PP_NOOP()                                                                                    \
                   : ::$::Assert::failure<::$::Logger::Level::L>(T, $::Source::Location() $_PP_VARGS(__VA_ARGS__)))

#define $_EXPECT(E, ...) $_ASSERT_IMPL(E, FATAL, "Fatal Assertion", __VA_ARGS__)
#define $_ABORT(...) $_ASSERT_IMPL(false, FATAL, "Program Aborted", __VA_ARGS__), ::$::System::unreachable()

#if $_PP_NDEBUG
#define $_ASSERT(E, ...) $_PP_NOOP()
#define $_WASSERT(E, ...) $_PP_NOOP()
#else
#define $_ASSERT(E, ...) $_ASSERT_IMPL(E, ERROR, "Error Assertion", __VA_ARGS__)
#define $_WASSERT(E, ...) $_ASSERT_IMPL(E, WARN, "Warning Assertion", __VA_ARGS__)
#endif

//  NAMESPACES  //

namespace $::Assert {

//  PUBLIC METHODS  //

/// @brief Static Warning Condition.
template <bool C> struct warn {};

/// @brief Denotes a static warning occured.
template <> struct [[deprecated("static_warn triggered")]] warn<false> {};

/// @brief Handles failures based on any logger level.
template <Logger::Level L> inline void failure() {}

/**
 * @brief Handles emitting assertion failures.
 * @param title                 Message title.
 * @param fmt                   Format message.
 * @param args                  Message arguments.
 */
template <Logger::Level L, class... As>
inline void failure(const char *title, const Source::Location &location, fmt::format_string<As...> fmt, As &&...args) {
  auto message = fmt::format(fmt, std::forward<As>(args)...);
  Logger::Output::write(L, "{0}: \"{1}\"", title, message);
  Logger::Output::write(L, "-> {0}", location); // show source

  // and run the base failure specialization
  failure<L>();
}

/**
 * @brief Handles emitting assertion failures.
 * @param title                 Message title.
 */
template <Logger::Level L> inline void failure(const char *title, const Source::Location &location) {
  Logger::Output::write(L, "{0} at \"{1}\"", title, location), failure<L>();
}

//  SPECIALIZATIONS  //

/// @brief Fatal errors are fatal.
template <> inline void failure<Logger::Level::FATAL>() { $::System::abort(); }

/// @brief Regular errors should be "debugbreaks".
template <> inline void failure<Logger::Level::ERROR>() { $::System::debugbreak(); }

} // namespace $::Assert

#endif
