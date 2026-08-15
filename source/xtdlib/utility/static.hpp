#ifndef _XTDLIB_UTILITY_STATIC_HPP
#define _XTDLIB_UTILITY_STATIC_HPP

namespace $::Ensure {

/// @brief Ensures any inherited classes are static-only.
struct Static {
  //  CONSTRUCTORS  //

  constexpr Static(...) = delete;
  constexpr ~Static() = delete;

  //  OPERATOR METHODS  //

  constexpr Static &operator=(Static &&) = delete;
  constexpr Static &operator=(const Static &) = delete;
};

} // namespace $::Ensure

#endif
